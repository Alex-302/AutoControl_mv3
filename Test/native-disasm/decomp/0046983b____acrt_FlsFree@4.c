// ___acrt_FlsFree@4 @ 0046983b size=86 callers=1

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    ___acrt_FlsFree@4
   
   Library: Visual Studio 2015 Release */

void ___acrt_FlsFree_4(DWORD param_1)

{
  code *pcVar1;
  
  pcVar1 = try_get_function(4,"FlsFree",(module_id *)&DAT_00486324,(module_id *)&DAT_0048632c);
  if (pcVar1 == (code *)0x0) {
    TlsFree(param_1);
  }
  else {
    (*(code *)PTR_guard_check_icall_004805b0)();
    (*pcVar1)();
  }
  return;
}


