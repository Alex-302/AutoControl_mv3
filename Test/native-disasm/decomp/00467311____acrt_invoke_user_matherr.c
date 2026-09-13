// ___acrt_invoke_user_matherr @ 00467311 size=73 callers=3

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    ___acrt_invoke_user_matherr
   
   Library: Visual Studio 2015 Release */

undefined4 __cdecl ___acrt_invoke_user_matherr(undefined4 param_1)

{
  undefined4 uVar1;
  byte bVar2;
  code *pcVar3;
  
  bVar2 = (byte)DAT_0049d070 & 0x1f;
  pcVar3 = (code *)((DAT_0049d070 ^ _DAT_0049f6b0) >> bVar2 |
                   (DAT_0049d070 ^ _DAT_0049f6b0) << 0x20 - bVar2);
  if (pcVar3 == (code *)0x0) {
    uVar1 = 0;
  }
  else {
    (*(code *)PTR_guard_check_icall_004805b0)(param_1);
    uVar1 = (*pcVar3)();
  }
  return uVar1;
}


