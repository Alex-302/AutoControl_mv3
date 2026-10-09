// FUN_00465f27 @ 00465f27 size=122 callers=2

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl
FUN_00465f27(wchar_t *param_1,wchar_t *param_2,wchar_t *param_3,uint param_4,uintptr_t param_5)

{
  __acrt_ptd *p_Var1;
  byte bVar2;
  code *pcVar3;
  
  p_Var1 = ___acrt_getptd_noexit();
  if (((p_Var1 == (__acrt_ptd *)0x0) || (pcVar3 = *(code **)(p_Var1 + 0x35c), pcVar3 == (code *)0x0)
      ) && (bVar2 = (byte)DAT_0049d070 & 0x1f,
           pcVar3 = (code *)((DAT_0049d070 ^ _DAT_0049f56c) >> bVar2 |
                            (DAT_0049d070 ^ _DAT_0049f56c) << 0x20 - bVar2), pcVar3 == (code *)0x0))
  {
                    /* WARNING: Subroutine does not return */
    __invoke_watson(param_1,param_2,param_3,param_4,param_5);
  }
  (*(code *)PTR_guard_check_icall_004805b0)(param_1,param_2,param_3,param_4,param_5);
  (*pcVar3)();
  return;
}


