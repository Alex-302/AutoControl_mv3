// FUN_0046c441 @ 0046c441 size=247 callers=1

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined4 __cdecl FUN_0046c441(int param_1,byte param_2,char *param_3,uint param_4,char param_5)

{
  char *pcVar1;
  char cVar2;
  undefined4 uVar3;
  errno_t eVar4;
  uint uVar5;
  char *pcVar6;
  undefined *local_48 [4];
  undefined *local_38;
  undefined *local_34;
  undefined *local_30;
  undefined *local_2c;
  char *local_28;
  undefined *local_24;
  char *local_20;
  undefined *local_1c;
  char *local_18;
  undefined *local_14;
  char *local_10;
  undefined *local_c;
  uint local_8;
  
  local_8 = DAT_0049d070 ^ (uint)&stack0xfffffffc;
  if (param_4 < param_2 + 4) {
    *param_3 = '\0';
    uVar3 = 0xc;
  }
  else {
    if (param_2 != 0) {
      *param_3 = '-';
      param_3 = param_3 + 1;
      param_4 = param_4 - 1;
      *param_3 = '\0';
    }
    local_28 = "NAN(SNAN)";
    local_48[0] = &DAT_0048688c;
    local_48[1] = &DAT_0048688c;
    local_48[2] = &DAT_00486890;
    local_48[3] = &DAT_00486890;
    local_20 = "nan(snan)";
    local_30 = &DAT_00486898;
    uVar5 = (param_5 != '\0') - 1 & 2;
    local_2c = &DAT_00486898;
    local_1c = &DAT_00486898;
    local_c = &DAT_00486898;
    local_18 = "NAN(IND)";
    local_38 = &DAT_00486894;
    local_34 = &DAT_00486894;
    local_24 = &DAT_00486894;
    local_14 = &DAT_00486894;
    local_10 = "nan(ind)";
    pcVar6 = local_48[param_1 * 4 + -4 + uVar5];
    pcVar1 = pcVar6 + 1;
    do {
      cVar2 = *pcVar6;
      pcVar6 = pcVar6 + 1;
    } while (cVar2 != '\0');
    eVar4 = _strcpy_s(param_3,param_4,
                      local_48[((param_1 * 4 + -3) -
                               (uint)((uint)((int)pcVar6 - (int)pcVar1) < param_4)) + uVar5]);
    uVar3 = 0;
    if (eVar4 != 0) {
                    /* WARNING: Subroutine does not return */
      __invoke_watson((wchar_t *)0x0,(wchar_t *)0x0,(wchar_t *)0x0,0,0);
    }
  }
  return uVar3;
}


