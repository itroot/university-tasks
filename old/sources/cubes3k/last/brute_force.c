#include <stdio.h>
#include <stdlib.h>

unsigned int externalFaces[24][9];
unsigned int internalFaces[12][9];
unsigned int cubes[64];
unsigned long long int matrix[9][6];

enum TypeOfTriangulation {
  T_0440=0, // Неправильный тип, все остальные правильные.
  T_0602=1,
  T_1331=2,
  T_2060=3,
  T_2222=4,
  T_4004=5
};

void initFaces() {
  externalFaces[0][0]=1;
  externalFaces[0][1]=1;
  externalFaces[0][2]=0;
  externalFaces[0][3]=0;
  externalFaces[0][4]=0;
  externalFaces[0][5]=0;
  externalFaces[0][6]=0;
  externalFaces[0][7]=0;
  externalFaces[0][8]=0;

  externalFaces[1][0]=2;
  externalFaces[1][1]=0;
  externalFaces[1][2]=0;
  externalFaces[1][3]=1;
  externalFaces[1][4]=0;
  externalFaces[1][5]=0;
  externalFaces[1][6]=0;
  externalFaces[1][7]=0;
  externalFaces[1][8]=0;

  externalFaces[2][0]=4;
  externalFaces[2][1]=0;
  externalFaces[2][2]=1;
  externalFaces[2][3]=0;
  externalFaces[2][4]=0;
  externalFaces[2][5]=0;
  externalFaces[2][6]=0;
  externalFaces[2][7]=0;
  externalFaces[2][8]=0;

  externalFaces[3][0]=8;
  externalFaces[3][1]=0;
  externalFaces[3][2]=0;
  externalFaces[3][3]=0;
  externalFaces[3][4]=1;
  externalFaces[3][5]=0;
  externalFaces[3][6]=0;
  externalFaces[3][7]=0;
  externalFaces[3][8]=0;

  externalFaces[4][0]=16;
  externalFaces[4][1]=2;
  externalFaces[4][2]=0;
  externalFaces[4][3]=0;
  externalFaces[4][4]=0;
  externalFaces[4][5]=0;
  externalFaces[4][6]=0;
  externalFaces[4][7]=0;
  externalFaces[4][8]=0;

  externalFaces[5][0]=32;
  externalFaces[5][1]=0;
  externalFaces[5][2]=0;
  externalFaces[5][3]=0;
  externalFaces[5][4]=0;
  externalFaces[5][5]=2;
  externalFaces[5][6]=0;
  externalFaces[5][7]=0;
  externalFaces[5][8]=0;

  externalFaces[6][0]=64;
  externalFaces[6][1]=0;
  externalFaces[6][2]=2;
  externalFaces[6][3]=0;
  externalFaces[6][4]=0;
  externalFaces[6][5]=0;
  externalFaces[6][6]=0;
  externalFaces[6][7]=0;
  externalFaces[6][8]=0;

  externalFaces[7][0]=128;
  externalFaces[7][1]=0;
  externalFaces[7][2]=0;
  externalFaces[7][3]=0;
  externalFaces[7][4]=0;
  externalFaces[7][5]=0;
  externalFaces[7][6]=2;
  externalFaces[7][7]=0;
  externalFaces[7][8]=0;

  externalFaces[8][0]=256;
  externalFaces[8][1]=4;
  externalFaces[8][2]=0;
  externalFaces[8][3]=0;
  externalFaces[8][4]=0;
  externalFaces[8][5]=0;
  externalFaces[8][6]=0;
  externalFaces[8][7]=0;
  externalFaces[8][8]=0;

  externalFaces[9][0]=512;
  externalFaces[9][1]=0;
  externalFaces[9][2]=0;
  externalFaces[9][3]=0;
  externalFaces[9][4]=0;
  externalFaces[9][5]=4;
  externalFaces[9][6]=0;
  externalFaces[9][7]=0;
  externalFaces[9][8]=0;

  externalFaces[10][0]=1024;
  externalFaces[10][1]=0;
  externalFaces[10][2]=0;
  externalFaces[10][3]=4;
  externalFaces[10][4]=0;
  externalFaces[10][5]=0;
  externalFaces[10][6]=0;
  externalFaces[10][7]=0;
  externalFaces[10][8]=0;

  externalFaces[11][0]=2048;
  externalFaces[11][1]=0;
  externalFaces[11][2]=0;
  externalFaces[11][3]=0;
  externalFaces[11][4]=0;
  externalFaces[11][5]=0;
  externalFaces[11][6]=0;
  externalFaces[11][7]=4;
  externalFaces[11][8]=0;

  externalFaces[12][0]=4096;
  externalFaces[12][1]=0;
  externalFaces[12][2]=0;
  externalFaces[12][3]=0;
  externalFaces[12][4]=0;
  externalFaces[12][5]=8;
  externalFaces[12][6]=0;
  externalFaces[12][7]=0;
  externalFaces[12][8]=0;

  externalFaces[13][0]=8192;
  externalFaces[13][1]=0;
  externalFaces[13][2]=0;
  externalFaces[13][3]=0;
  externalFaces[13][4]=0;
  externalFaces[13][5]=0;
  externalFaces[13][6]=0;
  externalFaces[13][7]=8;
  externalFaces[13][8]=0;

  externalFaces[14][0]=16384;
  externalFaces[14][1]=0;
  externalFaces[14][2]=0;
  externalFaces[14][3]=0;
  externalFaces[14][4]=0;
  externalFaces[14][5]=0;
  externalFaces[14][6]=8;
  externalFaces[14][7]=0;
  externalFaces[14][8]=0;

  externalFaces[15][0]=32768;
  externalFaces[15][1]=0;
  externalFaces[15][2]=0;
  externalFaces[15][3]=0;
  externalFaces[15][4]=0;
  externalFaces[15][5]=0;
  externalFaces[15][6]=0;
  externalFaces[15][7]=0;
  externalFaces[15][8]=8;

  externalFaces[16][0]=65536;
  externalFaces[16][1]=0;
  externalFaces[16][2]=0;
  externalFaces[16][3]=16;
  externalFaces[16][4]=0;
  externalFaces[16][5]=0;
  externalFaces[16][6]=0;
  externalFaces[16][7]=0;
  externalFaces[16][8]=0;

  externalFaces[17][0]=131072;
  externalFaces[17][1]=0;
  externalFaces[17][2]=0;
  externalFaces[17][3]=0;
  externalFaces[17][4]=0;
  externalFaces[17][5]=0;
  externalFaces[17][6]=0;
  externalFaces[17][7]=16;
  externalFaces[17][8]=0;

  externalFaces[18][0]=262144;
  externalFaces[18][1]=0;
  externalFaces[18][2]=0;
  externalFaces[18][3]=0;
  externalFaces[18][4]=16;
  externalFaces[18][5]=0;
  externalFaces[18][6]=0;
  externalFaces[18][7]=0;
  externalFaces[18][8]=0;

  externalFaces[19][0]=524288;
  externalFaces[19][1]=0;
  externalFaces[19][2]=0;
  externalFaces[19][3]=0;
  externalFaces[19][4]=0;
  externalFaces[19][5]=0;
  externalFaces[19][6]=0;
  externalFaces[19][7]=0;
  externalFaces[19][8]=16;

  externalFaces[20][0]=1048576;
  externalFaces[20][1]=0;
  externalFaces[20][2]=32;
  externalFaces[20][3]=0;
  externalFaces[20][4]=0;
  externalFaces[20][5]=0;
  externalFaces[20][6]=0;
  externalFaces[20][7]=0;
  externalFaces[20][8]=0;

  externalFaces[21][0]=2097152;
  externalFaces[21][1]=0;
  externalFaces[21][2]=0;
  externalFaces[21][3]=0;
  externalFaces[21][4]=0;
  externalFaces[21][5]=0;
  externalFaces[21][6]=32;
  externalFaces[21][7]=0;
  externalFaces[21][8]=0;

  externalFaces[22][0]=4194304;
  externalFaces[22][1]=0;
  externalFaces[22][2]=0;
  externalFaces[22][3]=0;
  externalFaces[22][4]=32;
  externalFaces[22][5]=0;
  externalFaces[22][6]=0;
  externalFaces[22][7]=0;
  externalFaces[22][8]=0;

  externalFaces[23][0]=8388608;
  externalFaces[23][1]=0;
  externalFaces[23][2]=0;
  externalFaces[23][3]=0;
  externalFaces[23][4]=0;
  externalFaces[23][5]=0;
  externalFaces[23][6]=0;
  externalFaces[23][7]=0;
  externalFaces[23][8]=32;

  internalFaces[0][0]=1;
  internalFaces[0][1]=8;
  internalFaces[0][2]=0;
  internalFaces[0][3]=0;
  internalFaces[0][4]=0;
  internalFaces[0][5]=1;
  internalFaces[0][6]=0;
  internalFaces[0][7]=0;
  internalFaces[0][8]=0;

  internalFaces[1][0]=2;
  internalFaces[1][1]=0;
  internalFaces[1][2]=0;
  internalFaces[1][3]=8;
  internalFaces[1][4]=0;
  internalFaces[1][5]=0;
  internalFaces[1][6]=0;
  internalFaces[1][7]=1;
  internalFaces[1][8]=0;

  internalFaces[2][0]=4;
  internalFaces[2][1]=0;
  internalFaces[2][2]=8;
  internalFaces[2][3]=0;
  internalFaces[2][4]=0;
  internalFaces[2][5]=0;
  internalFaces[2][6]=1;
  internalFaces[2][7]=0;
  internalFaces[2][8]=0;

  internalFaces[3][0]=8;
  internalFaces[3][1]=0;
  internalFaces[3][2]=0;
  internalFaces[3][3]=0;
  internalFaces[3][4]=8;
  internalFaces[3][5]=0;
  internalFaces[3][6]=0;
  internalFaces[3][7]=0;
  internalFaces[3][8]=1;

  internalFaces[4][0]=16;
  internalFaces[4][1]=16;
  internalFaces[4][2]=0;
  internalFaces[4][3]=2;
  internalFaces[4][4]=0;
  internalFaces[4][5]=0;
  internalFaces[4][6]=0;
  internalFaces[4][7]=0;
  internalFaces[4][8]=0;

  internalFaces[5][0]=32;
  internalFaces[5][1]=0;
  internalFaces[5][2]=0;
  internalFaces[5][3]=0;
  internalFaces[5][4]=0;
  internalFaces[5][5]=16;
  internalFaces[5][6]=0;
  internalFaces[5][7]=2;
  internalFaces[5][8]=0;

  internalFaces[6][0]=64;
  internalFaces[6][1]=0;
  internalFaces[6][2]=16;
  internalFaces[6][3]=0;
  internalFaces[6][4]=2;
  internalFaces[6][5]=0;
  internalFaces[6][6]=0;
  internalFaces[6][7]=0;
  internalFaces[6][8]=0;

  internalFaces[7][0]=128;
  internalFaces[7][1]=0;
  internalFaces[7][2]=0;
  internalFaces[7][3]=0;
  internalFaces[7][4]=0;
  internalFaces[7][5]=0;
  internalFaces[7][6]=16;
  internalFaces[7][7]=0;
  internalFaces[7][8]=2;

  internalFaces[8][0]=256;
  internalFaces[8][1]=32;
  internalFaces[8][2]=4;
  internalFaces[8][3]=0;
  internalFaces[8][4]=0;
  internalFaces[8][5]=0;
  internalFaces[8][6]=0;
  internalFaces[8][7]=0;
  internalFaces[8][8]=0;

  internalFaces[9][0]=512;
  internalFaces[9][1]=0;
  internalFaces[9][2]=0;
  internalFaces[9][3]=0;
  internalFaces[9][4]=0;
  internalFaces[9][5]=32;
  internalFaces[9][6]=4;
  internalFaces[9][7]=0;
  internalFaces[9][8]=0;

  internalFaces[10][0]=1024;
  internalFaces[10][1]=0;
  internalFaces[10][2]=0;
  internalFaces[10][3]=32;
  internalFaces[10][4]=4;
  internalFaces[10][5]=0;
  internalFaces[10][6]=0;
  internalFaces[10][7]=0;
  internalFaces[10][8]=0;

  internalFaces[11][0]=2048;
  internalFaces[11][1]=0;
  internalFaces[11][2]=0;
  internalFaces[11][3]=0;
  internalFaces[11][4]=0;
  internalFaces[11][5]=0;
  internalFaces[11][6]=0;
  internalFaces[11][7]=32;
  internalFaces[11][8]=4;
}

