// FUN_0041cae0 @ 0041cae0 size=266 callers=1

ushort __thiscall FUN_0041cae0(void *this,int param_1,int param_2)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  ushort uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  ushort uVar9;
  
  iVar4 = *(int *)((int)this + 0x10) - *(int *)((int)this + 0xc);
  iVar6 = iVar4 >> 0x1f;
  uVar5 = 0xffff;
  uVar9 = 0;
  uVar1 = 0xffff;
  iVar7 = 0x7fffffff;
  if (iVar4 / 0x14 + iVar6 != iVar6) {
    uVar8 = 0;
    do {
      iVar6 = *(int *)((int)this + 0xc) + uVar8 * 0x14;
      if ((*(int *)(*(int *)((int)this + 0x1c) * 4 + 4 + iVar6) <= param_2) &&
         (param_2 < *(int *)(iVar6 + 0xc + *(int *)((int)this + 0x1c) * 4))) {
        iVar2 = *(int *)(iVar6 + 4 + *(int *)((int)this + 0x18) * 4) - param_1;
        iVar4 = iVar2;
        if (iVar2 < 0) {
          iVar4 = 0;
        }
        iVar6 = param_1 - *(int *)(iVar6 + 0xc + *(int *)((int)this + 0x18) * 4);
        iVar3 = iVar6;
        if (iVar6 < 0) {
          iVar3 = 0;
        }
        if (iVar3 < iVar4) {
          iVar6 = iVar2;
        }
        if (iVar6 < 0) {
          iVar6 = 0;
        }
        uVar5 = uVar1;
        if (iVar6 < iVar7) {
          iVar7 = iVar6;
          uVar5 = uVar9;
          uVar1 = uVar9;
        }
      }
      uVar9 = uVar9 + 1;
      uVar8 = (uint)uVar9;
    } while (uVar8 < (uint)((*(int *)((int)this + 0x10) - *(int *)((int)this + 0xc)) / 0x14));
  }
  return uVar5;
}


