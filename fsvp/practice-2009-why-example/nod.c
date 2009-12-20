
/*@ predicate is_divisor(int m, int n) { if (m) then (n % m == 0) else \false } */

/*@ predicate is_gcd(int z, int x1, int x2) { 
  @         is_divisor(z,x1) 
  @      && is_divisor(z,x2)
  @      && \forall int i; is_divisor(i,x1) && is_divisor(i,x2) => (i <= z) } 
  @*/

/*@ logic int gcd(int m, int n) */
/*@ axiom gcd_def: \forall int m; \forall int n; is_gcd(gcd(m,n),m,n) */


/* The function returns the greatest common divisor of x1 and x2 */
/*@ requires (x1 > 0) && (x2 > 0)
  @ ensures is_gcd(\result,x1,x2) 
  @*/
int nod(int x1, int x2)
{
int y1 = x1;
int y2 = x2;
int tmp = 0;

  if (y1 > y2) {
    y1 = x2;
    y2 = x1;
  }
  /*@
    @ invariant ((0 < y1 <= y2) && gcd(x1,x2) == gcd(y1,y2))
    @        || ((y1 == 0) && gcd(x1,x2) == y2)
    @ variant y1
    @*/
  while (y1 != 0) {
    tmp = y1;
    y1 = y2%y1;
    y2 = tmp;
  }
  return y2;
}

