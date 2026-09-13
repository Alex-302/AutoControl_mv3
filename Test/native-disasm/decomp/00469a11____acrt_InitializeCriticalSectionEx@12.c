// ___acrt_InitializeCriticalSectionEx@12 @ 00469a11 size=98 callers=3

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    ___acrt_InitializeCriticalSectionEx@12
   
   Library: Visual Studio 2015 Release */

void ___acrt_InitializeCriticalSectionEx_12
               (LPCRITICAL_SECTION param_1,DWORD param_2,undefined4 param_3)

{
  code *pcVar1;
  
  pcVar1 = try_get_function(0x14,"InitializeCriticalSectionEx",(module_id *)&DAT_00486370,
                            (module_id *)&DAT_00486378);
  if (pcVar1 == (code *)0x0) {
    InitializeCriticalSectionAndSpinCount(param_1,param_2);
  }
  else {
    (*(code *)PTR_guard_check_icall_004805b0)(param_1,param_2,param_3);
    (*pcVar1)();
  }
  return;
}


