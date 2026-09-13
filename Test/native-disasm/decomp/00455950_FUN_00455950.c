// FUN_00455950 @ 00455950 size=132 callers=8

void __thiscall FUN_00455950(void *this,uint param_1)

{
  int *piVar1;
  undefined **ppuVar2;
  int iVar3;
  byte bVar4;
  uint uVar5;
  undefined4 *puVar6;
  byte *pbVar7;
  
  if ((*(uint *)((int)this + 8) & 0x100) == 0) {
    uVar5 = param_1 & 0xff;
  }
  else {
    piVar1 = *(int **)(*(int *)((int)this + 0xc) + 4);
    ppuVar2 = (undefined **)*piVar1;
    if (ppuVar2 == std::ctype<char>::vftable) {
      uVar5 = __Tolower(param_1 & 0xff,(_Ctypevec *)(piVar1 + 2));
      uVar5 = uVar5 & 0xff;
    }
    else {
      bVar4 = (*(code *)ppuVar2[4])(param_1);
      uVar5 = (uint)bVar4;
    }
  }
  iVar3 = *(int *)((int)this + 4);
  if (*(int *)(iVar3 + 0x18) == 0) {
    puVar6 = operator_new(0x20);
    *puVar6 = 0;
    puVar6[1] = 0;
    puVar6[2] = 0;
    puVar6[3] = 0;
    puVar6[4] = 0;
    puVar6[5] = 0;
    puVar6[6] = 0;
    puVar6[7] = 0;
    *(undefined4 **)(iVar3 + 0x18) = puVar6;
  }
  pbVar7 = (byte *)(*(int *)(iVar3 + 0x18) + (uVar5 >> 3));
  *pbVar7 = *pbVar7 | (byte)(1 << (uVar5 & 7));
  return;
}


