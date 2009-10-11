#ifndef BITCONTAINER_H_
#define BITCONTAINER_H_

#include <iostream>
using namespace std;

/***********DECLARATIONS*************/

template <unsigned int I> 
class BitContainer;

template<unsigned int I>
ostream& operator<<(ostream& os,const BitContainer<I>& bitcontainer);

  // Note: class architech-dependent, it assumes 1 byte == 8 bit
  // I -size of bytes in container (like std::bitset)
  
  /* * * * * * * * * * * * * * * * * * * * * * *
   *  I N T E R F A C E
   * * * * * * * * * * * * * * * * * * * * * * *
   */
  
  
template <unsigned int I> 
class BitContainer {
  public:
	  BitContainer();
    explicit BitContainer(unsigned int init);
	  ~BitContainer();
    BitContainer(const BitContainer& bc);
    BitContainer& operator=(const BitContainer& bc);
    BitContainer& operator~(); //neg
    BitContainer& operator++();
    BitContainer& operator--();
    unsigned int getbit(unsigned int pos)const;
    void setbit(unsigned int pos);
    void resetbit(unsigned int pos);
    unsigned int getUint(unsigned int uintpos=0)const;
    friend ostream& operator<< <I>(ostream& os,const BitContainer<I>& bitcontainer);
    
    // dangerous
    //unsigned int* getP();
  private:
    static const unsigned int BITS_IN_1_BYTE=8; // Bits In One Byte
    static const unsigned int SIZEOF_UINT=sizeof(unsigned int);
    static const unsigned int BITS_IN_UINT=BITS_IN_1_BYTE*SIZEOF_UINT;
    static const unsigned MAX_UINT= ~ static_cast<unsigned int>(0);
    unsigned int* RawBits;
    unsigned int Nuint; // Number of new[] uints;
    unsigned int Size; // Number of bits;
};

/* * * * * * * * * * * * * * * * * * * * * * * *
   *  I M P L E M E N T A T I O N
   * * * * * * * * * * * * * * * * * * * * * * *
   */

/*
template<unsigned int I> 
unsigned int* BitContainer<I>::getP() {
  return RawBits;
}
*/


template<unsigned int I> BitContainer<I>::BitContainer() {
  if (I==0) throw;
  Nuint=(I-1)/(BITS_IN_UINT)+1;
  Size=I;
  RawBits=new unsigned int[Nuint];
  // if (!RawBits) throw;
  for (unsigned int i=0; i<Nuint; ++i) {
    RawBits[i]=0; 
  }
}
template<unsigned int I> BitContainer<I>::BitContainer(unsigned int init) {
  if (I==0) throw;
  Nuint=(I-1)/(BITS_IN_UINT)+1;
  Size=I;
  RawBits=new unsigned int[Nuint];
  // if (!RawBits) throw;
  for (unsigned int i=0; i<Nuint; ++i) {
    RawBits[i]=init; 
  }
}


template<unsigned int I> BitContainer<I>::BitContainer(const BitContainer& bc) {
  Nuint=(I-1)/(BITS_IN_UINT)+1;
  Size=I;
  RawBits=new unsigned int[Nuint];
  // if (!RawBits) throw;
    for (unsigned int i=0; i<Nuint; ++i) {
    RawBits[i]=bc.RawBits[i]; // Copy bits;
  }
}

template<unsigned int I> 
BitContainer<I>& BitContainer<I>::operator=(const BitContainer& bc) {
  if (this == &bc) return *this; // self-assign
  for (unsigned int i=0; i<Nuint; ++i) {
    RawBits[i]=bc.RawBits[i]; // Copy bits;
  }
  return *this;
}

template<unsigned int I> 
BitContainer<I>& BitContainer<I>::operator~() {
  for (unsigned int i=0; i<Nuint; ++i) {
    RawBits[i]=~RawBits[i]; // Reverse bits;
  }
  return *this;
}

template<unsigned int I> 
BitContainer<I>& BitContainer<I>::operator++() {
  for (unsigned int i=0; i<Nuint; ++i) {
    if (RawBits[i]==MAX_UINT)  {
      RawBits[i]=0;
      continue;
    } else {
      ++RawBits[i];
      break;
    }
  }
  return *this;
}

template<unsigned int I> 
BitContainer<I>& BitContainer<I>::operator--() {
  for (unsigned int i=0; i<Nuint; ++i) {
    if (RawBits[i]==0)  {
      RawBits[i]=MAX_UINT;
      continue;
    } else {
      --RawBits[i];
      break;
    }
  }
  return *this;
}

template<unsigned int I> BitContainer<I>::~BitContainer() {
  delete[] RawBits;
}


template<unsigned int I> 
unsigned int BitContainer<I>::getbit(unsigned int pos) const {
  if (pos>=Size) throw;
  unsigned int current_uint=RawBits[pos/BITS_IN_UINT];
  return (current_uint>>(pos%BITS_IN_UINT))%2;
}

template<unsigned int I> 
void BitContainer<I>::setbit(unsigned int pos) {
  if (pos>=Size) throw;
  unsigned int *current_uint=RawBits+pos/BITS_IN_UINT;
  unsigned int mask=1;
  mask<<=pos%BITS_IN_UINT;
  *current_uint|=mask;
}

template<unsigned int I> 
void BitContainer<I>::resetbit(unsigned int pos) {
  if (pos>=Size) throw;
  unsigned int *current_uint=RawBits+pos/BITS_IN_UINT;
  unsigned int mask=1;
  mask<<=pos%BITS_IN_UINT;
  *current_uint&=~mask;
  
}

template<unsigned int I> 
unsigned int BitContainer<I>::getUint(unsigned int uintpos) const {
  if (0==uintpos) return *RawBits;
  if (uintpos<Nuint) return *(RawBits+uintpos); else throw;
}

template<unsigned int I>
ostream& operator<<(ostream& os,const BitContainer<I>& bitcontainer) {
  for(unsigned int i=bitcontainer.Size;i;) {
    os << bitcontainer.getbit(--i); 
  }
  return os; 
}

#endif /*BITCONTAINER_H_*/
