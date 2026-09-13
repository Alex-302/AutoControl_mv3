// ___acrt_GetUserDefaultLocaleName@8 @ 004699aa size=103 callers=1

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    ___acrt_GetUserDefaultLocaleName@8
   
   Library: Visual Studio 2015 Release */

void ___acrt_GetUserDefaultLocaleName_8(wchar_t *param_1,rsize_t param_2)

{
  code *pcVar1;
  LCID LVar2;
  undefined4 uVar3;
  
  pcVar1 = try_get_function(0x11,"GetUserDefaultLocaleName",(module_id *)&DAT_0048634c,
                            (module_id *)"GetUserDefaultLocaleName");
  if (pcVar1 == (code *)0x0) {
    uVar3 = 0;
    LVar2 = GetUserDefaultLCID();
    ___acrt_LCIDToLocaleName_16(LVar2,param_1,param_2,uVar3);
  }
  else {
    (*(code *)PTR_guard_check_icall_004805b0)(param_1,param_2);
    (*pcVar1)();
  }
  return;
}


