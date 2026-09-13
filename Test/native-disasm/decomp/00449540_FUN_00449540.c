// FUN_00449540 @ 00449540 size=105 callers=4

undefined4 * __thiscall FUN_00449540(void *this,undefined4 param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = operator_new(0x18);
  puVar2[4] = 0;
  puVar2[1] = 0xd;
  puVar2[2] = 0;
  puVar2[3] = 0;
  *puVar2 = &PTR_LAB_0048eb08;
  puVar2[5] = param_1;
  puVar2[4] = *(undefined4 *)((int)this + 4);
  iVar1 = *(int *)(*(int *)((int)this + 4) + 0xc);
  if (iVar1 != 0) {
    puVar2[3] = iVar1;
    *(undefined4 **)(*(int *)(*(int *)((int)this + 4) + 0xc) + 0x10) = puVar2;
  }
  *(undefined4 **)(*(int *)((int)this + 4) + 0xc) = puVar2;
  *(undefined4 **)((int)this + 4) = puVar2;
  return puVar2;
}


