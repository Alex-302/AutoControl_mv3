// FUN_0043b250 @ 0043b250 size=223 callers=3

void __fastcall FUN_0043b250(int param_1)

{
  int iVar1;
  void *pvVar2;
  undefined4 *puVar3;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004791b6;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *(undefined ***)(*(int *)(*(int *)(param_1 + -0x68) + 4) + -0x68 + param_1) = &PTR_LAB_0048eb44;
  iVar1 = *(int *)(*(int *)(param_1 + -0x68) + 4);
  *(int *)(iVar1 + -0x6c + param_1) = iVar1 + -0x68;
  *(undefined ***)(param_1 + -0x50) = &PTR_FUN_0048e984;
  FUN_0043df60(param_1 + -0x50);
  pvVar2 = *(void **)(param_1 + -0x1c);
  *(undefined ***)(param_1 + -0x50) = &PTR_FUN_0048e3e8;
  if (pvVar2 != (void *)0x0) {
    local_8 = 0;
    if (*(int **)((int)pvVar2 + 4) != (int *)0x0) {
      puVar3 = (undefined4 *)(**(code **)(**(int **)((int)pvVar2 + 4) + 8))();
      if (puVar3 != (undefined4 *)0x0) {
        (**(code **)*puVar3)(1);
      }
    }
    FUN_0045a6a4(pvVar2);
  }
  *(undefined ***)(*(int *)(*(int *)(param_1 + -0x68) + 4) + -0x68 + param_1) = &PTR_LAB_0048e968;
  iVar1 = *(int *)(*(int *)(param_1 + -0x68) + 4);
  *(int *)(iVar1 + -0x6c + param_1) = iVar1 + -0x20;
  *(undefined ***)(*(int *)(*(int *)(param_1 + -0x58) + 4) + -0x58 + param_1) = &PTR_LAB_0048f09c;
  iVar1 = *(int *)(*(int *)(param_1 + -0x58) + 4);
  *(int *)(iVar1 + -0x5c + param_1) = iVar1 + -8;
  *(undefined ***)(*(int *)(*(int *)(param_1 + -0x68) + 4) + -0x68 + param_1) = &PTR_LAB_0048ec6c;
  iVar1 = *(int *)(*(int *)(param_1 + -0x68) + 4);
  *(int *)(iVar1 + -0x6c + param_1) = iVar1 + -0x18;
  ExceptionList = local_10;
  return;
}


