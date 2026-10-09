// FUN_00443c10 @ 00443c10 size=144 callers=1

void FUN_00443c10(void)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  iVar1 = DAT_004a3350 - DAT_004a334c >> 0x1f;
  if ((DAT_004a3350 - DAT_004a334c) / 0x14 + iVar1 == iVar1) {
    iVar1 = (DAT_004a334c - DAT_004a3348) / 0x14;
    if (iVar1 == 0xccccccc) {
                    /* WARNING: Subroutine does not return */
      FUN_00458ec4("vector<T> too long");
    }
    uVar4 = iVar1 + 1;
    uVar2 = (DAT_004a3350 - DAT_004a3348) / 0x14;
    uVar3 = 0;
    if (uVar2 <= 0xccccccc - (uVar2 >> 1)) {
      uVar3 = (uVar2 >> 1) + uVar2;
    }
    if (uVar4 <= uVar3) {
      uVar4 = uVar3;
    }
    FUN_00444490(uVar4);
  }
  return;
}


