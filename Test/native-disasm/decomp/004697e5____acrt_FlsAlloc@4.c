// ___acrt_FlsAlloc@4 @ 004697e5 size=86 callers=1

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    ___acrt_FlsAlloc@4
   
   Library: Visual Studio 2015 Release */

void ___acrt_FlsAlloc_4(undefined4 param_1)

{
  code *pcVar1;
  
  pcVar1 = try_get_function(3,"FlsAlloc",(module_id *)&DAT_0048631c,(module_id *)&DAT_00486324);
  if (pcVar1 == (code *)0x0) {
    TlsAlloc();
  }
  else {
    (*(code *)PTR_guard_check_icall_004805b0)(param_1);
    (*pcVar1)();
  }
  return;
}


