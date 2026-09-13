// FUN_00435710 @ 00435710 size=69 callers=1

void __fastcall FUN_00435710(int param_1)

{
  undefined4 *puVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_004791b6;
  local_10 = ExceptionList;
  local_8 = 0;
  if (*(int **)(param_1 + 0xc) != (int *)0x0) {
    ExceptionList = &local_10;
    puVar1 = (undefined4 *)(**(code **)(**(int **)(param_1 + 0xc) + 8))();
    if (puVar1 != (undefined4 *)0x0) {
      (**(code **)*puVar1)(1);
    }
  }
  ExceptionList = local_10;
  return;
}


