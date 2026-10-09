// FUN_004559e0 @ 004559e0 size=171 callers=1

void __thiscall FUN_004559e0(void *this,uint param_1)

{
  uint uVar1;
  int *piVar2;
  undefined **ppuVar3;
  uint *puVar4;
  int iVar5;
  undefined4 *puVar6;
  uint uVar7;
  
  if ((*(uint *)((int)this + 8) & 0x100) != 0) {
    piVar2 = *(int **)(*(int *)((int)this + 0xc) + 4);
    ppuVar3 = (undefined **)*piVar2;
    if (ppuVar3 == std::ctype<char>::vftable) {
      iVar5 = __Tolower(param_1 & 0xff,(_Ctypevec *)(piVar2 + 2));
      param_1._0_1_ = (undefined1)iVar5;
    }
    else {
      param_1._0_1_ = (*(code *)ppuVar3[4])(param_1);
    }
  }
  iVar5 = *(int *)((int)this + 4);
  if (*(int *)(iVar5 + 0x1c) == 0) {
    puVar6 = operator_new(0xc);
    *puVar6 = 0;
    puVar6[1] = 0;
    puVar6[2] = 0;
    *(undefined4 **)(iVar5 + 0x1c) = puVar6;
  }
  puVar4 = *(uint **)(iVar5 + 0x1c);
  if (*puVar4 <= puVar4[1]) {
    uVar1 = puVar4[1] + 0x10;
    uVar7 = FUN_0046320d((void *)puVar4[2],uVar1);
    if (uVar7 == 0) {
                    /* WARNING: Subroutine does not return */
      FUN_00458e6a();
    }
    puVar4[2] = uVar7;
    *puVar4 = uVar1;
  }
  *(undefined1 *)(puVar4[2] + puVar4[1]) = (undefined1)param_1;
  puVar4[1] = puVar4[1] + 1;
  return;
}


