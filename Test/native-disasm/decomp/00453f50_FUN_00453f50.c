// FUN_00453f50 @ 00453f50 size=715 callers=2

void __thiscall FUN_00453f50(void *this,int param_1,int param_2,char param_3)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 uVar7;
  int iVar8;
  
  iVar8 = *(int *)((int)this + 4);
  if ((*(int *)(iVar8 + 4) == 6) && (*(int *)(iVar8 + 0x18) != 1)) {
    *(int *)(iVar8 + 0x18) = *(int *)(iVar8 + 0x18) + -1;
    FUN_00451920(this,(uint)*(byte *)(*(int *)(iVar8 + 0x1c) + *(int *)(iVar8 + 0x18)));
  }
  iVar8 = *(int *)((int)this + 4);
  if ((*(int *)(iVar8 + 4) == 9) || (*(int *)(iVar8 + 4) == 0xe)) {
    iVar8 = *(int *)(iVar8 + 0x14);
  }
  if ((param_1 == 0) && (param_2 == 1)) {
    puVar2 = operator_new(0x14);
    puVar2[1] = 0x11;
    puVar2[2] = 0;
    puVar2[3] = 0;
    puVar2[4] = 0;
    *puVar2 = &PTR_LAB_0048ecb0;
    puVar3 = operator_new(0x1c);
    puVar3[1] = 0x10;
    puVar3[2] = 0;
    puVar3[3] = 0;
    puVar3[4] = 0;
    *puVar3 = &PTR_FUN_0048e854;
    puVar3[5] = puVar2;
    puVar3[6] = 0;
    puVar4 = operator_new(0x1c);
    puVar4[1] = 0x10;
    puVar4[2] = 0;
    puVar4[3] = 0;
    puVar4[4] = 0;
    *puVar4 = &PTR_FUN_0048e854;
    puVar4[5] = puVar2;
    puVar4[6] = 0;
    puVar5 = operator_new(0x14);
    *puVar5 = &PTR_LAB_0048ecb0;
    puVar5[1] = 8;
    puVar5[2] = 0;
    puVar5[3] = 0;
    puVar5[4] = 0;
    puVar6 = operator_new(0x18);
    puVar6[1] = 9;
    puVar6[2] = 0;
    puVar6[3] = 0;
    puVar6[4] = 0;
    *puVar6 = &PTR_LAB_0048eb08;
    puVar6[5] = puVar5;
    puVar4[3] = puVar5;
    puVar5[4] = puVar4;
    puVar5[3] = puVar6;
    puVar6[4] = puVar5;
    puVar6[3] = puVar2;
    puVar3[6] = puVar4;
    puVar2[4] = *(undefined4 *)((int)this + 4);
    iVar1 = *(int *)(*(int *)((int)this + 4) + 0xc);
    if (iVar1 != 0) {
      puVar2[3] = iVar1;
      *(undefined4 **)(*(int *)(*(int *)((int)this + 4) + 0xc) + 0x10) = puVar2;
    }
    *(undefined4 **)(*(int *)((int)this + 4) + 0xc) = puVar2;
    *(undefined4 **)((int)this + 4) = puVar2;
    *(undefined4 **)(*(int *)(iVar8 + 0x10) + 0xc) = puVar3;
    puVar3[4] = *(undefined4 *)(iVar8 + 0x10);
    *(undefined4 **)(iVar8 + 0x10) = puVar3;
    puVar3[3] = iVar8;
    if (param_3 == '\0') {
      iVar1 = puVar4[3];
      uVar7 = *(undefined4 *)(iVar8 + 0x10);
      *(undefined4 *)(iVar8 + 0x10) = *(undefined4 *)(iVar1 + 0x10);
      *(undefined4 *)(iVar1 + 0x10) = uVar7;
      uVar7 = puVar3[3];
      puVar3[3] = puVar4[3];
      puVar4[3] = uVar7;
      return;
    }
  }
  else {
    puVar2 = operator_new(0x18);
    puVar2[1] = 0x13;
    puVar2[2] = 0;
    puVar2[3] = 0;
    puVar2[4] = 0;
    *puVar2 = &PTR_LAB_0048eb08;
    puVar2[5] = 0;
    puVar3 = operator_new(0x28);
    iVar1 = *(int *)(*(int *)this + 0x18);
    *(int *)(*(int *)this + 0x18) = iVar1 + 1;
    uVar7 = 0;
    puVar3[1] = 0x12;
    if (param_3 != '\0') {
      uVar7 = 2;
    }
    puVar3[3] = 0;
    puVar3[2] = uVar7;
    puVar3[5] = param_1;
    puVar3[4] = 0;
    *puVar3 = &PTR_LAB_0048e458;
    puVar3[6] = param_2;
    puVar3[7] = puVar2;
    puVar3[8] = iVar1;
    puVar3[9] = 0xffffffff;
    puVar2[5] = puVar3;
    puVar2[4] = *(undefined4 *)((int)this + 4);
    iVar1 = *(int *)(*(int *)((int)this + 4) + 0xc);
    if (iVar1 != 0) {
      puVar2[3] = iVar1;
      *(undefined4 **)(*(int *)(*(int *)((int)this + 4) + 0xc) + 0x10) = puVar2;
    }
    *(undefined4 **)(*(int *)((int)this + 4) + 0xc) = puVar2;
    *(undefined4 **)((int)this + 4) = puVar2;
    *(undefined4 **)(*(int *)(iVar8 + 0x10) + 0xc) = puVar3;
    puVar3[4] = *(undefined4 *)(iVar8 + 0x10);
    *(undefined4 **)(iVar8 + 0x10) = puVar3;
    puVar3[3] = iVar8;
  }
  return;
}


