// __wsetlocale @ 00468513 size=128 callers=2

/* Library Function - Single Match
    __wsetlocale
   
   Library: Visual Studio 2015 Release */

wchar_t * __cdecl __wsetlocale(int _Category,wchar_t *_Locale)

{
  int *piVar1;
  undefined4 *local_2c;
  __acrt_ptd **local_28;
  wchar_t **local_24;
  int *local_20;
  wchar_t **local_1c;
  __acrt_ptd **local_18;
  undefined4 local_14;
  wchar_t *local_10;
  __acrt_ptd *local_c;
  __crt_seh_guarded_call<void> local_5;
  
  local_10 = (wchar_t *)0x0;
  local_14 = 0;
  if ((uint)_Category < 6) {
    local_c = FUN_0046aa74();
    FUN_00471f6c();
    *(uint *)(local_c + 0x350) = *(uint *)(local_c + 0x350) | 0x10;
    local_18 = &local_c;
    local_2c = &local_14;
    local_28 = &local_c;
    local_24 = &local_10;
    local_20 = &_Category;
    local_1c = &_Locale;
    __crt_seh_guarded_call<void>::
    operator()<<lambda_70818de7b02deff9841e8b0962a60ed9>,<lambda_2af78c5f5901b1372d98f9ab3177dfa6>&,<lambda_f51fe5fd7c79a33db34fc9310f277369>&>
              (&local_5,(<lambda_70818de7b02deff9841e8b0962a60ed9> *)&local_5,
               (<lambda_2af78c5f5901b1372d98f9ab3177dfa6> *)&local_2c,
               (<lambda_f51fe5fd7c79a33db34fc9310f277369> *)&local_18);
  }
  else {
    piVar1 = __errno();
    *piVar1 = 0x16;
    FUN_00465fa2();
    local_10 = (wchar_t *)0x0;
  }
  return local_10;
}


