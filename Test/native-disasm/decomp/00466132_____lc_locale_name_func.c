// ____lc_locale_name_func @ 00466132 size=41 callers=6

/* Library Function - Single Match
    ____lc_locale_name_func
   
   Library: Visual Studio 2015 Release */

wchar_t ** __cdecl ____lc_locale_name_func(void)

{
  __acrt_ptd *p_Var1;
  int local_8;
  
  p_Var1 = FUN_0046aa74();
  local_8 = *(int *)(p_Var1 + 0x4c);
  ___acrt_update_locale_info((int)p_Var1,&local_8);
  return (wchar_t **)(local_8 + 0xa0);
}


