#include "syscall.h"

int main()
{
	int j, k, r;
	j = OSAdd(15,10);
	k = OSSub(j,15);
	r = OSDiv(140,k);
	OSMul(112,r);
	Print("Hello, we are B97611034 & B97901082\n", 36);
	Halt();
}
