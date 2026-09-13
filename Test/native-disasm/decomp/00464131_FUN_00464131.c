// FUN_00464131 @ 00464131 size=52 callers=13

/* WARNING: Function: __SEH_prolog4_GS replaced with injection: SEH_prolog4 */

void FUN_00464131(void)

{
  code *pcVar1;
  __acrt_ptd *p_Var2;
  
  p_Var2 = FUN_0046aa74();
  pcVar1 = *(code **)(p_Var2 + 0xc);
  if (pcVar1 != (code *)0x0) {
    (*(code *)PTR_guard_check_icall_004805b0)();
    (*pcVar1)();
  }
                    /* WARNING: Subroutine does not return */
  _abort();
}


