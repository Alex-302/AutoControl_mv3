// FUN_00402800 @ 00402800 size=62 callers=5

void __fastcall FUN_00402800(int param_1)

{
  undefined4 *puVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 uStack_8;
  
  uStack_8 = 0xffffffff;
  puStack_c = &LAB_004790f0;
  local_10 = ExceptionList;
  if (*(int **)(param_1 + 4) != (int *)0x0) {
    ExceptionList = &local_10;
    puVar1 = (undefined4 *)(**(code **)(**(int **)(param_1 + 4) + 8))();
    if (puVar1 != (undefined4 *)0x0) {
      (**(code **)*puVar1)(1);
    }
  }
  ExceptionList = local_10;
  return;
}


