// ___acrt_update_thread_multibyte_data @ 004709e0 size=150 callers=2

/* WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4 */
/* WARNING: Function: __SEH_epilog4 replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    ___acrt_update_thread_multibyte_data
   
   Library: Visual Studio 2015 Release */

int * ___acrt_update_thread_multibyte_data(void)

{
  int iVar1;
  __acrt_ptd *p_Var2;
  int *_Memory;
  
  p_Var2 = FUN_0046aa74();
  if (((*(uint *)(p_Var2 + 0x350) & DAT_0049d3f8) == 0) || (*(int *)(p_Var2 + 0x4c) == 0)) {
    ___acrt_lock(5);
    _Memory = *(int **)(p_Var2 + 0x48);
    if (_Memory != (int *)PTR_DAT_0049d9a8) {
      if (_Memory != (int *)0x0) {
        LOCK();
        iVar1 = *_Memory;
        *_Memory = iVar1 + -1;
        UNLOCK();
        if ((iVar1 + -1 == 0) && (_Memory != &DAT_0049d788)) {
          FID_conflict__free(_Memory);
        }
      }
      *(undefined **)(p_Var2 + 0x48) = PTR_DAT_0049d9a8;
      _Memory = (int *)PTR_DAT_0049d9a8;
      LOCK();
      *(int *)PTR_DAT_0049d9a8 = *(int *)PTR_DAT_0049d9a8 + 1;
      UNLOCK();
    }
    FUN_00470a71();
  }
  else {
    _Memory = *(int **)(p_Var2 + 0x48);
  }
  if (_Memory == (int *)0x0) {
                    /* WARNING: Subroutine does not return */
    _abort();
  }
  return _Memory;
}


