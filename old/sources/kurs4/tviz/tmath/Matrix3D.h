#ifndef MATRIX3D_H_
#define MATRIX3D_H_

#include <iostream>
#include "Point3D.h"
using namespace std;

template <class T> 
class Matrix3D; // Square matrix with size Matrix3D<T>::SIZE

typedef Matrix3D<int> IntMatrix3D;

template <class T>
ostream& operator<<(ostream& os, const Matrix3D<T>& matrix);
template <class T>
Point3D operator*(const Point3D& point,const Matrix3D<T>& matrix);
template <class T>
Point3D operator*(const Matrix3D<T>& matrix,const Point3D& point);


template <class T> 
class Matrix3D {
  public: 
    Matrix3D(); // creates zerofill matrix
    explicit Matrix3D(T* elems); // Must be HEIGHT*WIDTH elems
    
    Matrix3D(const Matrix3D<T>& matrix);
    Matrix3D<T>& operator=(const Matrix3D<T>& matrix);
    bool operator==(const Matrix3D<T>& matrix)const;
    bool operator<(const Matrix3D<T>& matrix)const; // for std::set, temporary
    
    friend ostream& operator<< <T>(ostream& os, const Matrix3D<T>& matrix);
    friend Point3D operator* <T>(const Point3D& point,const Matrix3D<T>& matrix);
    friend Point3D operator* <T>(const Matrix3D<T>& matrix,const Point3D& point);
    
    Matrix3D<T> operator*(const Matrix3D<T>& rhs)const;

    
    T& elem(unsigned int height,unsigned int width);
    const T& const_elem(unsigned int height,unsigned int width) const;
    void loadIdentity();
    
  private:
    static const unsigned int SIZE=3;
    static const unsigned int HEIGHT=SIZE;
    static const unsigned int WIDTH=SIZE;
    T rawM[3][3]; 
};



template <class T>
Matrix3D<T>::Matrix3D() {
  for(unsigned int i=0;i<HEIGHT;++i) 
    for(unsigned int j=0;j<WIDTH;++j)
      rawM[i][j]=0;
};

template <class T>
Matrix3D<T>::Matrix3D(T* elems) {
  for(unsigned int i=0;i<HEIGHT;++i) 
    for(unsigned int j=0;j<WIDTH;++j)
      rawM[i][j]=elems[j+WIDTH*i];
};


template <class T>
Matrix3D<T>::Matrix3D(const Matrix3D<T>& matrix) {
  for(unsigned int i=0;i<HEIGHT;++i) 
    for(unsigned int j=0;j<WIDTH;++j)
      this->rawM[i][j]=matrix.const_elem(i,j);
}

template <class T>
Matrix3D<T>& Matrix3D<T>::operator=(const Matrix3D<T>& matrix) {
  if (&matrix==this) return *this; // self
  for(unsigned int i=0;i<HEIGHT;++i) 
    for(unsigned int j=0;j<WIDTH;++j)
      this->rawM[i][j]=matrix.const_elem(i,j);
  return *this;
}

template <class T>
bool Matrix3D<T>::operator==(const Matrix3D<T>& matrix) const {
  for(unsigned int i=0;i<HEIGHT;++i) { 
    for(unsigned int j=0;j<WIDTH;++j) {
      if (matrix.const_elem(i,j)!=this->rawM[i][j]) return false;   
    }
  }
  return true;
}

template <class T>
bool Matrix3D<T>::operator<(const Matrix3D<T>& matrix) const {
  for(unsigned int i=0;i<HEIGHT;++i) { 
    for(unsigned int j=0;j<WIDTH;++j) {
      if (this->const_elem(i,j)<matrix.const_elem(i,j)) return true; else 
        if (this->const_elem(i,j)>matrix.const_elem(i,j)) return false; 
    }
  }
  return false;
}

template <class T>
Matrix3D<T> Matrix3D<T>::operator*(const Matrix3D<T>& rhs)const {
  Matrix3D tmp;
  for(unsigned int i=0;i<HEIGHT;++i) {
    for(unsigned int j=0;j<WIDTH;++j) {
      for(unsigned int k=0;k<SIZE;++k) {
        tmp.elem(i,j)+=this->const_elem(i,k)*rhs.const_elem(k,j);
      }
    }
  }
  return tmp; 
}



template <class T>
void Matrix3D<T>::loadIdentity() {
  for(unsigned int i=0;i<HEIGHT;++i) 
    for(unsigned int j=0;j<WIDTH;++j)
      rawM[i][j]=(i==j?1:0);
};

template <class T>
T& Matrix3D<T>::elem(unsigned int height,unsigned int width) {
  if ((height>=HEIGHT) || (width>=WIDTH)) throw;
  return rawM[height][width];
}

template <class T>
const T& Matrix3D<T>::const_elem(unsigned int height,unsigned int width) const {
  if ((height>=HEIGHT) || (width>=WIDTH)) throw;
  return rawM[height][width];
}

template <class T>
ostream& operator<<(ostream& os, const Matrix3D<T>& matrix) {
  os<<"{";
  for(unsigned int i=0;i<Matrix3D<T>::HEIGHT;++i) { 
    for(unsigned int j=0;j<Matrix3D<T>::WIDTH;++j) {
      os<<matrix.rawM[i][j]<<
      (((i==Matrix3D<T>::SIZE-1)&&(j==Matrix3D<T>::SIZE-1))?"}":",");
    }
    os<<endl;
  }
  return os<<endl;  
}

template <class T>
Point3D operator*(const Point3D& point, const Matrix3D<T>& matrix) {
  Point3D tmp;
  for(unsigned int i=0;i<Matrix3D<T>::HEIGHT;++i) {
    for(unsigned int j=0;j<Matrix3D<T>::WIDTH;++j) {
      tmp.elem(i)+=matrix.const_elem(i,j)*point.const_elem(j);
    }
  }
  return tmp;
}

template <class T>
Point3D operator*(const Matrix3D<T>& matrix,const Point3D& point) {
  return point*matrix;
}

#endif /*MATRIX3D_H_*/
