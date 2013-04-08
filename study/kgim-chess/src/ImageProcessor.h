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


#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QObject>
#include <vector>




class QImage;

struct CheckMatePosition {
  int BlackKingX;
  int BlackKingY;
  int WhiteAttackerX;
  int WhiteAttackerY;
  int EscapeX;
  int EscapeY;
};


struct kaverage {
  int Gray;
  int k;
};

struct RectArea {
  RectArea(void);
  RectArea(int xf,int yf,int widthf, int heightf);
  int x;
  int y;
  int width;
  int height;
};

 /*! 
  * This structure is implements a square of a virtual board.
  *  It is used to decide where on the desk attcked squares
  *  and is there a CHECK, STALEMATE or CHECKMATE.
  */
struct PieceSquare {
  //! Type of the figure. 0 - Nothing, 1 - King ,2 - Queen, 3 - Pawn
  int Type;
  //! white or black - color of Piece(if it exist)
  int Color;
  //! 1 if this square is attected by white piece, 0 if not
  int IsAttacked;
};

/*!
 * This is main class for image processing. It do all operation needed to
 * found desk on picture, binarize, etc.
 */
class ImageProcessor : public QObject {
  Q_OBJECT

  public:
    ImageProcessor(void);
    ImageProcessor(QImage SourceImage);
    void setImage(QImage SourceImage);
    QImage proceed(int Debug=0);


  signals:
    void sendLogMessage(QString Message, int IsError);
    void sendImage(QImage& Image);

  private:
    QImage *image;
    QImage *source;
    RectArea ChessArea;
    int DebugMode;


    //! used for logging
    void writeLog(QString Message, int IsError=0);
    //! finds desk on image
    RectArea findDesk(void);
    //! This function process image and then finds pieces on the board.
    void findPieces(std::vector<std::vector<PieceSquare> > &ChessDesk);
    RectArea findSquare(int x, int y);
    void drawRect(RectArea rect, int Color=0xff0000,int Bold=1);
    void drawAttack(CheckMatePosition position);
    void getProjections(RectArea rect, std::vector<int> &HP, std::vector<int> &VP);
    void filterAutoContrast(RectArea rect, QImage& rect, int minGray, int maxGray);
    void filterMedian(RectArea rect, QImage& img);
    void filterAverage(RectArea rect, QImage& img);
    void approximateBorder(RectArea rect, QImage& img);
    void filterErosion(RectArea rect, QImage& img);
    void filterDilation(RectArea rect, QImage& img);
    void filterFigure(RectArea rect, QImage& img);
    void recognizePiece(RectArea rect, QImage& img, PieceSquare &ChessDeskPiece);
    CheckMatePosition checkPosition(std::vector<std::vector<PieceSquare> > &ChessDesk);

};


#endif
