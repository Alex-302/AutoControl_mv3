// FUN_00435a90 @ 00435a90 size=102 callers=2

void FUN_00435a90(void)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  if (DAT_004a2510 - DAT_004a250c >> 2 != 0) {
    return;
  }
  iVar2 = DAT_004a250c - DAT_004a2508 >> 2;
  if (iVar2 != 0x3fffffff) {
    uVar3 = iVar2 + 1;
    uVar4 = DAT_004a2510 - DAT_004a2508 >> 2;
    uVar1 = 0;
    if (uVar4 <= 0x3fffffff - (uVar4 >> 1)) {
      uVar1 = (uVar4 >> 1) + uVar4;
    }
    if (uVar3 <= uVar1) {
      uVar3 = uVar1;
    }
    FUN_0043c190(uVar3);
    return;
  }
                    /* WARNING: Subroutine does not return */
  FUN_00458ec4("vector<T> too long");
}


