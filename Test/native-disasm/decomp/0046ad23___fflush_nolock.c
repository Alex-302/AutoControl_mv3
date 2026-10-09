// __fflush_nolock @ 0046ad23 size=71 callers=2

/* Library Function - Single Match
    __fflush_nolock
   
   Library: Visual Studio 2015 Release */

int __cdecl __fflush_nolock(FILE *_File)

{
  int iVar1;
  
  if (_File == (FILE *)0x0) {
    iVar1 = common_flush_all(0);
    return iVar1;
  }
  iVar1 = ___acrt_stdio_flush_nolock(_File);
  if (iVar1 == 0) {
    if (((uint)_File->_flag >> 0xb & 1) != 0) {
      iVar1 = __fileno(_File);
      iVar1 = __commit(iVar1);
      if (iVar1 != 0) goto LAB_0046ad44;
    }
    iVar1 = 0;
  }
  else {
LAB_0046ad44:
    iVar1 = -1;
  }
  return iVar1;
}


