// _localeconv @ 0046416d size=42 callers=2

/* Library Function - Single Match
    _localeconv
   
   Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release */

lconv * __cdecl _localeconv(void)

{
  __acrt_ptd *p_Var1;
  int local_8;
  
  p_Var1 = FUN_0046aa74();
  local_8 = *(int *)(p_Var1 + 0x4c);
  ___acrt_update_locale_info((int)p_Var1,&local_8);
  return *(lconv **)(local_8 + 0x88);
}


