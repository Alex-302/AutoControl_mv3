// common_lseek<__int64> @ 00473ce9 size=244 callers=1

/* WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4 */
/* WARNING: Function: __SEH_epilog4 replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    __int64 __cdecl common_lseek<__int64>(int,__int64,int)
   
   Library: Visual Studio 2015 Release */

__int64 __cdecl common_lseek<__int64>(int param_1,__int64 param_2,int param_3)

{
  ulong *puVar1;
  int *piVar2;
  int iVar3;
  __int64 _Var4;
  int in_stack_ffffffc0;
  
  if (param_1 == -2) {
    puVar1 = ___doserrno();
    *puVar1 = 0;
    piVar2 = __errno();
    *piVar2 = 9;
  }
  else {
    if ((-1 < param_1) && ((uint)param_1 < DAT_0049faf8)) {
      iVar3 = (param_1 & 0x3fU) * 0x30;
      if ((*(byte *)((&DAT_0049f8f8)[param_1 >> 6] + 0x28 + iVar3) & 1) != 0) {
        ___acrt_lowio_lock_fh(param_1);
        _Var4 = -1;
        if ((*(byte *)((&DAT_0049f8f8)[param_1 >> 6] + 0x28 + iVar3) & 1) == 0) {
          piVar2 = __errno();
          *piVar2 = 9;
          puVar1 = ___doserrno();
          *puVar1 = 0;
        }
        else {
          _Var4 = common_lseek_nolock<__int64>(param_1,param_2,in_stack_ffffffc0);
        }
        FUN_00473dc1();
        return _Var4;
      }
    }
    puVar1 = ___doserrno();
    *puVar1 = 0;
    piVar2 = __errno();
    *piVar2 = 9;
    FUN_00465fa2();
  }
  return -1;
}


