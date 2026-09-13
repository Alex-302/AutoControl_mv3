// ___acrt_LCIDToLocaleName@16 @ 00469ad6 size=106 callers=3

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    ___acrt_LCIDToLocaleName@16
   
   Library: Visual Studio 2015 Release */

void ___acrt_LCIDToLocaleName_16(int param_1,wchar_t *param_2,rsize_t param_3,undefined4 param_4)

{
  code *pcVar1;
  
  pcVar1 = try_get_function(0x17,"LCIDToLocaleName",(module_id *)&DAT_0048639c,
                            (module_id *)"LCIDToLocaleName");
  if (pcVar1 == (code *)0x0) {
    FUN_00473998(param_1,param_2,param_3);
  }
  else {
    (*(code *)PTR_guard_check_icall_004805b0)(param_1,param_2,param_3,param_4);
    (*pcVar1)();
  }
  return;
}


