#ifndef ETC_H_
#define ETC_H_
extern unsigned int static_ext_faces;
extern unsigned int static_int_faces;
extern bool static_is_dual;
extern bool static_is_usial;

unsigned int getBinaryDigit(unsigned int keeper, unsigned int position);
void setBinaryDigit(unsigned int &keeper, unsigned int position, unsigned int value);
#endif
