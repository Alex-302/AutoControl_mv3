// ___acrt_is_packaged_app @ 00469c56 size=135 callers=1

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    ___acrt_is_packaged_app
   
   Library: Visual Studio 2015 Release */

uint __fastcall ___acrt_is_packaged_app(void)

{
  uint uVar1;
  code *pcVar2;
  int iVar3;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_0049d070 ^ (uint)&stack0xfffffffc;
  if (DAT_0049f8f4 == 0) {
    pcVar2 = try_get_function(8,"GetCurrentPackageId",(module_id *)&DAT_0048633c,
                              (module_id *)&DAT_00486344);
    if (pcVar2 != (code *)0x0) {
      local_c = 0;
      (*(code *)PTR_guard_check_icall_004805b0)(&local_c,0);
      iVar3 = (*pcVar2)();
      if (iVar3 == 0x7a) {
        LOCK();
        UNLOCK();
        DAT_0049f8f4 = 1;
        return 1;
      }
    }
    uVar1 = DAT_0049f8f4;
    LOCK();
    DAT_0049f8f4 = 2;
    UNLOCK();
    uVar1 = uVar1 & 0xffffff00;
  }
  else {
    uVar1 = (uint)(DAT_0049f8f4 == 1);
  }
  return uVar1;
}


