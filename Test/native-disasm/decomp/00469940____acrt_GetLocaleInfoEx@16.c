// ___acrt_GetLocaleInfoEx@16 @ 00469940 size=106 callers=16

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    ___acrt_GetLocaleInfoEx@16
   
   Library: Visual Studio 2015 Release */

void ___acrt_GetLocaleInfoEx_16(wchar_t *param_1,LCTYPE param_2,LPWSTR param_3,int param_4)

{
  code *pcVar1;
  LCID Locale;
  
  pcVar1 = try_get_function(0xd,"GetLocaleInfoEx",(module_id *)&DAT_00486344,
                            (module_id *)&DAT_0048634c);
  if (pcVar1 == (code *)0x0) {
    Locale = ___acrt_LocaleNameToLCID_8(param_1,0);
    GetLocaleInfoW(Locale,param_2,param_3,param_4);
  }
  else {
    (*(code *)PTR_guard_check_icall_004805b0)(param_1);
    (*pcVar1)();
  }
  return;
}


