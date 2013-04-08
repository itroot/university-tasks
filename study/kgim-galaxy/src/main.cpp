/*
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Author : Ivan Tolstosheyev, group 322 (23.09.07)
*/


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include "SDL.h"
#define GALAXY_SIZE 400
#define X_RES 640
#define Y_RES 480
#define PI 3.1415926

class Galaxy { // Father of all galaxies;
  public:
    Galaxy(void);
    void Draw(SDL_Surface *screen,SDL_Surface *back); // Drawing galaxies
    void ChangeXY(int dx,int dy);   // Change cooedinates of galaxies
    void virtual ReDraw(int dnum)=0; // Change number of ways (only for SpyralGalaxy)
    void SetColor(int Color);
  protected:
    int Stars[GALAXY_SIZE][GALAXY_SIZE]; // Array of pixels (can contain 1 or 0)
    int Way[GALAXY_SIZE][GALAXY_SIZE]; // Array of stars - used to generate Stars array
    int xpos;                            // position on x axis
    int ypos;                            // position on y axis
  private:
    int IsColored;
};
// Next 3 classes implements 3 different types of galaxies. 
class EllipticGalaxy : public Galaxy {
  public:
    void ReDraw(int dnum);
    EllipticGalaxy(void);
  private:
    int WideParam;
};

class AlmondShapedGalaxy : public Galaxy {
  public:
    void ReDraw(int dnum);
    AlmondShapedGalaxy(void);
};

class SpiralGalaxy : public Galaxy {
  public:
    SpiralGalaxy(void);
    void Draw(SDL_Surface *screen);
    void ReDraw(int dnum);
  private:
    int Way[GALAXY_SIZE][GALAXY_SIZE];
    int NumOfWays;
};

void Slock(SDL_Surface *screen); // Lock screen
void Sulock(SDL_Surface *screen);// Unlock screen
void DrawPixel(SDL_Surface *screen, int x, int y, Uint8 R, Uint8 G, Uint8 B);
void DrawScene(SDL_Surface *screen, SDL_Surface *back, Galaxy &current);


int main(int argc, char *argv[]) {
  Galaxy *milkyway=new EllipticGalaxy();

  SDL_Surface *screen; // Screen
  SDL_Surface *back;   // Background image with stars
  Uint8 *keys;         // For user interface

  if ( SDL_Init(SDL_INIT_VIDEO) < 0 ){ // Initializing SDL 
    printf("Unable to init SDL: %s\n", SDL_GetError());
    exit(1);
  }

  atexit(SDL_Quit); // Setting exit function (to exit SDL correctly)

  SDL_WM_SetCaption("1 Task","main"); // Setting window caption

  screen=SDL_SetVideoMode(X_RES,Y_RES,32,SDL_HWSURFACE|SDL_DOUBLEBUF); // Video mode
  if ( screen == NULL ){
    printf("Unable to set 640x480 video: %s\n", SDL_GetError());
    exit(1);
  }

  back=SDL_LoadBMP("back.bmp"); // Loading backgroung image
  //             Main loop
  int done=0; // exit flag
  while(done == 0){

    SDL_Event event;

    while ( SDL_PollEvent(&event) ){
      if ( event.type == SDL_QUIT ){
       done = 1; 
      }
      if ( event.type == SDL_KEYDOWN ){
        if ( event.key.keysym.sym == SDLK_ESCAPE ){
          done = 1; 
        }
      }
    }

    keys = SDL_GetKeyState(NULL); // Catching keys
    if(keys[SDLK_UP]){milkyway->ChangeXY(0,-1);}
    if(keys[SDLK_DOWN]){milkyway->ChangeXY(0,1);}
    if(keys[SDLK_LEFT]){milkyway->ChangeXY(-1,0);}
    if(keys[SDLK_RIGHT]){milkyway->ChangeXY(1,0);}
    if (keys[SDLK_1]) {delete milkyway; milkyway=new EllipticGalaxy();}
    if (keys[SDLK_2]) {delete milkyway; milkyway=new AlmondShapedGalaxy();}
    if (keys[SDLK_3]) {delete milkyway; milkyway=new SpiralGalaxy();}
    if (keys[SDLK_PAGEUP]) milkyway->ReDraw(1);
    if (keys[SDLK_PAGEDOWN]) milkyway->ReDraw(-1);
    if (keys[SDLK_4]) milkyway->SetColor(1);
    if (keys[SDLK_5]) milkyway->SetColor(0);
    DrawScene(screen,back,*milkyway);

  }
  //            End of main loop

}



