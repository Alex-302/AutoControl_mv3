// ___libm_error_support @ 00475503 size=536 callers=6

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    ___libm_error_support
   
   Library: Visual Studio 2015 Release */

void __cdecl
___libm_error_support(undefined8 *param_1,undefined8 *param_2,undefined8 *param_3,int param_4)

{
  undefined8 uVar1;
  code *pcVar2;
  int iVar3;
  int *piVar4;
  undefined4 local_28;
  char *local_24;
  undefined8 local_20;
  undefined8 local_18;
  undefined8 local_10;
  uint local_8;
  
  local_8 = DAT_0049d070 ^ (uint)&stack0xfffffffc;
  if (DAT_0049fc0c == 0) {
    pcVar2 = ___acrt_invoke_user_matherr;
  }
  else {
    pcVar2 = DecodePointer(DAT_004a33e0);
  }
  if (0x1a < param_4) {
    if (param_4 != 0x1b) {
      if (param_4 == 0x1c) {
        local_24 = "pow";
      }
      else if (param_4 == 0x31) {
        local_24 = "sqrt";
      }
      else if (param_4 == 0x3a) {
        local_24 = "acos";
      }
      else {
        if (param_4 != 0x3d) {
          if ((param_4 != 1000) && (param_4 != 0x3e9)) {
            return;
          }
          uVar1 = *param_1;
          goto LAB_00475658;
        }
        local_24 = "asin";
      }
      goto LAB_00475577;
    }
    local_28 = 2;
LAB_004756c9:
    local_24 = "pow";
    goto LAB_004756d0;
  }
  if (param_4 == 0x1a) {
    uVar1 = 0x3ff0000000000000;
LAB_00475658:
    *param_3 = uVar1;
    return;
  }
  if (0xe < param_4) {
    if (param_4 == 0xf) {
      local_24 = "exp";
    }
    else {
      if (param_4 == 0x18) {
        local_28 = 3;
        goto LAB_004756c9;
      }
      if (param_4 != 0x19) {
        return;
      }
      local_24 = "pow";
    }
    local_28 = 4;
    local_20 = *param_1;
    local_18 = *param_2;
    local_10 = *param_3;
    (*(code *)PTR_guard_check_icall_004805b0)(&local_28);
    (*pcVar2)();
    goto LAB_00475706;
  }
  if (param_4 == 0xe) {
    local_28 = 3;
    local_24 = "exp";
  }
  else {
    if (param_4 != 2) {
      if (param_4 == 3) {
        local_24 = "log";
      }
      else {
        if (param_4 == 8) {
          local_28 = 2;
          local_24 = "log10";
          goto LAB_004756d0;
        }
        if (param_4 != 9) {
          return;
        }
        local_24 = "log10";
      }
LAB_00475577:
      local_28 = 1;
      local_20 = *param_1;
      local_18 = *param_2;
      local_10 = *param_3;
      (*(code *)PTR_guard_check_icall_004805b0)(&local_28);
      iVar3 = (*pcVar2)();
      if (iVar3 == 0) {
        piVar4 = __errno();
        *piVar4 = 0x21;
      }
      goto LAB_00475706;
    }
    local_28 = 2;
    local_24 = "log";
  }
LAB_004756d0:
  local_20 = *param_1;
  local_18 = *param_2;
  local_10 = *param_3;
  (*(code *)PTR_guard_check_icall_004805b0)(&local_28);
  iVar3 = (*pcVar2)();
  if (iVar3 == 0) {
    piVar4 = __errno();
    *piVar4 = 0x22;
  }
LAB_00475706:
  *param_3 = local_10;
  return;
}


