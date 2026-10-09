// ___acrt_FlsSetValue@8 @ 004698e7 size=89 callers=2

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    ___acrt_FlsSetValue@8
   
   Library: Visual Studio 2015 Release */

void ___acrt_FlsSetValue_8(DWORD param_1,LPVOID param_2)

{
  code *pcVar1;
  
  pcVar1 = try_get_function(6,"FlsSetValue",(module_id *)&DAT_00486334,(module_id *)&DAT_0048633c);
  if (pcVar1 == (code *)0x0) {
    TlsSetValue(param_1,param_2);
  }
  else {
    (*(code *)PTR_guard_check_icall_004805b0)();
    (*pcVar1)();
  }
  return;
}


