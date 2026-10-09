// __set_errno_from_matherr @ 0046cfe0 size=47 callers=5

/* Library Function - Single Match
    __set_errno_from_matherr
   
   Library: Visual Studio 2015 Release */

void __cdecl __set_errno_from_matherr(int param_1)

{
  int *piVar1;
  
  if (param_1 == 1) {
    piVar1 = __errno();
    *piVar1 = 0x21;
  }
  else if (param_1 - 2U < 2) {
    piVar1 = __errno();
    *piVar1 = 0x22;
    return;
  }
  return;
}


