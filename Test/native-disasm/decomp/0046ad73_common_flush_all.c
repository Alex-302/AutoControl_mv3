// common_flush_all @ 0046ad73 size=188 callers=2

/* WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4 */
/* WARNING: Function: __SEH_epilog4 replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    _common_flush_all
   
   Library: Visual Studio 2015 Release */

int __cdecl common_flush_all(int param_1)

{
  undefined4 *puVar1;
  FILE *_File;
  int iVar2;
  undefined4 *puVar3;
  int local_28;
  int local_20;
  
  local_20 = 0;
  local_28 = 0;
  ___acrt_lock(8);
  puVar1 = DAT_0049f55c + DAT_0049f558;
  for (puVar3 = DAT_0049f55c; puVar3 != puVar1; puVar3 = puVar3 + 1) {
    _File = (FILE *)*puVar3;
    if (_File != (FILE *)0x0) {
      __lock_file(_File);
      if (((uint)_File->_flag >> 0xd & 1) != 0) {
        if (param_1 == 1) {
          iVar2 = __fflush_nolock(_File);
          if (iVar2 != -1) {
            local_20 = local_20 + 1;
          }
        }
        else if ((param_1 == 0) && (((uint)_File->_flag >> 1 & 1) != 0)) {
          iVar2 = __fflush_nolock(_File);
          if (iVar2 == -1) {
            local_28 = -1;
          }
        }
      }
      FUN_0046ae18();
    }
  }
  FUN_0046ae42();
  if (param_1 != 1) {
    local_20 = local_28;
  }
  return local_20;
}