void initCubes() {
  cubes[0]=T_2060;
  cubes[1]=T_1331;
  cubes[2]=T_1331;
  cubes[3]=T_2222;
  cubes[4]=T_1331;
  cubes[5]=T_2222;
  cubes[6]=T_2222;
  cubes[7]=T_4004;
  cubes[8]=T_1331;
  cubes[9]=T_0602;
  cubes[10]=T_0440;
  cubes[11]=T_1331;
  cubes[12]=T_0440;
  cubes[13]=T_1331;
  cubes[14]=T_0440;
  cubes[15]=T_2222;
  cubes[16]=T_1331;
  cubes[17]=T_0440;
  cubes[18]=T_0602;
  cubes[19]=T_1331;
  cubes[20]=T_0440;
  cubes[21]=T_0440;
  cubes[22]=T_1331;
  cubes[23]=T_2222;
  cubes[24]=T_2222;
  cubes[25]=T_1331;
  cubes[26]=T_1331;
  cubes[27]=T_2060;
  cubes[28]=T_0440;
  cubes[29]=T_0440;
  cubes[30]=T_0440;
  cubes[31]=T_1331;
  cubes[32]=T_1331;
  cubes[33]=T_0440;
  cubes[34]=T_0440;
  cubes[35]=T_0440;
  cubes[36]=T_0602;
  cubes[37]=T_1331;
  cubes[38]=T_1331;
  cubes[39]=T_2222;
  cubes[40]=T_2222;
  cubes[41]=T_1331;
  cubes[42]=T_0440;
  cubes[43]=T_0440;
  cubes[44]=T_1331;
  cubes[45]=T_2060;
  cubes[46]=T_0440;
  cubes[47]=T_1331;
  cubes[48]=T_2222;
  cubes[49]=T_0440;
  cubes[50]=T_1331;
  cubes[51]=T_0440;
  cubes[52]=T_1331;
  cubes[53]=T_0440;
  cubes[54]=T_2060;
  cubes[55]=T_1331;
  cubes[56]=T_4004;
  cubes[57]=T_2222;
  cubes[58]=T_2222;
  cubes[59]=T_1331;
  cubes[60]=T_2222;
  cubes[61]=T_1331;
  cubes[62]=T_1331;
  cubes[63]=T_0602;
}

