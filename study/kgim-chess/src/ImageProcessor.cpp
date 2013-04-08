/***************************************************************************
 *   Copyright (C) 2007 by Ivan A. Tolstosheyev   *
 *   ivan.tolstosheyev@gmail.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "ImageProcessor.h"
#include "ImageViewer.h"
#include <math.h>
#include <QtGui>
#include <vector>


ImageProcessor::ImageProcessor(void) {
  image=NULL;
  source=NULL;
};

ImageProcessor::ImageProcessor(QImage SourceImage) {
  image = new QImage(SourceImage);
  source = new QImage(SourceImage);
}

void ImageProcessor::setImage(QImage SourceImage) {
  if (image!=NULL) delete image;
  image = new QImage(SourceImage);
  if (source!=NULL) delete source;
  source = new QImage(SourceImage);
}

void ImageProcessor::writeLog(QString Message, int IsError) {
  emit sendLogMessage(Message,IsError);
}


RectArea ImageProcessor::findDesk(void) {

  std::vector<int> HProjection;
  std::vector<int> VProjection;

  getProjections(RectArea(0,0,image->width(),image->height()),HProjection, VProjection);

  int HMinElem=255;
  int VMinElem=255;

  for(unsigned int i=0;i<HProjection.size();i++) {
    if (HProjection[i]<HMinElem) {HMinElem=HProjection[i];}
  }

  for(unsigned int i=0;i<VProjection.size();i++) {
    if (VProjection[i]<VMinElem) {VMinElem=VProjection[i];}
  }

  int HCountMin=0;
  int VCountMin=0;

  while (HCountMin<18) {
    HCountMin=0;
    for(unsigned int i=0;i<HProjection.size();i++) {
      if (HProjection[i]<=HMinElem) {HCountMin++;}
    }
    HMinElem++;
  }
  
  while (VCountMin<18) {
    VCountMin=0;
    for(unsigned int i=0;i<VProjection.size();i++) {
      if (VProjection[i]<=VMinElem) {VCountMin++;}
    }
    VMinElem++;
  }
  if (HCountMin>18) {
    writeLog(QString(tr("ERROR: Can't find desk")),1);
  }

  int x1=0;
  for(x1=0;(static_cast<unsigned int>(x1))<HProjection.size();x1++) {
    if (HProjection[x1]<=HMinElem) {break;} 
  }

  int y1=0;
  for(y1=0;(static_cast<unsigned int>(y1))<VProjection.size();y1++) {
    if (VProjection[y1]<=VMinElem) break;
  }

  int x2=0;
  for(x2=HProjection.size()-1;x2>=0;x2--) {
    if (HProjection[x2]<=HMinElem) break; 
  }

  int y2=0;
  for(y2=VProjection.size()-1;y2>=0;y2--) {
    if (VProjection[y2]<=VMinElem) break;
  }


  int StepX=(x2-x1-1)/8;
  for (int i=0;i<=8;i++) {
    if (((HProjection[x1+i*StepX])>HMinElem) ||
        ((HProjection[x1+i*StepX+1])>HMinElem)) {
          writeLog(QString(tr("ERROR: Can't found 2px - lines on X axis")),1);
        }
  }

  int StepY=(y2-y1-1)/8;
  for (int i=0;i<=8;i++) {
    if (((VProjection[y1+i*StepY])>VMinElem) ||
          ((VProjection[y1+i*StepY+1])>VMinElem)) {
            writeLog(QString(tr("ERROR: Can't found 2px - lines on Y axis")),1);
          }
  }


  writeLog(QString(tr("Found chess desk at X: %1; Y: %2; Width: %3; Height: %4;")).arg(x1).arg(y1).arg(x2-x1).arg(y2-y1));
  return RectArea(x1,y1,x2-x1+1,y2-y1+1);
}

void ImageProcessor::findPieces(std::vector<std::vector<PieceSquare> > &ChessDesk) {
  RectArea CurrentSquare=findSquare(0,0);

  // Finding min and max brightness for autocontrast.
  int MaxGrayPixel=0;
  int MinGrayPixel=255;

  for(int i=0;i<8;i++) {
    for(int j=0;j<8;j++) {
      CurrentSquare=findSquare(i,j);
      for(int k=0;k<CurrentSquare.width-1;k++) {
        for(int l=0;l<CurrentSquare.height-1;l++) {
          int CurrentGrayPixel=qGray(image->pixel(CurrentSquare.x+k,CurrentSquare.y+l));
          if (CurrentGrayPixel>MaxGrayPixel) {
            MaxGrayPixel=CurrentGrayPixel;
          }
          if (CurrentGrayPixel<MinGrayPixel) {
            MinGrayPixel=CurrentGrayPixel;
          }
        }
      }
    }
  }
  
  writeLog(QString(tr("Minimum brightness: %1; Maximium brightness: %2;")).arg(MinGrayPixel).arg(MaxGrayPixel));

  
  int a[256];

  for(int i=0;i<256;i++) {a[i]=0;}
  
  for(int i=0;i<8;i++) {
    for(int j=0;j<8;j++) {
      CurrentSquare=findSquare(i,j);

      if ((MaxGrayPixel-MinGrayPixel)<128) {
        filterAutoContrast(CurrentSquare, *image,MinGrayPixel,MaxGrayPixel);
        filterAverage(CurrentSquare, *image);
      }
      filterMedian(CurrentSquare, *image);

      for(int k=0;k<CurrentSquare.width-1;k++) {
        for(int l=0;l<CurrentSquare.height-1;l++) {
          a[qGray(image->pixel(CurrentSquare.x+k,CurrentSquare.y+l))]++;
        }
      }
      CurrentSquare.x--;
      CurrentSquare.y--;
      CurrentSquare.width++;
      CurrentSquare.height++;
      drawRect(CurrentSquare);
    }
  }

  int max=0;

  for(int i=0;i<256;i++) {
    if (a[i]>max) max=a[i];
    //writeLog(QString("G %1 %2").arg(i).arg(a[i]));
  }

  writeLog(QString("MAX %1").arg(max));
  for(int i=0;i<256;i++) {
    for(int j=0;j<static_cast<int>((static_cast<double>(a[i]))*500/max);j++) {
      //image->setPixel(i,j,0x0000ff);
    }
  }
  
  std::vector<int> sorta;
  for(int i=0;i<256;i++) {
    sorta.push_back(a[i]);
  }
  std::sort(&sorta[0], &sorta[sorta.size()]);
  std::vector<int> Maximums;
  for (int i=255;i>=0;i--) {
    int IsInsideExtr=0;
    int EnterExtr=0;
    int LastEnter=-10;
    for(int j=0;j<256;j++) {
      if ((a[j]>sorta[i]) && (!IsInsideExtr)) {
        IsInsideExtr=1;
        EnterExtr++;
        if (abs(LastEnter-j)<10) {
          IsInsideExtr=0;
          EnterExtr--;
          Maximums.pop_back();
        } else {
          LastEnter=j;
          Maximums.push_back(j);
          writeLog(QString("POS %1").arg(j));
        }
      }

      if ((a[j]<sorta[i]) && (IsInsideExtr)) {
        IsInsideExtr=0;
      }
    }
    writeLog(QString("EXT %1").arg(EnterExtr));
    if (EnterExtr>=2) {break;} else Maximums.clear();
  }
  
  std::sort(&Maximums[0], &Maximums[Maximums.size()]);

  while (a[Maximums[0]]>0){Maximums[0]--;}
  while (a[Maximums[1]]>0){Maximums[1]++;}
  writeLog(QString("M1 %1 M2 %2").arg(Maximums[0]).arg(Maximums[1]));
;

  /////////////////////////////////////!!!!!!!!!!!!!!!!!!!!!!!!
  
  for(int i=0;i<8;i++) {
    for(int j=0;j<8;j++) {
      CurrentSquare=findSquare(i,j);

      int AboveScale=0;
      int BelowScale=0;
      for(int k=0;k<CurrentSquare.width-1;k++) {
        for(int l=0;l<CurrentSquare.height-1;l++) {
          int current=qGray(image->pixel(CurrentSquare.x+k,CurrentSquare.y+l));
          if ((current<Maximums[0]) || (current>Maximums[1])) { 
            image->setPixel(CurrentSquare.x+k,CurrentSquare.y+l,0xffffff);
            if (current<Maximums[0]) BelowScale++;
            if (current>Maximums[1]) AboveScale++;
          } else 
          {
            image->setPixel(CurrentSquare.x+k,CurrentSquare.y+l,0x000000);
          }
        }
      }

      if (AboveScale>BelowScale) {
        ChessDesk[i][j].Color=1;
      } else {
        ChessDesk[i][j].Color=0;
      }
      
      writeLog(QString(tr("X %1 Y %2 C %3")).arg(i+1).arg(j+1).arg(ChessDesk[i][j].Color));

      if (DebugMode) {
        sendImage(*image);
        writeLog(QString(tr("Binarizing square X:%1 Y:%2.")).arg(i+1).arg(j+1));
      }
        
      approximateBorder(CurrentSquare, *image);

      if ((MaxGrayPixel-MinGrayPixel)<128) {
        filterDilation(CurrentSquare, *image);
        filterErosion(CurrentSquare, *image);
      }

      filterErosion(CurrentSquare, *image);
      filterDilation(CurrentSquare, *image);
      filterFigure(CurrentSquare, *image);
      recognizePiece(CurrentSquare, *image, ChessDesk[i][j]);
    }
  }
  
  for(int i=0;i<8;i++) {
    for(int j=0;j<8;j++) {
      if (ChessDesk[i][j].Type) {
        int type=ChessDesk[i][j].Type;
        int color=ChessDesk[i][j].Color;
        if (type==1 && color==0)
          writeLog(QString("X %1 Y %2 F %3").arg(i+1).arg(j+1).arg("Black King"));
        if (type==1 && color==1)
          writeLog(QString("X %1 Y %2 F %3").arg(i+1).arg(j+1).arg("White King"));
        if (type==2 && color==0)
          writeLog(QString("X %1 Y %2 F %3").arg(i+1).arg(j+1).arg("Black Queen"));
        if (type==2 && color==1)
          writeLog(QString("X %1 Y %2 F %3").arg(i+1).arg(j+1).arg("White Queen"));
        if (type==3 && color==0)
          writeLog(QString("X %1 Y %2 F %3").arg(i+1).arg(j+1).arg("Black Pawn"));
        if (type==3 && color==1)
          writeLog(QString("X %1 Y %2 F %3").arg(i+1).arg(j+1).arg("White Pawn"));
      }
    }
  }
  /////////////////////////////////////
  CheckMatePosition CurrentAttack=checkPosition(ChessDesk);

  delete image;
  image = new QImage(*source);
  drawRect(ChessArea,0xff0000);
  for(int i=0;i<8;i++) {
    for(int j=0;j<8;j++) {
      CurrentSquare=findSquare(i,j);
      if (ChessDesk[i][j].Type) {
        int type=ChessDesk[i][j].Type;
        int color=ChessDesk[i][j].Color;
        if (type==1 && color==0) //Black King
          drawRect(CurrentSquare,qRgb(30,89,19),5);
        if (type==1 && color==1) //White King
          drawRect(CurrentSquare,qRgb(121,11,11),5);
        if (type==2 && color==0) //Black Queen
          drawRect(CurrentSquare,qRgb(54,179,35),5);
        if (type==2 && color==1) //White Queen
          drawRect(CurrentSquare,qRgb(237,44,44),5);
        if (type==3 && color==0) //Black Pawn
          drawRect(CurrentSquare,qRgb(177,235,167),5);
        if (type==3 && color==1) //White Pawn
          drawRect(CurrentSquare,qRgb(250,192,192),5);
      }
    }
  }

  
  drawAttack(CurrentAttack);

  sendImage(*image);
}

void ImageProcessor::getProjections(RectArea rect, std::vector<int> &HP, std::vector<int> &VP) {
  HP.clear();
  VP.clear();

  int Hrgb=0;
  int Vrgb=0;

  for(int i=0;i<rect.width;i++){
    Hrgb=0;
    for(int j=0;j<rect.height;j++) {
      Hrgb+=qGray(image->pixel(i+rect.x,j+rect.y));
    }
    HP.push_back(Hrgb/rect.height);
  }


  for(int i=0;i<rect.height;i++){
    Vrgb=0;
    for(int j=0;j<rect.width;j++) {
      Vrgb+=qGray(image->pixel(j+rect.x,i+rect.y));
    }
    VP.push_back(Vrgb/rect.width);
  }
}

RectArea ImageProcessor::findSquare(int x, int y) {
  const int line_size=2;
  int square_size=(ChessArea.height-18)/8;
  return RectArea(ChessArea.x+x*(square_size+line_size)+line_size,
                    ChessArea.y+y*(square_size+line_size)+line_size,
                    square_size+1,square_size+1);
}

void ImageProcessor::drawRect(RectArea rect, int Color, int Bold) {
  for(int j=0;j<Bold;j++) {
    for(int i=rect.x;i<rect.x+rect.width;i++) {
      image->setPixel(i,rect.y,Color);
      image->setPixel(i,rect.y+rect.height-1,Color);
    }
  
    for(int i=rect.y;i<rect.y+rect.height;i++) {
      image->setPixel(rect.x,i,Color);
      image->setPixel(rect.x+rect.width-1,i,Color);
    }
    rect.x++;
    rect.y++;
    rect.width-=2;
    rect.height-=2;
  }
}

QImage ImageProcessor::proceed(int Debug) {

  DebugMode=Debug;

  std::vector<std::vector<PieceSquare> >
      ChessDesk(8,std::vector<PieceSquare>(8));

  for(int i=0;i<8;i++) {
    for(int j=0;j<8;j++) {
      ChessDesk[i][j].Type=0;
      ChessDesk[i][j].Color=0;
      ChessDesk[i][j].IsAttacked=0;
    }
  }

  ChessArea=findDesk();
  drawRect(ChessArea);

  findPieces(ChessDesk);

  return *image;
}

RectArea::RectArea(void) {
  x=0;
  y=0;
  width=0;
  height=0;
}

RectArea::RectArea(int xf, int yf, int widthf, int heightf) {
  x=xf;
  y=yf;
  width=widthf;
  height=heightf;
}

void ImageProcessor::filterAutoContrast(RectArea rect, QImage& img,
                                        int minGray, int maxGray) {

  for(int i=0;i<rect.width-1;i++) {
    for(int j=0;j<rect.height-1;j++) {
      int current=255/(maxGray-minGray)*
          (qGray(img.pixel(i+rect.x,j+rect.y))-minGray);
      if (current>255) current=maxGray;
      img.setPixel(i+rect.x,
                      j+rect.y,
                      current*0x010101);
    }
  }
  if (DebugMode) {
    sendImage(*image);
    writeLog(QString(tr("Autocontrast")));
  }
}

void ImageProcessor::filterMedian(RectArea rect, QImage& img) {

  std::vector<std::vector<kaverage> > vsquare (rect.width,std::vector<kaverage>(
                                               rect.height));
  int average;

  for(int i=0;i<rect.width;i++) {
    for(int j=0; j<rect.height;j++) {
      vsquare[i][j].Gray=qGray(img.pixel(i+rect.x,j+rect.y));
      vsquare[i][j].k=0;
      average+=vsquare[i][j].Gray;
    }
  }
  average=average/(rect.width*rect.height);
  
  std::vector<int> arr;

  for(int i=2;i<rect.width-2;i++) {
    for(int j=2; j<rect.height-2;j++) {
      arr.clear();
      for (int k=-2; k<=2; k++) {
        for (int l=-2; l<=2; l++) {
          if(abs(k*k+l*l)<2)
            arr.push_back(vsquare[i+k][j+l].Gray);
        }
      }
      std::sort(&arr[0], &arr[arr.size()]);
      img.setPixel(i+rect.x,j+rect.y,arr[
           // 0
          arr.size()/2
              ]*0x010101);
        //qApp->processEvents();
    }
  }
  if (DebugMode) {
    sendImage(*image);
    writeLog(QString(tr("MedianFilter")));
  }

}

void ImageProcessor::filterAverage(RectArea rect, QImage& img) {

  std::vector<std::vector<kaverage> > vsquare (rect.width,std::vector<kaverage>(
                                               rect.height));
  int average;

  for(int i=0;i<rect.width;i++) {
    for(int j=0; j<rect.height;j++) {
      vsquare[i][j].Gray=qGray(img.pixel(i+rect.x,j+rect.y));
      vsquare[i][j].k=0;
      average+=vsquare[i][j].Gray;
    }
  }
  average=average/(rect.width*rect.height);
  
  std::vector<int> arr;

  for(int i=2;i<rect.width-2;i++) {
    for(int j=2; j<rect.height-2;j++) {
      arr.clear();
      for (int k=-2; k<=2; k++) {
        for (int l=-2; l<=2; l++) {
          if(abs(k*k+l*l)<2)
            arr.push_back(vsquare[i+k][j+l].Gray);
        }
      }
      int avrg=0;
      for(int m=0;(static_cast<unsigned int>(m))<arr.size();m++) {
        avrg+=arr[m];
      }
      avrg/=arr.size();
      img.setPixel(i+rect.x,j+rect.y,avrg*0x010101);
        //qApp->processEvents();
    }
  }
  if (DebugMode) {
    sendImage(*image);
    writeLog(QString(tr("AverageFilter")));
  }

}


void ImageProcessor::approximateBorder(RectArea rect, QImage& img) {

  for(int i=0;i<rect.width-1;i++) {
    for(int j=0; j<rect.height-1;j++) {
      if ((abs(i-0)<=2) ||
           (abs(j-0)<=2) ||
           (abs(i-rect.width)<=2) ||
           (abs(j-rect.height)<=2) 
         ) {
        img.setPixel(i+rect.x,j+rect.y,0x000000);
      }
    }
  }
  if (DebugMode) {
    sendImage(*image);
    writeLog(QString(tr("Drawing black borders")));
  }
}

void ImageProcessor::filterErosion(RectArea rect, QImage& img) {

  std::vector<std::vector<kaverage> > vsquare (rect.width,std::vector<kaverage>(
                                               rect.height));
  int average;

  for(int i=0;i<rect.width;i++) {
    for(int j=0; j<rect.height;j++) {
      vsquare[i][j].Gray=qGray(img.pixel(i+rect.x,j+rect.y));
      vsquare[i][j].k=0;
      average+=vsquare[i][j].Gray;
    }
  }
  average=average/(rect.width*rect.height);

  for(int i=2;i<rect.width-2;i++) {
    for(int j=2; j<rect.height-2;j++) {
      for (int k=-1; k<=1; k++) {
        for (int l=-1; l<=1; l++) {
          if ((abs(k)+abs(l))<2) 
            if (!vsquare[i+k][j+l].Gray) {
            img.setPixel(i+rect.x,j+rect.y,0x000000);
            break;
          }
          if (!vsquare[i+k][j+l].Gray) break;
        }
      }
    //  img.setPixel(i+rect.x,j+rect.y,arr[
           // 0
      //    arr.size()/2
     //         ]*0x010101);
    }
  }
  if (DebugMode) {
    sendImage(*image);
    writeLog(QString(tr("Erosion")));
  }
}

void ImageProcessor::filterDilation(RectArea rect, QImage& img) {

  std::vector<std::vector<kaverage> > vsquare (rect.width,std::vector<kaverage>(
                                               rect.height));
  int average;

  for(int i=0;i<rect.width;i++) {
    for(int j=0; j<rect.height;j++) {
      vsquare[i][j].Gray=qGray(img.pixel(i+rect.x,j+rect.y));
      vsquare[i][j].k=0;
      average+=vsquare[i][j].Gray;
    }
  }
  average=average/(rect.width*rect.height);

  for(int i=2;i<rect.width-2;i++) {
    for(int j=2; j<rect.height-2;j++) {
      for (int k=-1; k<=1; k++) {
        for (int l=-1; l<=1; l++) {
        if ((abs(k)+abs(l))<2) 
          if (vsquare[i+k][j+l].Gray) {
            img.setPixel(i+rect.x,j+rect.y,0xffffff);
            break;
          }
          if (vsquare[i+k][j+l].Gray) break;
        }
      }
    //  img.setPixel(i+rect.x,j+rect.y,arr[
           // 0
      //    arr.size()/2
     //         ]*0x010101);
    }
  }
  if (DebugMode) {
    sendImage(*image);
    writeLog(QString(tr("Dilation")));
  }
}

void ImageProcessor::filterFigure(RectArea rect, QImage& img) {


  std::vector<std::vector<kaverage> > vsquare (rect.width,std::vector<kaverage>(
                                               rect.height));
  int average;

  for(int i=0;i<rect.width;i++) {
    for(int j=0; j<rect.height;j++) {
      vsquare[i][j].Gray=qGray(img.pixel(i+rect.x,j+rect.y));
      vsquare[i][j].k=0;
      average+=vsquare[i][j].Gray;
    }
  }
  average=average/(rect.width*rect.height);

  int CurrentLabelNumber=0;

  for(int i=1;i<rect.width-1;i++) {
    for(int j=1; j<rect.height-1;j++) {

      if (vsquare[i][j].Gray) {
        if(!vsquare[i-1][j].k && !vsquare[i][j-1].k) {
          CurrentLabelNumber++;
          vsquare[i][j].k=CurrentLabelNumber;
        }

        else if ((!vsquare[i-1][j].k && vsquare[i][j-1].k) ||
                  (vsquare[i-1][j].k && !vsquare[i][j-1].k)) {
          if (vsquare[i-1][j].k) {vsquare[i][j].k=vsquare[i-1][j].k;}
          if (vsquare[i][j-1].k) {vsquare[i][j].k=vsquare[i][j-1].k;}
        }

        else if (vsquare[i-1][j].k && vsquare[i][j-1].k) {
          if (vsquare[i-1][j].k == vsquare[i][j-1].k){
            vsquare[i][j].k=vsquare[i][j-1].k;
          }
          else {
            int tmpLabel=vsquare[i-1][j].k;
            vsquare[i][j].k=vsquare[i][j-1].k;
            for(int m=1;m<rect.width-1;m++) {
              for(int l=1; l<rect.height-1;l++) {
                if (vsquare[m][l].k==tmpLabel) {
                  vsquare[m][l].k=vsquare[i][j-1].k;
                }
              }
            }
          }
        }
      }

    }
  }

  std::vector<int> GkArea(CurrentLabelNumber+1,0);

  for(int i=1;i<rect.width-1;i++) {
    for(int j=1; j<rect.height-1;j++) {
      if (vsquare[i][j].k!=0) GkArea[vsquare[i][j].k]++;
    }
  }

  int MaxK=0;
  int ThisK=0;

  for (int i=1; (static_cast<unsigned int>(i))<GkArea.size(); i++) {
     if (GkArea[i]>MaxK) {
       MaxK=GkArea[i];
       ThisK=i;
     }
  }

  for(int i=1;i<rect.width-1;i++) {
    for(int j=1; j<rect.height-1;j++) {
      if (vsquare[i][j].k!=ThisK) {vsquare[i][j].k=0;}
            else
            if (GkArea[vsquare[i][j].k]<100) {vsquare[i][j].k=0;}
    }
  }

  for(int i=1;i<rect.width-1;i++) {
    for(int j=1; j<rect.height-1;j++) {
      img.setPixel(rect.x+i,rect.y+j,vsquare[i][j].k?0xffffff:0x000000
                   //0xffffff*vsquare[i][j].k/(CurrentLabelNumber+2)
                  );
    }
  }
  if (DebugMode) {
    sendImage(*image);
    writeLog(QString(tr("Finding compact spaces.")));
  }
}




void ImageProcessor::recognizePiece(RectArea rect, QImage& img, PieceSquare &ChessDeskPiece) {
  

  std::vector<std::vector<kaverage> > vsquare (rect.width,std::vector<kaverage>(
                                               rect.height));
  int average;
  int NumOfPixels=0;

  int HasPiece=0;
  for(int i=1;i<rect.width-1;i++) {
    for(int j=1; j<rect.height-1;j++) {
      vsquare[i][j].Gray=qGray(img.pixel(i+rect.x,j+rect.y));
      if (vsquare[i][j].Gray) NumOfPixels++;
      if (vsquare[i][j].Gray && !HasPiece) HasPiece=1;
      vsquare[i][j].k=0;
      average+=vsquare[i][j].Gray;
    }
  }
  average=average/(rect.width*rect.height);

  if (HasPiece) {
    double Elongation=0;
    double Compaction=0;

    int Perimeter=0;
    int VolumeArea=0;

    for(int i=1;i<rect.width-1;i++) {
      for(int j=1; j<rect.height-1;j++) {
        if (vsquare[i][j].Gray) {
          VolumeArea++;
          if (!vsquare[i+1][j+1].Gray ||
              !vsquare[i+1][j].Gray ||
              !vsquare[i+1][j-1].Gray ||
              !vsquare[i][j+1].Gray ||
              !vsquare[i][j-1].Gray ||
              !vsquare[i-1][j+1].Gray ||
              !vsquare[i-1][j].Gray ||
              !vsquare[i-1][j-1].Gray) {
            Perimeter++;
              }
        }
      }
    }
    
    Compaction=static_cast<double>(Perimeter*Perimeter)/VolumeArea;
    //writeLog(QString("Perimeter %1 \n Square %2").arg(Perimeter).arg(VolumeArea));

    writeLog(QString("Compact %3").arg(Compaction));

    int XCenterMass=0;
    int YCenterMass=0;
    
    for(int i=1;i<rect.width-1;i++) {
      for(int j=1; j<rect.height-1;j++) {
        if (vsquare[i][j].Gray) {
          XCenterMass+=i;
          YCenterMass+=j;
        }
      }
    }
    XCenterMass/=NumOfPixels;
    YCenterMass/=NumOfPixels;
    //writeLog(QString("XCenterMass %1 YCenterMass %2").arg(XCenterMass).arg(YCenterMass));

    double m02=0;
    double m20=0;
    double m11=0;
    
    for(int i=1;i<rect.width-1;i++) {
      for(int j=1; j<rect.height-1;j++) {
        if (vsquare[i][j].Gray) {
          m02+=(YCenterMass-j)*(YCenterMass -j);
          m20+=(XCenterMass-i)*(XCenterMass -i);
          m11+=(i-XCenterMass)*(j-YCenterMass);
        }
      }
    }
    Elongation=(m20+m02+sqrt((m20-m02)*(m20-m02)+4*m11*m11))/
               (m20+m02-sqrt((m20-m02)*(m20-m02)+4*m11*m11));
    writeLog(QString("Elongation %1 \n").arg(Elongation));

    if (Elongation>2) {
      ChessDeskPiece.Type=3; // Pawn
    } else {
        if (Compaction>50) {
          ChessDeskPiece.Type=2; //Queen
      } else {
          ChessDeskPiece.Type=1; //King
      }
    }


  } else {
    ChessDeskPiece.Type=0;
  }
  if (DebugMode) {
    sendImage(*image);
    writeLog(QString(tr("Piece recognition")));
  }
}


CheckMatePosition ImageProcessor::checkPosition(std::vector<std::vector<PieceSquare> > &ChessDesk) {

  CheckMatePosition CurrentCheckMate;
  
  
  for(int i=0;i<8;i++) {
    for(int j=0;j<8;j++) {
      if (ChessDesk[i][j].Type==1) {
        if (ChessDesk[i][j].Color==0) {
          CurrentCheckMate.BlackKingX=i;
          CurrentCheckMate.BlackKingY=j;
          CurrentCheckMate.WhiteAttackerX=-1;
          CurrentCheckMate.WhiteAttackerY=-1;
          CurrentCheckMate.EscapeX=-1;
          CurrentCheckMate.EscapeY=-1;
        }
      }
    }
  }

  for(int i=0;i<8;i++) {
    for(int j=0;j<8;j++) {
      if (ChessDesk[i][j].Type) {
        if (ChessDesk[i][j].Color) {
          if (ChessDesk[i][j].Type==1) { // King
            for (int k=-1;k<=1;k++) {
              for (int l=-1;l<=1;l++) {
                if (k==0 && l==0) continue;
                if ((i+k)>=0 && (i+k)<8 && (j+l)>=0 && (j+k)<8) {
                  ChessDesk[i+k][j+l].IsAttacked=1;
                }
              }
            }
          }
          if (ChessDesk[i][j].Type==2) { // Queen
            for (int k=0;k<8;k++) {
              ChessDesk[k][j].IsAttacked=1;
              ChessDesk[i][k].IsAttacked=1;
              if ((i+k)<8 && (j+k)<8) ChessDesk[i+k][j+k].IsAttacked=1;
              if ((i-k)>=0 && (j+k)<8) ChessDesk[i-k][j+k].IsAttacked=1;
              if ((i+k)<8 && (j-k)>=0) ChessDesk[i+k][j-k].IsAttacked=1;
              if ((i-k)>=0 && (j-k)>=0) ChessDesk[i-k][j-k].IsAttacked=1;
            }
          }
          if (ChessDesk[i][j].Type==3) { // Pawn
            if (i<7 && j>0) ChessDesk[i+1][j-1].IsAttacked=1;
            if (i>0 && j>0) ChessDesk[i-1][j-1].IsAttacked=1;
          }
          ChessDesk[i][j].IsAttacked=1;
          if (ChessDesk[CurrentCheckMate.BlackKingX][CurrentCheckMate.BlackKingY].IsAttacked 
              && CurrentCheckMate.WhiteAttackerX==-1
              && CurrentCheckMate.WhiteAttackerY==-1
             ) {
            CurrentCheckMate.WhiteAttackerX=i;
            CurrentCheckMate.WhiteAttackerY=j;
          }
        }
      }
    }
  }
  int IsChecked=0;
  int CanMove=0;
  int WhereCantToGo=0;
  for(int i=0;i<8;i++) {
    for(int j=0;j<8;j++) {
      if (ChessDesk[i][j].Type==1) {
        if (ChessDesk[i][j].Color==0) {
          if (ChessDesk[i][j].IsAttacked) IsChecked=1;
          for (int k=-1;k<=1;k++) {
            for (int l=-1;l<=1;l++) {
              if (k==0 && l==0) continue;
              if ((i+k)>=0 && (i+k)<8 && (j+l)>=0 && (j+k)<8) {
                if (ChessDesk[i+k][j+l].IsAttacked || ChessDesk[i+k][j+l].Type) {
                  WhereCantToGo++;
                }
                else {
                  CurrentCheckMate.EscapeX=i+k;
                  CurrentCheckMate.EscapeY=j+l;
                }
              } else {WhereCantToGo++;}
            }
          }
        }
      }
    }
  }
  writeLog(QString("Black king can't to go to %1 squares.\n").arg(WhereCantToGo));
  if (WhereCantToGo==8) {CanMove=0;} else {CanMove=1;}
  if (CanMove && !IsChecked) writeLog(QString("USIAL\n"));
  if (CanMove && IsChecked) writeLog(QString("CHECK\n"));
  if (!CanMove && !IsChecked) writeLog(QString("STALEMATE\n"));
  if (!CanMove && IsChecked) writeLog(QString("CHECKMATE\n"));

  return CurrentCheckMate;
}


void ImageProcessor::drawAttack(CheckMatePosition position) {
  QPainter painter(image);
  RectArea BlackKing=findSquare(position.BlackKingX,position.BlackKingY);
  if (position.WhiteAttackerX!=-1) {
    RectArea WhiteAttacker=findSquare(position.WhiteAttackerX,position.WhiteAttackerY);
    painter.setPen(QPen(QBrush(0xff0000),5));
    painter.drawLine(BlackKing.x+BlackKing.width/2, BlackKing.y+BlackKing.height/2,
                   WhiteAttacker.x+WhiteAttacker.width/2,WhiteAttacker.y+WhiteAttacker.height/2);
  }
  
  if (position.EscapeX!=-1) {
    RectArea Escape=findSquare(position.EscapeX,position.EscapeY);
    painter.setPen(QPen(QBrush(0x00ff00),5));
    painter.drawLine(BlackKing.x+BlackKing.width/2, BlackKing.y+BlackKing.height/2,
                    Escape.x+Escape.width/2,Escape.y+Escape.height/2);
  }
  painter.end();
}


