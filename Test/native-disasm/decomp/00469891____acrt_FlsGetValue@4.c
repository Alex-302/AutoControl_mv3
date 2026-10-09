// ___acrt_FlsGetValue@4 @ 00469891 size=86 callers=2

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    ___acrt_FlsGetValue@4
   
   Library: Visual Studio 2015 Release */

void ___acrt_FlsGetValue_4(DWORD param_1)

{
  code *pcVar1;
  
  pcVar1 = try_get_function(5,"FlsGetValue",(module_id *)&DAT_0048632c,(module_id *)&DAT_00486334);
  if (pcVar1 == (code *)0x0) {
    TlsGetValue(param_1);
  }
  else {
    (*(code *)PTR_guard_check_icall_004805b0)();
    (*pcVar1)();
  }
  return;
}


