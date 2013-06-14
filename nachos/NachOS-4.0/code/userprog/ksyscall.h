/**************************************************************
 *
 * userprog/ksyscall.h
 *
 * Kernel interface for systemcalls 
 *
 * by Marcus Voelp  (c) Universitaet Karlsruhe
 *
 **************************************************************/

#ifndef __USERPROG_KSYSCALL_H__ 
#define __USERPROG_KSYSCALL_H__ 

#include "kernel.h"
#include "synchconsole.h"
#include <stdarg.h>
#include <sstream>

void SysHalt()
{
  kernel->interrupt->Halt();
}


int SysAdd(int op1, int op2)
{
  return op1 + op2;
}

//----------------------------------------------------------------------
// myExit(int status)
//     call when the user program terminated
//----------------------------------------------------------------------
int myExit(int status)
{
    numUsrProg--;
    numThread--;
    cout << kernel->currentThread->getName() << " Terminated\n";
    kernel->currentThread->Finish();
    return 1;
}

//----------------------------------------------------------------------
// string int2str(int val)
//     convert integer to string
//----------------------------------------------------------------------
string int2str(int val)
{
    ostringstream out;
    out << val;
    return out.str();
}

//----------------------------------------------------------------------
// myPrintF(int address, int value)
//     like printf, but only print char and integer
//----------------------------------------------------------------------
int myPrintF(int address, int input)
{
   char str[128];
   int value = 0;
   int idx = 0;
   int addr = address;
   while(true){
      kernel->machine->ReadMem((int)addr++, 1, &value);
      if (value == '\0'){
         str[idx++] = value;
	 break;
      }
      if ((char)value == '%'){
         int format = 0;
	 kernel->machine->ReadMem((int)addr++, 1, &format);
	 if (format != 'd'){
            str[idx++] = (char)value;
            str[idx++] = (char)format;
	 }
	 else{
	    string s = int2str(input);
            for (int i=0; i<s.size(); i++)
                str[idx++] = s[i];
	 }
      }
      else
	 str[idx++] = (char)value;
   }
   kernel->synchConsoleOut->PutString(str, idx);
   //printf(str);
   return 1;
}


#endif /* ! __USERPROG_KSYSCALL_H__ */
