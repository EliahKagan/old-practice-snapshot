/*You are required to complete
this function*/
class GfG
{
     long floorSqrt(long n)
	 {
	     // Problem constraints say n <= 10**6, so Math.sqrt() and casting
	     // is sufficient. In Java, double is IEEE754 binary64, which has
	     // 53-bit significands and thus can exactly represent every n for
	     // which abs(n) < 2**53. Further, problem contraints say 1 <= n,
	     // so (long)n == floor(n). NOTE: If problem constraints are
	     // changed, then a different implementation may be needed. Which
	     // changes are appropriate will depend on the details of the new
	     // constraints as well as any time requirements.
	     return (long)Math.sqrt(n);
	 }
}
