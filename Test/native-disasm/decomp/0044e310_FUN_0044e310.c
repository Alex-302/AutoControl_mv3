// FUN_0044e310 @ 0044e310 size=135 callers=2

void __thiscall FUN_0044e310(void *this,int param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  
  iVar2 = *(int *)(param_1 + 0xc);
  iVar3 = *(int *)(param_2 + 0xc);
  *(undefined4 *)(param_2 + 0xc) = 0;
  iVar4 = *(int *)((int)this + 4);
  *(int *)((int)this + 4) = param_2;
  *(undefined4 *)(param_2 + 0xc) = 0;
  *(int *)(iVar4 + 0xc) = param_2;
  piVar1 = (int *)(iVar2 + 0x18);
  iVar4 = *piVar1;
  while (iVar4 != 0) {
    iVar2 = *piVar1;
    piVar1 = (int *)(iVar2 + 0x18);
    iVar4 = *(int *)(iVar2 + 0x18);
  }
  puVar5 = operator_new(0x1c);
  puVar5[5] = param_2;
  puVar5[1] = 0x10;
  puVar5[2] = 0;
  puVar5[3] = 0;
  puVar5[4] = 0;
  *puVar5 = &PTR_FUN_0048e854;
  puVar5[6] = 0;
  *(undefined4 **)(iVar2 + 0x18) = puVar5;
  puVar5[3] = iVar3;
  *(undefined4 *)(iVar3 + 0x10) = *(undefined4 *)(iVar2 + 0x18);
  return;
}


