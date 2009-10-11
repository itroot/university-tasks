#ifndef VECTOR3D_H_
#define VECTOR3D_H_

template<class T> class Vector3D {
  public:
  	Vector3D();
    Vector3D(const T& in_x, const T& in_y, const T& in_z);
   ~Vector3D();
    // minus 
    Vector3D& operator-=(const Vector3D& rhs);
    Vector3D operator-(const Vector3D& rhs);
    // plus
    Vector3D& operator+=(const Vector3D& rhs);
    Vector3D operator+(const Vector3D& rhs)const;
    // /
    Vector3D& operator/=(const T& rhs);
    Vector3D operator/(const T& rhs);
    // cross product;
    Vector3D operator&(const Vector3D& rhs);
    
    T& operator[](int index);
    const T& operator[](int index) const;

    T x()const;
    T y()const;
    T z()const;
    
    T norm_2()const;
  private:
    T X;
    T Y;
    T Z;
   
};

template<class T> Vector3D<T>::Vector3D() {
  X=0;
  Y=0;
  Z=0; 
}

template<class T> Vector3D<T>::Vector3D(const T& in_x, const T& in_y, const T& in_z) {
  X=in_x;
  Y=in_y;
  Z=in_z; 
}

template<class T> Vector3D<T>& Vector3D<T>::operator-=(const Vector3D<T>& rhs) {
  this->X-=rhs.X;
  this->Y-=rhs.Y;
  this->Z-=rhs.Z;
  return *this;
}

template<class T> Vector3D<T> Vector3D<T>::operator-(const Vector3D<T>& rhs) {
  Vector3D<T> that=*this;
  that-=rhs;
  return that;
}

template<class T> Vector3D<T>& Vector3D<T>::operator+=(const Vector3D<T>& rhs) {
  this->X+=rhs.X;
  this->Y+=rhs.Y;
  this->Z+=rhs.Z;
  return *this;
}

template<class T> Vector3D<T> Vector3D<T>::operator+(const Vector3D<T>& rhs) const {
  Vector3D<T> that=*this;
  that+=rhs;
  return that;
}

template<class T> Vector3D<T>& Vector3D<T>::operator/=(const T& rhs) {
  this->X/=rhs;
  this->Y/=rhs;
  this->Z/=rhs;
  return *this;
}

template<class T> Vector3D<T> Vector3D<T>::operator/(const T& rhs) {
  Vector3D<T> that=*this;
  that/=rhs;
  return that;
}


template<class T> Vector3D<T> Vector3D<T>::operator&(const Vector3D<T>& rhs) {
  Vector3D<T>& lhs=*this; //synonim
  return Vector3D<T>(
               lhs.y()*rhs.z()-rhs.y()*lhs.z(),
               rhs.x()*lhs.z()-lhs.x()*rhs.z(),
               lhs.x()*rhs.y()-rhs.x()*lhs.y()
              );
}

template<class T> T Vector3D<T>::x() const {return X;}
template<class T> T Vector3D<T>::y() const {return Y;}
template<class T> T Vector3D<T>::z() const {return Z;}

template<class T> T Vector3D<T>::norm_2() const {
  return sqrt(X*X+Y*Y+Z*Z);
}

template<class T> T& Vector3D<T>::operator[](int index) {
  if (index==0) return X;
  if (index==1) return Y;
  if (index==2) return Z;
  // throw (out_of_range)
  return Z;
}

template<class T> const T& Vector3D<T>::operator[](int index) const {
  if (index==0) return X;
  if (index==1) return Y;
  if (index==2) return Z;
  // throw (out_of_range)
  return Z;
} 

template<class T> Vector3D<T>::~Vector3D() {}

#endif /*VECTOR3D_H_*/