void Slock(SDL_Surface *screen) {

  if ( SDL_MUSTLOCK(screen) ){ 
    if ( SDL_LockSurface(screen) < 0 ){ 
      return; 
    } 
  } 

} 


void Sulock(SDL_Surface *screen) {

  if ( SDL_MUSTLOCK(screen) ){ 
    SDL_UnlockSurface(screen); 
  } 

} 


void DrawPixel(SDL_Surface *screen, int x, int y, Uint8 R, Uint8 G, Uint8 B) {

  Uint32 color = SDL_MapRGB(screen->format, R, G, B);
  switch (screen->format->BytesPerPixel){
    case 1:  // Assuming 8-bpp 
    {
      Uint8 *bufp;
      bufp = (Uint8 *)screen->pixels + y*screen->pitch + x; *bufp = color;
    } break;
    case 2: // Probably 15-bpp or 16-bpp 
    { 
      Uint16 *bufp; 
      bufp = (Uint16 *)screen->pixels + y*screen->pitch/2 + x; *bufp = color; 
    } break; 
    case 3: // Slow 24-bpp mode, usually not used 
    { 
      Uint8 *bufp; 
      bufp = (Uint8 *)screen->pixels + y*screen->pitch + x * 3; 
      if(SDL_BYTEORDER == SDL_LIL_ENDIAN){ 
        bufp[0] = color; 
        bufp[1] = color >> 8; 
        bufp[2] = color >> 16; 
      }else{ 
        bufp[2] = color; 
        bufp[1] = color >> 8; 
        bufp[0] = color >> 16; 
      } 
    } break; 
    case 4: // Probably 32-bpp 
    { 
      Uint32 *bufp; 
      bufp = (Uint32 *)screen->pixels + y*screen->pitch/4 + x; 
      *bufp = color; 
    } break; 
  } 
} 

Uint32 GetPixel(SDL_Surface *surface, int x, int y) {
  int bpp = surface->format->BytesPerPixel;
  Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

  switch(bpp) {
    case 1:
      return *p;

    case 2:
      return *(Uint16 *)p;

    case 3:
      if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
        return p[0] << 16 | p[1] << 8 | p[2];
      else
        return p[0] | p[1] << 8 | p[2] << 16;

    case 4:
      return *(Uint32 *)p;

    default:
      return 0;
  }
}

void DrawScene(SDL_Surface *screen, SDL_Surface *back, Galaxy &current) {
  SDL_Rect BackRect;

  BackRect.x=0;
  BackRect.y=0;

  Slock(screen);
  SDL_BlitSurface(back, NULL, screen, &BackRect);
  current.Draw(screen,back);
  Sulock(screen); 
  SDL_Flip(screen);
}




void Galaxy::Draw(SDL_Surface * screen, SDL_Surface* back) {
  for(int i=0;i<GALAXY_SIZE;i++){
    for(int j=0;j<GALAXY_SIZE;j++) {
      Uint8 r,g,b;
      SDL_GetRGB(GetPixel(back,i+xpos,j+ypos),back->format,&r,&g,&b);
      int distance = static_cast<int>(sqrt(pow(i-GALAXY_SIZE/2,2)+pow(j-GALAXY_SIZE/2,2)));
      if (distance>255) distance=255;
      if (Stars[i][j]) 
        if (IsColored) {
          DrawPixel(screen,xpos+i,ypos+j,
                    ((255-distance)*(255-distance)+r*distance)/255,
                     ((255-distance)*(255-distance)+g*distance)/255,
                      ((255-distance/2)*(255-distance)+b*distance)/255);
        } else
        {
          DrawPixel(screen,xpos+i,ypos+j,
                    (255*(255-distance)+r*distance)/255,
                    (255*(255-distance)+g*distance)/255,
                    (255*(255-distance)+b*distance)/255);
        }
    }
  }
}

void Galaxy::SetColor(int Color) {
  if (Color==1) IsColored=1;
  if (Color==0) IsColored=0;
}


void Galaxy::ChangeXY(int dx,int dy) {
  if (
      ((xpos+dx)>0) && ((xpos+dx)<X_RES-GALAXY_SIZE) &&
      ((ypos+dy)>0) && ((ypos+dy)<Y_RES-GALAXY_SIZE)
     ) {
  xpos+=dx;
  ypos+=dy;
     }
}



