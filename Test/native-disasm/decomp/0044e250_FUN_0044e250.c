// FUN_0044e250 @ 0044e250 size=185 callers=2

undefined4 * __thiscall FUN_0044e250(void *this,int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  puVar2 = operator_new(0x14);
  puVar2[4] = 0;
  puVar2[1] = 0x11;
  puVar2[2] = 0;
  puVar2[3] = 0;
  *puVar2 = &PTR_LAB_0048ecb0;
  puVar2[4] = *(undefined4 *)((int)this + 4);
  iVar1 = *(int *)(*(int *)((int)this + 4) + 0xc);
  if (iVar1 != 0) {
    puVar2[3] = iVar1;
    *(undefined4 **)(*(int *)(*(int *)((int)this + 4) + 0xc) + 0x10) = puVar2;
  }
  *(undefined4 **)(*(int *)((int)this + 4) + 0xc) = puVar2;
  *(undefined4 **)((int)this + 4) = puVar2;
  puVar3 = operator_new(0x1c);
  puVar3[5] = puVar2;
  puVar3[1] = 0x10;
  puVar3[2] = 0;
  puVar3[3] = 0;
  puVar3[4] = 0;
  *puVar3 = &PTR_FUN_0048e854;
  puVar3[6] = 0;
  iVar1 = *(int *)(param_1 + 0xc);
  *(undefined4 **)(*(int *)(iVar1 + 0x10) + 0xc) = puVar3;
  puVar3[4] = *(undefined4 *)(iVar1 + 0x10);
  *(undefined4 **)(iVar1 + 0x10) = puVar3;
  puVar3[3] = iVar1;
  return puVar2;
}


