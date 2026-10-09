// FUN_0043bd50 @ 0043bd50 size=95 callers=1

void __fastcall FUN_0043bd50(undefined4 *param_1)

{
  void *pvVar1;
  undefined4 *puVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_004791b6;
  local_10 = ExceptionList;
  pvVar1 = (void *)param_1[0xd];
  ExceptionList = &local_10;
  *param_1 = &PTR_FUN_0048e3e8;
  if (pvVar1 != (void *)0x0) {
    local_8 = 0;
    if (*(int **)((int)pvVar1 + 4) != (int *)0x0) {
      puVar2 = (undefined4 *)(**(code **)(**(int **)((int)pvVar1 + 4) + 8))();
      if (puVar2 != (undefined4 *)0x0) {
        (**(code **)*puVar2)(1);
      }
    }
    FUN_0045a6a4(pvVar1);
  }
  ExceptionList = local_10;
  return;
}


