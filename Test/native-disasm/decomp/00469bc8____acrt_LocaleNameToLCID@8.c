// ___acrt_LocaleNameToLCID@8 @ 00469bc8 size=92 callers=4

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    ___acrt_LocaleNameToLCID@8
   
   Library: Visual Studio 2015 Release */

void ___acrt_LocaleNameToLCID_8(wchar_t *param_1,undefined4 param_2)

{
  code *pcVar1;
  
  pcVar1 = try_get_function(0x18,"LocaleNameToLCID",(module_id *)&DAT_004863b8,
                            (module_id *)"LocaleNameToLCID");
  if (pcVar1 == (code *)0x0) {
    ___acrt_DownlevelLocaleNameToLCID(param_1);
  }
  else {
    (*(code *)PTR_guard_check_icall_004805b0)(param_1,param_2);
    (*pcVar1)();
  }
  return;
}


