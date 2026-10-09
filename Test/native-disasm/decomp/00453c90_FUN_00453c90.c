// FUN_00453c90 @ 00453c90 size=315 callers=4

undefined4 __fastcall FUN_00453c90(int *param_1)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  
  if (param_1[0x13] == -1) {
                    /* WARNING: Subroutine does not return */
    FUN_00458f04(2);
  }
  if (((param_1[0x14] & 0x10000U) == 0) ||
     (cVar1 = FUN_00455650(param_1,(char)param_1[0x12]), cVar1 == '\0')) {
    uVar2 = param_1[0x14];
    if ((uVar2 & 0x8000) != 0) {
      if ((char)param_1[0x12] == 'a') {
        param_1[0x11] = 7;
      }
      else {
        if ((char)param_1[0x12] != 'b') goto LAB_00453cfa;
        param_1[0x11] = 8;
      }
      goto LAB_00453ccd;
    }
LAB_00453cfa:
    cVar1 = (char)param_1[0x12];
    if ((cVar1 == 'c') && ((uVar2 & 0x40000) != 0)) {
      FUN_0044dfd0(param_1);
      if ((*(ushort *)
            (*(int *)(*(int *)(param_1[0xf] + 4) + 0xc) + (uint)*(byte *)(param_1 + 0x12) * 2) &
          0x103) == 0) {
                    /* WARNING: Subroutine does not return */
        FUN_00458f04(2);
      }
      uVar2 = (int)(char)*(byte *)(param_1 + 0x12) & 0x8000001f;
      if ((int)uVar2 < 0) {
        uVar2 = (uVar2 - 1 | 0xffffffe0) + 1;
      }
      param_1[0x11] = (int)(char)uVar2;
      goto LAB_00453ccd;
    }
    if ((cVar1 == 'x') && ((uVar2 & 0x1000) != 0)) {
      FUN_0044dfd0(param_1);
      iVar4 = 2;
LAB_00453d61:
      iVar4 = FUN_004553d0(param_1,0x10,iVar4);
      if (iVar4 != 0) goto LAB_00453dc4;
    }
    else {
      if ((cVar1 == 'u') && ((uVar2 & 0x800) != 0)) {
        FUN_0044dfd0(param_1);
        iVar4 = 4;
        goto LAB_00453d61;
      }
      if (((uVar2 & 0x2000) == 0) || (iVar4 = FUN_004553d0(param_1,8,3), iVar4 == 3)) {
        uVar3 = FUN_004555f0((int)param_1);
        return uVar3;
      }
      if (param_1[0x11] == 0) goto LAB_00453dc4;
    }
  }
  else {
LAB_00453ccd:
    FUN_0044dfd0(param_1);
  }
  if ((uint)param_1[0x11] < 0x100) {
    iVar4 = param_1[0x11];
    param_1[0x11] = (int)(char)iVar4;
    return CONCAT31((char)iVar4 >> 7,1);
  }
LAB_00453dc4:
                    /* WARNING: Subroutine does not return */
  FUN_00458f04(2);
}


