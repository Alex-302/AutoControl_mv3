// ___acrt_IsValidLocaleName@4 @ 00469a73 size=99 callers=1

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    ___acrt_IsValidLocaleName@4
   
   Library: Visual Studio 2015 Release */

void ___acrt_IsValidLocaleName_4(wchar_t *param_1)

{
  code *pcVar1;
  LCID Locale;
  DWORD dwFlags;
  
  pcVar1 = try_get_function(0x15,"IsValidLocaleName",(module_id *)&DAT_00486378,
                            (module_id *)"IsValidLocaleName");
  if (pcVar1 == (code *)0x0) {
    dwFlags = 1;
    Locale = ___acrt_LocaleNameToLCID_8(param_1,0);
    IsValidLocale(Locale,dwFlags);
  }
  else {
    (*(code *)PTR_guard_check_icall_004805b0)(param_1);
    (*pcVar1)();
  }
  return;
}


