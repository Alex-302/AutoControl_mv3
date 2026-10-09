// FUN_00455860 @ 00455860 size=212 callers=2

undefined4 * __thiscall FUN_00455860(void *this,char param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047eaa0;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  puVar2 = operator_new(0x18);
  local_8 = 0;
  puVar2[2] = 0;
  puVar2[3] = 0;
  puVar2[1] = (param_1 != '\0') + 10;
  puVar2[4] = 0;
  *puVar2 = &PTR_FUN_0048e43c;
  puVar2[5] = 0;
  puVar3 = operator_new(0x14);
  *puVar3 = &PTR_LAB_0048ecb0;
  puVar3[1] = 1;
  puVar3[2] = 0;
  puVar3[3] = 0;
  puVar3[4] = 0;
  puVar2[4] = *(undefined4 *)((int)this + 4);
  iVar1 = *(int *)(*(int *)((int)this + 4) + 0xc);
  if (iVar1 != 0) {
    puVar2[3] = iVar1;
    *(undefined4 **)(*(int *)(*(int *)((int)this + 4) + 0xc) + 0x10) = puVar2;
  }
  *(undefined4 **)(*(int *)((int)this + 4) + 0xc) = puVar2;
  puVar2[5] = puVar3;
  puVar3[4] = puVar2;
  *(undefined4 **)((int)this + 4) = puVar3;
  ExceptionList = local_10;
  return puVar2;
}


