// FUN_00471f6c @ 00471f6c size=107 callers=2

/* WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4 */
/* WARNING: Function: __SEH_epilog4 replaced with injection: EH_epilog3 */

undefined ** FUN_00471f6c(void)

{
  __acrt_ptd *p_Var1;
  undefined **ppuVar2;
  
  p_Var1 = FUN_0046aa74();
  if (((*(uint *)(p_Var1 + 0x350) & DAT_0049d3f8) == 0) ||
     (ppuVar2 = *(undefined ***)(p_Var1 + 0x4c), ppuVar2 == (undefined **)0x0)) {
    ___acrt_lock(4);
    ppuVar2 = __updatetlocinfoEx_nolock((undefined4 *)(p_Var1 + 0x4c),DAT_0049fafc);
    FUN_00471fd2();
    if (ppuVar2 == (undefined **)0x0) {
                    /* WARNING: Subroutine does not return */
      _abort();
    }
  }
  return ppuVar2;
}


