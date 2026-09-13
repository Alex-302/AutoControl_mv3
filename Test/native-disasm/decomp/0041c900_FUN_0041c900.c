// FUN_0041c900 @ 0041c900 size=175 callers=2

ushort __thiscall FUN_0041c900(void *this,int param_1,int param_2)

{
  int iVar1;
  undefined *puVar2;
  int iVar3;
  ushort uVar4;
  uint uVar5;
  
  iVar3 = *(int *)((int)this + 0x10) - *(int *)((int)this + 0xc);
  iVar1 = iVar3 >> 0x1f;
  uVar4 = 0;
  if (iVar3 / 0x14 + iVar1 != iVar1) {
    iVar1 = *(int *)((int)this + 0xc);
    uVar5 = 0;
    do {
      if ((((*(int *)(iVar1 + 4 + uVar5 * 0x14) <= param_1) &&
           (param_1 < *(int *)(iVar1 + 0xc + uVar5 * 0x14))) &&
          (*(int *)(iVar1 + 8 + uVar5 * 0x14) <= param_2)) &&
         (param_2 < *(int *)(iVar1 + 0x10 + uVar5 * 0x14))) {
        puVar2 = FUN_00419890(*(uint *)(iVar1 + (uint)uVar4 * 0x14));
        if (puVar2[0x24] == '\x03') {
          return 0xffff;
        }
        return uVar4;
      }
      uVar4 = uVar4 + 1;
      uVar5 = (uint)uVar4;
    } while (uVar5 < (uint)((*(int *)((int)this + 0x10) - *(int *)((int)this + 0xc)) / 0x14));
  }
  return 0xffff;
}