void initMatrix() {
  int i=0;
  int j=0;
  for (i=0;i<9;++i) {
    for (j=0;j<6;++j) {
      matrix[i][j]=0;
    }
  }
}

void printMatrix() {
  int i=0;
  int j=0;
  for (i=0;i<9;++i) {
    for (j=0;j<6;++j) {
      printf("%lld\t",matrix[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}


int main(int argc, char * argv[]) {
  unsigned int LocalCubes[8];
  unsigned int types[6];
  int i=0;
  unsigned int i_ext=0;
  unsigned int i_int=0;

  for (i=0;i<8;++i) LocalCubes[i]=0;

  initFaces();
  initCubes();
  initMatrix();
 
  for (i_int=0;i_int<=0xfff;++i_int) {
    for ( i_ext=0;i_ext<=0xffffff;++i_ext) {
      int i=0;

      for (i=0;i<8;++i) {
        LocalCubes[i]=0;
      }

      for(i=0;i<24;++i) {
        if (i_ext&externalFaces[i][0]) {
           LocalCubes[0]|=externalFaces[i][1];
           LocalCubes[1]|=externalFaces[i][2];
           LocalCubes[2]|=externalFaces[i][3];
           LocalCubes[3]|=externalFaces[i][4];
           LocalCubes[4]|=externalFaces[i][5];
           LocalCubes[5]|=externalFaces[i][6];
           LocalCubes[6]|=externalFaces[i][7];
           LocalCubes[7]|=externalFaces[i][8];
        }
      }
      for(i=0;i<12;++i) {
        if (i_int&internalFaces[i][0]) {
           LocalCubes[0]|=internalFaces[i][1];
           LocalCubes[1]|=internalFaces[i][2];
           LocalCubes[2]|=internalFaces[i][3];
           LocalCubes[3]|=internalFaces[i][4];
           LocalCubes[4]|=internalFaces[i][5];
           LocalCubes[5]|=internalFaces[i][6];
           LocalCubes[6]|=internalFaces[i][7];
           LocalCubes[7]|=internalFaces[i][8];
        }
      }

      for (i=0;i<6;++i) {
        types[i]=0;
      }

      int ALL_OK=1;
      for (i=0;i<8;++i) {
        if (cubes[LocalCubes[i]]==T_0440) {
          ALL_OK=0;
          break;
        }
        ++types[cubes[LocalCubes[i]]];
      }
      if (!ALL_OK) continue;

        ++matrix[types[T_0602]][T_0602];
        ++matrix[types[T_1331]][T_1331];
        ++matrix[types[T_2060]][T_2060];
        ++matrix[types[T_2222]][T_2222];
        ++matrix[types[T_4004]][T_4004];

    }
    printf("i_int: %d \n",i_int);
    printMatrix();
  }

  printMatrix();
  return(0);
}
