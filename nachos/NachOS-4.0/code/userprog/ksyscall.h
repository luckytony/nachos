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
    //kernel->currentThread->Finish();
}

//----------------------------------------------------------------------
// myPrint(in address, int value)
//     print something like ("Hello World %d", 1)
//----------------------------------------------------------------------
int myPrint(int address, int input)
{
     int addr = address;
     int value = 0;
     int idx = 0;
     char str[128];
     while(true){
         kernel->machine->ReadMem(addr++, 1, &value);
         if (value == '\0')
             break;
         else
             str[idx++] = (char)value;
     }
     printf(str, input);
     return 1;
}

//----------------------------------------------------------------------
// myPrintUint(int input)
//     print unsigned integer
//----------------------------------------------------------------------
int myPrintUInt(int input)
{
   if (input < 10){
      input = input + 48;
      kernel->synchConsoleOut->PutChar((char)input);
   }
   else{
      int reminder = input % 10;
      input = input / 10;
      myPrintUInt(input);
      reminder = reminder + 48;
      kernel->synchConsoleOut->PutChar((char)reminder);
   }
   return 1;
}


//----------------------------------------------------------------------
// myPrintF(char* input, ...)
//     like printf, but only print char and integer
//----------------------------------------------------------------------
int myPrintF(char* input, ...)
{
   va_list list;
   va_start(list, input);
   int value = 0;
   int addr = (int)input;
   while(true){
      kernel->machine->ReadMem((int)addr++, 1, &value);
      if (value == '\0')
	 break;
      if ((char)value == '%'){
         int format = 0;
	 kernel->machine->ReadMem((int)addr++, 1, &format);
	 if (format != 'd'){
	    kernel->synchConsoleOut->PutChar((char)value);
	    kernel->synchConsoleOut->PutChar((char)format);
	 }
	 else{
            format = va_arg(list, int);
	    if (format < 0){
	       kernel->synchConsoleOut->PutChar('-');
	       format = 0 - format;
	    }
	    myPrintUInt(format);
	 }
      }
      else
	 kernel->synchConsoleOut->PutChar((char)value);
   }

   va_end(list);
   return 1;

}


#endif /* ! __USERPROG_KSYSCALL_H__ */
