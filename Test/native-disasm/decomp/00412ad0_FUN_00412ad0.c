// FUN_00412ad0 @ 00412ad0 size=245 callers=4

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00412ad0(void)

{
  undefined1 *puVar1;
  uint uVar2;
  int iVar3;
  uint *puVar4;
  undefined1 local_d;
  uint local_c;
  
  uVar2 = 0;
  local_d = 0;
  puVar4 = DAT_004a28b0;
  if (DAT_004a28bc != 0) {
    if (((int)DAT_004a28bc < 0) && (DAT_004a28bc != 0)) {
      iVar3 = -((-DAT_004a28bc - 1 >> 5) * 4 + 4);
    }
    else {
      iVar3 = (DAT_004a28bc >> 5) * 4;
    }
    puVar4 = (uint *)((int)DAT_004a28b0 + iVar3);
    uVar2 = DAT_004a28bc & 0x1f;
  }
  local_c = local_c & 0xffffff00;
  FUN_0044a210(&local_d,local_c,DAT_004a28b0,0,puVar4,uVar2);
  DAT_004a23a2 = 0;
  puVar1 = &DAT_004a26b8;
  iVar3 = 0;
  do {
    iVar3 = iVar3 + 1;
    *puVar1 = 0;
    puVar1 = puVar1 + 1;
  } while (iVar3 != 10);
  uVar2 = 0;
  local_d = 0;
  puVar4 = DAT_004a2598;
  if (DAT_004a25a4 != 0) {
    if (((int)DAT_004a25a4 < 0) && (DAT_004a25a4 != 0)) {
      iVar3 = -((-DAT_004a25a4 - 1 >> 5) * 4 + 4);
    }
    else {
      iVar3 = (DAT_004a25a4 >> 5) * 4;
    }
    puVar4 = (uint *)((int)DAT_004a2598 + iVar3);
    uVar2 = DAT_004a25a4 & 0x1f;
  }
  local_c = local_c & 0xffffff00;
  FUN_0044a210(&local_d,local_c,DAT_004a2598,0,puVar4,uVar2);
  _DAT_004a2434 = 0;
  return;
}


