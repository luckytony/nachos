#include "syscall.h"

int main()
{
	int j, k, r, l;
	j = OSAdd(15,10);
	PrintF("The return value of OSAdd(15, 10) is %d\n", j);
	k = OSSub(j,15);
	PrintF("The return value of OSSub(%d, 15) is %d\n", j, k);
	r = OSDiv(140,k);
	PrintF("The return value of OSDiv(140, %d) is %d\n", k, r);
	l = OSMul(112,r);
	PrintF("The return value of OSMul(112, %d) is %d\n", r, l);
	Print("Hello, we are B97611034 & B97901082\n", 36);
	Halt();
}
