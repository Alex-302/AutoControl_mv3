// FUN_00451670 @ 00451670 size=188 callers=1

void __fastcall FUN_00451670(int *param_1)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  
  if (((param_1[0x14] & 0x100U) == 0) ||
     (iVar2 = FUN_004553d0(param_1,10,0x7fffffff), iVar2 == 0x7fffffff)) {
    uVar3 = FUN_00453c90(param_1);
    if ((char)uVar3 == '\0') {
      if (((param_1[0x14] & 0x20000U) != 0) &&
         (uVar3 = FUN_00453ad0(param_1,'\x01'), (char)uVar3 != '\0')) {
        return;
      }
                    /* WARNING: Subroutine does not return */
      FUN_00458f04(2);
    }
  }
  else {
    uVar1 = param_1[0x11];
    if (uVar1 != 0) {
      if (((((param_1[0x14] & 0x200U) == 0) || (uVar1 < 10)) && ((int)uVar1 <= param_1[3])) &&
         ((uVar1 < (uint)param_1[8] &&
          ((*(uint *)(param_1[5] + (uVar1 >> 5) * 4) & 1 << ((byte)uVar1 & 0x1f)) != 0)))) {
        FUN_00453ee0(param_1 + 9,uVar1);
        return;
      }
                    /* WARNING: Subroutine does not return */
      FUN_00458f04(3);
    }
    if ((param_1[0x14] & 0x100000U) == 0) {
                    /* WARNING: Subroutine does not return */
      FUN_00458f04(2);
    }
  }
  FUN_00451920(param_1 + 9,(uint)*(byte *)(param_1 + 0x11));
  return;
}


