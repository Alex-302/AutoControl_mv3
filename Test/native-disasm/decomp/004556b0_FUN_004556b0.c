// FUN_004556b0 @ 004556b0 size=424 callers=2

void __thiscall FUN_004556b0(void *this,byte param_1,uint param_2)

{
  int *piVar1;
  undefined **ppuVar2;
  uint *puVar3;
  char cVar4;
  int iVar5;
  undefined4 *puVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  byte *pbVar10;
  uint uVar11;
  
  uVar11 = (uint)param_1;
  uVar9 = param_2 & 0xff;
  if ((*(uint *)((int)this + 8) & 0x100) != 0) {
    piVar1 = *(int **)(*(int *)((int)this + 0xc) + 4);
    ppuVar2 = (undefined **)*piVar1;
    if (ppuVar2 == std::ctype<char>::vftable) {
      iVar5 = __Tolower(uVar11,(_Ctypevec *)(piVar1 + 2));
      cVar4 = (char)iVar5;
    }
    else {
      cVar4 = (*(code *)ppuVar2[4])(uVar11);
    }
    uVar11 = (uint)cVar4;
    piVar1 = *(int **)(*(int *)((int)this + 0xc) + 4);
    ppuVar2 = (undefined **)*piVar1;
    if (ppuVar2 == std::ctype<char>::vftable) {
      iVar5 = __Tolower(uVar9,(_Ctypevec *)(piVar1 + 2));
      cVar4 = (char)iVar5;
    }
    else {
      cVar4 = (*(code *)ppuVar2[4])(uVar9);
    }
    uVar9 = (uint)cVar4;
  }
  iVar5 = *(int *)((int)this + 4);
  if (uVar11 <= uVar9) {
    while (uVar9 < *(uint *)((int)this + 0x10)) {
      if (*(int *)(iVar5 + 0x18) == 0) {
        puVar6 = operator_new(0x20);
        *puVar6 = 0;
        puVar6[1] = 0;
        puVar6[2] = 0;
        puVar6[3] = 0;
        puVar6[4] = 0;
        puVar6[5] = 0;
        puVar6[6] = 0;
        puVar6[7] = 0;
        *(undefined4 **)(iVar5 + 0x18) = puVar6;
      }
      uVar7 = uVar11 & 7;
      pbVar10 = (byte *)((uVar11 >> 3) + *(int *)(iVar5 + 0x18));
      uVar11 = uVar11 + 1;
      *pbVar10 = *pbVar10 | (byte)(1 << uVar7);
      if (uVar9 < uVar11) {
        return;
      }
    }
    if (uVar11 <= uVar9) {
      if (uVar9 - uVar11 < *(uint *)((int)this + 0x14)) {
        if (uVar11 <= uVar9) {
          do {
            FUN_004559e0(this,uVar11);
            uVar11 = uVar11 + 1;
          } while (uVar11 <= uVar9);
          return;
        }
      }
      else {
        if (*(int *)(iVar5 + 0x20) == 0) {
          puVar6 = operator_new(0xc);
          *puVar6 = 0;
          puVar6[1] = 0;
          puVar6[2] = 0;
          *(undefined4 **)(iVar5 + 0x20) = puVar6;
        }
        puVar3 = *(uint **)(iVar5 + 0x20);
        if (*puVar3 <= puVar3[1]) {
          uVar7 = puVar3[1] + 0x10;
          uVar8 = FUN_0046320d((void *)puVar3[2],uVar7);
          if (uVar8 == 0) {
                    /* WARNING: Subroutine does not return */
            FUN_00458e6a();
          }
          puVar3[2] = uVar8;
          *puVar3 = uVar7;
        }
        *(char *)(puVar3[2] + puVar3[1]) = (char)uVar11;
        puVar3[1] = puVar3[1] + 1;
        puVar3 = *(uint **)(iVar5 + 0x20);
        if (*puVar3 <= puVar3[1]) {
          uVar7 = puVar3[1] + 0x10;
          uVar11 = FUN_0046320d((void *)puVar3[2],uVar7);
          if (uVar11 == 0) {
                    /* WARNING: Subroutine does not return */
            FUN_00458e6a();
          }
          puVar3[2] = uVar11;
          *puVar3 = uVar7;
        }
        *(char *)(puVar3[2] + puVar3[1]) = (char)uVar9;
        puVar3[1] = puVar3[1] + 1;
      }
    }
  }
  return;
}