Galaxy::Galaxy(void) {
  IsColored=1;
  xpos=X_RES/2-GALAXY_SIZE/2; // Position of the
  ypos=Y_RES/2-GALAXY_SIZE/2; // current galaxy
  for(int i=0;i<GALAXY_SIZE;i++)
    for(int j=0;j<GALAXY_SIZE;j++) Stars[i][j]=0;
}




EllipticGalaxy::EllipticGalaxy(void) {
  WideParam=100; // This parameter is show how "wide" is elliptic galaxy
  for(int i=0;i<GALAXY_SIZE;i++){
    for(int j=0;j<GALAXY_SIZE;j++) {
      if (exp(
          -pow(
               pow(i-GALAXY_SIZE/2,2)+
          pow(j-GALAXY_SIZE/2,2)
          ,2)/
          pow(GALAXY_SIZE,3)
             )
          >=((static_cast<double>(rand()))/RAND_MAX)) {
        Way[i][j]=1;
          } else {
            Way[i][j]=0;
          }
    }
  }
  ReDraw(0);
}

void EllipticGalaxy::ReDraw(int dnum) {
  if (dnum==0) {
    for(int i=0;i<GALAXY_SIZE;i++)
      for(int j=0;j<GALAXY_SIZE;j++)
        Stars[i][j]=Way[i][j];
  } else {
    if (((WideParam+dnum)>50) && ((WideParam+dnum)<=100)) WideParam+=dnum;
    for(int i=0;i<GALAXY_SIZE;i++)
      for(int j=0;j<GALAXY_SIZE;j++) {
      Stars[i][j]=Way[static_cast<int>((i-GALAXY_SIZE/2)*WideParam/100.+GALAXY_SIZE/2)]
                  [static_cast<int>((j-GALAXY_SIZE/2)*WideParam/100.+GALAXY_SIZE/2)];
      }
  }
};

AlmondShapedGalaxy::AlmondShapedGalaxy(void) {
  const int a_almond=20;
  const int b_almond=50;
  for(int i=0;i<GALAXY_SIZE;i++){
    for(int j=0;j<GALAXY_SIZE;j++) {
      if ((exp(
           -pow(pow(i-GALAXY_SIZE/2,2)/pow(a_almond,2)+
           pow(j-GALAXY_SIZE/2,2)/pow(b_almond,2),1))
          ) >= ((static_cast<double>(rand()))/RAND_MAX)) {
        Stars[i][j]=1;
          } else {
            Stars[i][j]=0;
          }
    }
  }

}

void AlmondShapedGalaxy::ReDraw(int dnum) {};

SpiralGalaxy::SpiralGalaxy(void) {
  NumOfWays=8;
  const int width=30;
  const int length=70000;
  for(int i=0;i<GALAXY_SIZE;i++){
    for(int j=0;j<GALAXY_SIZE;j++) {
      if ((exp(-pow(abs(i-GALAXY_SIZE/2),5)/pow(length,2))*exp(-pow(abs(j-GALAXY_SIZE/2),5)/pow(width,2))
          ) >= ((static_cast<double>(rand()))/RAND_MAX)) {
        if (i>GALAXY_SIZE/2) Way[i][j]=1; // Cutting galaxy way
          }
    }
  }
  ReDraw(0);
}


void SpiralGalaxy::ReDraw(int dnum) {
  if (((NumOfWays+dnum)>0)&&((NumOfWays+dnum)<17)) NumOfWays+=dnum; else return;
  for(int i=0;i<GALAXY_SIZE;i++){
    for(int j=0;j<GALAXY_SIZE;j++) {
      Stars[i][j]=0;
      double d=pow(sqrt(pow(abs(i-GALAXY_SIZE/2),2)+pow(abs(j-GALAXY_SIZE/2),2)),1.4);
      for (int TempAngle=0; TempAngle<NumOfWays;TempAngle++) {
        if (Way[i][j])
          Stars[
              static_cast<int>(((i-GALAXY_SIZE/2)*sin(PI*.5*GALAXY_SIZE/d+2*PI/NumOfWays*TempAngle))+
              ((j-GALAXY_SIZE/2)*cos(PI*.5*GALAXY_SIZE/d+2*PI/NumOfWays*TempAngle))+GALAXY_SIZE/2)]
              [
              static_cast<int>(((i-GALAXY_SIZE/2)*cos(PI*.5*GALAXY_SIZE/d+2*PI/NumOfWays*TempAngle))+
              ((j-GALAXY_SIZE/2)*sin(PI*.5*GALAXY_SIZE/d+2*PI/NumOfWays*TempAngle))+GALAXY_SIZE/2)]=1;
      }
    }
  }
}
