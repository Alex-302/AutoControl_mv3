// FUN_0041c880 @ 0041c880 size=113 callers=2

undefined4 __thiscall FUN_0041c880(void *this,int param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  ushort uVar4;
  
  uVar4 = 0;
  iVar2 = *(int *)((int)this + 0x10) - *(int *)((int)this + 0xc);
  iVar1 = iVar2 >> 0x1f;
  if (iVar2 / 0x14 + iVar1 != iVar1) {
    uVar3 = 0;
    do {
      if (param_1 == *(int *)(*(int *)((int)this + 0xc) + uVar3 * 0x14)) {
        return CONCAT22((short)(uVar3 * 5 >> 0x10),uVar4);
      }
      uVar4 = uVar4 + 1;
      uVar3 = (uint)uVar4;
    } while (uVar3 < (uint)((*(int *)((int)this + 0x10) - *(int *)((int)this + 0xc)) / 0x14));
  }
  return 0xffff;
}


