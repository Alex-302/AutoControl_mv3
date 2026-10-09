// ___acrt_LCMapStringEx@36 @ 00469b40 size=136 callers=4

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    ___acrt_LCMapStringEx@36
   
   Library: Visual Studio 2015 Release */

void ___acrt_LCMapStringEx_36
               (wchar_t *param_1,DWORD param_2,LPCWSTR param_3,int param_4,LPWSTR param_5,
               int param_6,undefined4 param_7,undefined4 param_8,undefined4 param_9)

{
  code *pcVar1;
  LCID Locale;
  
  pcVar1 = try_get_function(0x16,"LCMapStringEx",(module_id *)&DAT_00486394,
                            (module_id *)&DAT_0048639c);
  if (pcVar1 == (code *)0x0) {
    Locale = ___acrt_LocaleNameToLCID_8(param_1,0);
    LCMapStringW(Locale,param_2,param_3,param_4,param_5,param_6);
  }
  else {
    (*(code *)PTR_guard_check_icall_004805b0)
              (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    (*pcVar1)();
  }
  return;
}


