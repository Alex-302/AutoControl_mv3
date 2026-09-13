// FUN_00454af0 @ 00454af0 size=178 callers=1

uint __fastcall FUN_00454af0(int *param_1)

{
  int iVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  
  param_1[4] = param_1[4] + 1;
  if (((param_1[0x14] & 0x8000000U) == 0) && (param_1[0x13] == 0x29)) {
                    /* WARNING: Subroutine does not return */
    FUN_00458f04(5);
  }
  if (((param_1[0x14] & 0x20U) == 0) || (param_1[0x13] != 0x3f)) {
    if ((param_1[0x10] & 0x200U) == 0) {
      uVar4 = FUN_00455d40((int)param_1);
      param_1[4] = param_1[4] + -1;
      return CONCAT31((int3)((uint)uVar4 >> 8),1);
    }
  }
  else {
    FUN_0044dfd0(param_1);
    iVar1 = param_1[0x13];
    FUN_0044dfd0(param_1);
    if (iVar1 != 0x3a) {
      if (iVar1 == 0x21) {
        uVar2 = FUN_00455d90(param_1,'\x01');
        param_1[4] = param_1[4] + -1;
        return uVar2 & 0xffffff00;
      }
      if (iVar1 == 0x3d) {
        uVar2 = FUN_00455d90(param_1,'\0');
        param_1[4] = param_1[4] + -1;
        return uVar2 & 0xffffff00;
      }
                    /* WARNING: Subroutine does not return */
      FUN_00458f04(0xe);
    }
  }
  puVar3 = FUN_0044e3a0(param_1 + 9,8);
  FUN_0044ecb0(param_1);
  uVar4 = FUN_004494b0(param_1 + 9,(int)puVar3);
  param_1[4] = param_1[4] + -1;
  return CONCAT31((int3)((uint)uVar4 >> 8),1);
}


