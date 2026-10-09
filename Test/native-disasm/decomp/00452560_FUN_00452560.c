// FUN_00452560 @ 00452560 size=308 callers=1

undefined4 __thiscall FUN_00452560(void *this,int param_1)

{
  int *piVar1;
  undefined **ppuVar2;
  char *pcVar3;
  byte bVar4;
  byte bVar5;
  int iVar6;
  char *pcVar7;
  uint uVar8;
  uint uVar9;
  char *pcVar10;
  
  bVar5 = **(byte **)this;
  if ((*(uint *)((int)this + 0x5c) & 0x100) != 0) {
    piVar1 = *(int **)(*(int *)((int)this + 0x70) + 4);
    ppuVar2 = (undefined **)*piVar1;
    if (ppuVar2 == std::ctype<char>::vftable) {
      iVar6 = __Tolower((uint)bVar5,(_Ctypevec *)(piVar1 + 2));
      bVar5 = (byte)iVar6;
    }
    else {
      bVar5 = (*(code *)ppuVar2[4])(bVar5);
    }
  }
  pcVar3 = *(char **)this;
  pcVar10 = pcVar3 + 1;
  if ((*(uint **)(param_1 + 0x14) == (uint *)0x0) ||
     (pcVar7 = (char *)FUN_0044f050(pcVar3,*(char **)((int)this + 0x50),*(uint **)(param_1 + 0x14)),
     pcVar7 == pcVar3)) {
    if (*(int *)(param_1 + 0x20) != 0) {
      bVar4 = bVar5;
      if ((*(uint *)((int)this + 0x5c) & 0x800) != 0) {
        bVar4 = FUN_0044d7d0(*(void **)((int)this + 0x70),bVar5);
      }
      uVar9 = 0;
      uVar8 = *(uint *)(*(int *)(param_1 + 0x20) + 4);
      if (uVar8 != 0) {
        iVar6 = *(int *)(*(int *)(param_1 + 0x20) + 8);
        do {
          if ((*(byte *)(iVar6 + uVar9) <= bVar4) && (bVar4 <= *(byte *)(iVar6 + 1 + uVar9))) {
            uVar8 = 1;
            goto LAB_00452662;
          }
          uVar9 = uVar9 + 2;
        } while (uVar9 < uVar8);
      }
    }
    if ((*(int *)(param_1 + 0x18) == 0) ||
       ((*(byte *)((uint)(bVar5 >> 3) + *(int *)(param_1 + 0x18)) & (byte)(1 << (bVar5 & 7))) == 0))
    {
      uVar8 = 0;
    }
    else {
      uVar8 = 1;
    }
  }
  else {
    uVar8 = 1;
    pcVar10 = pcVar7;
  }
LAB_00452662:
  if (uVar8 != (*(uint *)(param_1 + 8) & 1)) {
    *(char **)this = pcVar10;
    return 1;
  }
  return 0;
}


