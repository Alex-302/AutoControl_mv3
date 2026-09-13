// FUN_004494b0 @ 004494b0 size=139 callers=12

void __thiscall FUN_004494b0(void *this,int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 4);
  if (iVar2 == 8) {
    iVar2 = 9;
  }
  else if (iVar2 == 10) {
    iVar2 = 0xc;
  }
  else {
    iVar2 = (uint)(iVar2 != 0xb) * 2 + 0xc;
  }
  puVar1 = operator_new(0x18);
  puVar1[4] = 0;
  puVar1[1] = iVar2;
  puVar1[2] = 0;
  puVar1[3] = 0;
  *puVar1 = &PTR_LAB_0048eb08;
  puVar1[5] = param_1;
  puVar1[4] = *(undefined4 *)((int)this + 4);
  iVar2 = *(int *)(*(int *)((int)this + 4) + 0xc);
  if (iVar2 != 0) {
    puVar1[3] = iVar2;
    *(undefined4 **)(*(int *)(*(int *)((int)this + 4) + 0xc) + 0x10) = puVar1;
  }
  *(undefined4 **)(*(int *)((int)this + 4) + 0xc) = puVar1;
  *(undefined4 **)((int)this + 4) = puVar1;
  return;
}


