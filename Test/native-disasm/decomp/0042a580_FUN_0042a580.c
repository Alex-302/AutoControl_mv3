// FUN_0042a580 @ 0042a580 size=142 callers=1

void FUN_0042a580(void)

{
  void *this;
  uint uVar1;
  ushort uVar2;
  undefined *puVar3;
  undefined4 uVar4;
  HMENU pHVar5;
  
  if ((DAT_004a2998 != 0) || (DAT_004a299c != (void *)0x0)) {
    puVar3 = FUN_00419890(DAT_004a29c4);
    uVar1 = DAT_004a29c4;
    this = DAT_004a299c;
    if (puVar3[0x24] == '3') {
      if (DAT_004a2998 != 0) {
        pHVar5 = *(HMENU *)(puVar3 + 0x1c);
        if (pHVar5 == (HMENU)0x0) {
          puVar3 = FUN_00419890(DAT_004a29c4);
          pHVar5 = *(HMENU *)(puVar3 + 0x1c);
        }
        uVar2 = FUN_0041d340(pHVar5,uVar1);
        FUN_0041d510(pHVar5,uVar2);
        return;
      }
      uVar4 = FUN_0041c880(DAT_004a299c,DAT_004a29c4);
      FUN_0041c080(this,(ushort)uVar4);
      FUN_0041c140((int)this);
    }
  }
  return;
}


