#include "Etc.h"

unsigned int static_ext_faces=0;
unsigned int static_int_faces=0;
bool static_is_dual=false;
bool static_is_usial=false;

unsigned int getBinaryDigit(unsigned int keeper, unsigned int position) {
  return (keeper>>position)%2;
}

void setBinaryDigit(unsigned int &keeper, unsigned int position, unsigned int value) {
  unsigned int tmp=1;
  tmp<<=position;
  //cout << "keeper " << keeper << " pos " << position << " value " << value;
  if (value) {
    keeper|=tmp;
  } else {
    keeper&=~tmp;
  }
  //cout << " :: " << keeper << endl;
} 
