// FUN_00451920 @ 00451920 size=171 callers=5

void __thiscall FUN_00451920(void *this,uint param_1)

{
  uint uVar1;
  int *piVar2;
  undefined **ppuVar3;
  int iVar4;
  int iVar5;
  
  if ((*(int *)(*(int *)((int)this + 4) + 4) != 6) ||
     ((*(byte *)(*(int *)((int)this + 4) + 8) & 4) != 0)) {
    FUN_00454220((int)this);
  }
  if ((*(uint *)((int)this + 8) & 0x100) == 0) {
    if ((*(uint *)((int)this + 8) & 0x800) != 0) {
      param_1._0_1_ = FUN_0044d7d0(*(void **)((int)this + 0xc),(undefined1)param_1);
    }
  }
  else {
    piVar2 = *(int **)(*(int *)((int)this + 0xc) + 4);
    ppuVar3 = (undefined **)*piVar2;
    if (ppuVar3 == std::ctype<char>::vftable) {
      iVar4 = __Tolower(param_1 & 0xff,(_Ctypevec *)(piVar2 + 2));
      param_1._0_1_ = (undefined1)iVar4;
    }
    else {
      param_1._0_1_ = (*(code *)ppuVar3[4])(param_1);
    }
  }
  iVar4 = *(int *)((int)this + 4);
  if (*(uint *)(iVar4 + 0x14) <= *(uint *)(iVar4 + 0x18)) {
    uVar1 = *(uint *)(iVar4 + 0x18) + 0x10;
    iVar5 = FUN_0046320d(*(void **)(iVar4 + 0x1c),uVar1);
    if (iVar5 == 0) {
                    /* WARNING: Subroutine does not return */
      FUN_00458e6a();
    }
    *(int *)(iVar4 + 0x1c) = iVar5;
    *(uint *)(iVar4 + 0x14) = uVar1;
  }
  *(undefined1 *)(*(int *)(iVar4 + 0x1c) + *(int *)(iVar4 + 0x18)) = (undefined1)param_1;
  *(int *)(iVar4 + 0x18) = *(int *)(iVar4 + 0x18) + 1;
  return;
}


