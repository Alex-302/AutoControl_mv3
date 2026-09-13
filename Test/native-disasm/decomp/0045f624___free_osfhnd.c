// __free_osfhnd @ 0045f624 size=145 callers=1

/* Library Function - Single Match
    __free_osfhnd
   
   Library: Visual Studio 2015 Release */

int __cdecl __free_osfhnd(int param_1)

{
  int iVar1;
  int *piVar2;
  ulong *puVar3;
  int iVar4;
  DWORD nStdHandle;
  
  if ((-1 < param_1) && ((uint)param_1 < DAT_0049faf8)) {
    iVar4 = (param_1 & 0x3fU) * 0x30;
    if (((*(byte *)(iVar4 + 0x28 + (&DAT_0049f8f8)[param_1 >> 6]) & 1) != 0) &&
       (*(int *)(iVar4 + 0x18 + (&DAT_0049f8f8)[param_1 >> 6]) != -1)) {
      iVar1 = FUN_004672cf();
      if (iVar1 == 1) {
        if (param_1 == 0) {
          nStdHandle = 0xfffffff6;
        }
        else if (param_1 == 1) {
          nStdHandle = 0xfffffff5;
        }
        else {
          if (param_1 != 2) goto LAB_0045f68a;
          nStdHandle = 0xfffffff4;
        }
        SetStdHandle(nStdHandle,(HANDLE)0x0);
      }
LAB_0045f68a:
      *(undefined4 *)(iVar4 + 0x18 + (&DAT_0049f8f8)[param_1 >> 6]) = 0xffffffff;
      return 0;
    }
  }
  piVar2 = __errno();
  *piVar2 = 9;
  puVar3 = ___doserrno();
  *puVar3 = 0;
  return -1;
}


