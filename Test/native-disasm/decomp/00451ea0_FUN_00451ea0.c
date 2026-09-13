// FUN_00451ea0 @ 00451ea0 size=306 callers=1

undefined4 __thiscall FUN_00451ea0(void *this,int param_1)

{
  undefined **ppuVar1;
  int iVar2;
  byte bVar3;
  byte bVar4;
  int iVar5;
  int *piVar6;
  uint uVar7;
  uint uVar8;
  undefined4 local_4;
  
  bVar4 = **(byte **)this;
  if ((*(uint *)((int)this + 0x5c) & 0x100) != 0) {
    piVar6 = *(int **)(*(int *)((int)this + 0x70) + 4);
    ppuVar1 = (undefined **)*piVar6;
    if (ppuVar1 == std::ctype<char>::vftable) {
      iVar5 = __Tolower((uint)bVar4,(_Ctypevec *)(piVar6 + 2));
      bVar4 = (byte)iVar5;
    }
    else {
      bVar4 = (*(code *)ppuVar1[4])(bVar4);
    }
  }
  iVar5 = *(int *)this + 1;
  if (*(uint **)(param_1 + 0x14) != (uint *)0x0) {
    piVar6 = FUN_0044ef00(&local_4,*(uint **)(param_1 + 0x14),*(char **)this,
                          *(char **)((int)this + 0x50));
    if (*piVar6 != *(int *)this) {
      uVar7 = 1;
      iVar5 = *piVar6;
      goto LAB_00451fa0;
    }
  }
  if (*(int *)(param_1 + 0x20) != 0) {
    bVar3 = bVar4;
    if ((*(uint *)((int)this + 0x5c) & 0x800) != 0) {
      bVar3 = FUN_0044d7d0(*(void **)((int)this + 0x70),bVar4);
    }
    uVar8 = 0;
    uVar7 = *(uint *)(*(int *)(param_1 + 0x20) + 4);
    if (uVar7 != 0) {
      iVar2 = *(int *)(*(int *)(param_1 + 0x20) + 8);
      do {
        if ((*(byte *)(iVar2 + uVar8) <= bVar3) && (bVar3 <= *(byte *)(iVar2 + 1 + uVar8))) {
          uVar7 = 1;
          goto LAB_00451fa0;
        }
        uVar8 = uVar8 + 2;
      } while (uVar8 < uVar7);
    }
  }
  if ((*(int *)(param_1 + 0x18) == 0) ||
     ((*(byte *)((uint)(bVar4 >> 3) + *(int *)(param_1 + 0x18)) & (byte)(1 << (bVar4 & 7))) == 0)) {
    uVar7 = 0;
  }
  else {
    uVar7 = 1;
  }
LAB_00451fa0:
  if (uVar7 != (*(uint *)(param_1 + 8) & 1)) {
    *(int *)this = iVar5;
    return 1;
  }
  return 0;
}


