// FUN_00439f00 @ 00439f00 size=144 callers=2

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00439f00(void)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  iVar1 = _DAT_004a2558 - DAT_004a2554 >> 0x1f;
  if ((_DAT_004a2558 - DAT_004a2554) / 0x18 + iVar1 == iVar1) {
    iVar1 = (DAT_004a2554 - _DAT_004a2550) / 0x18;
    if (iVar1 == 0xaaaaaaa) {
                    /* WARNING: Subroutine does not return */
      FUN_00458ec4("vector<T> too long");
    }
    uVar4 = iVar1 + 1;
    uVar2 = (_DAT_004a2558 - _DAT_004a2550) / 0x18;
    uVar3 = 0;
    if (uVar2 <= 0xaaaaaaa - (uVar2 >> 1)) {
      uVar3 = (uVar2 >> 1) + uVar2;
    }
    if (uVar4 <= uVar3) {
      uVar4 = uVar3;
    }
    FUN_0043d670(uVar4);
  }
  return;
}


