// __read @ 0046d6bb size=261 callers=1

/* WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4 */
/* WARNING: Function: __SEH_epilog4 replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    __read
   
   Library: Visual Studio 2015 Release */

int __cdecl __read(int _FileHandle,void *_DstBuf,uint _MaxCharCount)

{
  ulong *puVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  
  if (_FileHandle == -2) {
    puVar1 = ___doserrno();
    *puVar1 = 0;
    piVar2 = __errno();
    *piVar2 = 9;
    return -1;
  }
  if ((-1 < _FileHandle) && ((uint)_FileHandle < DAT_0049faf8)) {
    iVar3 = (_FileHandle & 0x3fU) * 0x30;
    if ((*(byte *)((&DAT_0049f8f8)[_FileHandle >> 6] + 0x28 + iVar3) & 1) != 0) {
      if (_MaxCharCount < 0x80000000) {
        ___acrt_lowio_lock_fh(_FileHandle);
        iVar4 = -1;
        if ((*(byte *)((&DAT_0049f8f8)[_FileHandle >> 6] + 0x28 + iVar3) & 1) == 0) {
          piVar2 = __errno();
          *piVar2 = 9;
          puVar1 = ___doserrno();
          *puVar1 = 0;
        }
        else {
          iVar4 = __read_nolock(_FileHandle,_DstBuf,_MaxCharCount);
        }
        FUN_0046d7a5();
        return iVar4;
      }
      puVar1 = ___doserrno();
      *puVar1 = 0;
      piVar2 = __errno();
      *piVar2 = 0x16;
      goto LAB_0046d7c0;
    }
  }
  puVar1 = ___doserrno();
  *puVar1 = 0;
  piVar2 = __errno();
  *piVar2 = 9;
LAB_0046d7c0:
  FUN_00465fa2();
  return -1;
}


