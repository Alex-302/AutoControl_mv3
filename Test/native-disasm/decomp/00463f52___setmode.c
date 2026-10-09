// __setmode @ 00463f52 size=256 callers=2

/* WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4 */
/* WARNING: Function: __SEH_epilog4 replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    __setmode
   
   Library: Visual Studio 2015 Release */

int __cdecl __setmode(int _FileHandle,int _Mode)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  if ((((_Mode == 0x4000) || (_Mode == 0x8000)) || (_Mode == 0x10000)) ||
     ((_Mode == 0x40000 || (_Mode == 0x20000)))) {
    if (_FileHandle == -2) {
      piVar1 = __errno();
      *piVar1 = 9;
      return -1;
    }
    if ((-1 < _FileHandle) && ((uint)_FileHandle < DAT_0049faf8)) {
      iVar2 = (_FileHandle & 0x3fU) * 0x30;
      if ((*(byte *)((&DAT_0049f8f8)[_FileHandle >> 6] + 0x28 + iVar2) & 1) != 0) {
        ___acrt_lowio_lock_fh(_FileHandle);
        iVar3 = -1;
        if ((*(byte *)((&DAT_0049f8f8)[_FileHandle >> 6] + 0x28 + iVar2) & 1) == 0) {
          piVar1 = __errno();
          *piVar1 = 9;
        }
        else {
          iVar3 = __setmode_nolock(_FileHandle,_Mode);
        }
        FUN_0046403f();
        return iVar3;
      }
    }
    piVar1 = __errno();
    *piVar1 = 9;
  }
  else {
    piVar1 = __errno();
    *piVar1 = 0x16;
  }
  FUN_00465fa2();
  return -1;
}


