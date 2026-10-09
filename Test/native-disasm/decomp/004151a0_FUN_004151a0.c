// FUN_004151a0 @ 004151a0 size=147 callers=18

void __fastcall FUN_004151a0(int *param_1)

{
  int *piVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004791b6;
  local_10 = ExceptionList;
  piVar1 = param_1 + 5;
  ExceptionList = &local_10;
  if (7 < (uint)param_1[10]) {
    ExceptionList = &local_10;
    FUN_00402430((void *)*piVar1,param_1[10] + 1,2);
  }
  param_1[10] = 7;
  param_1[9] = 0;
  if (7 < (uint)param_1[10]) {
    piVar1 = (int *)*piVar1;
  }
  *(undefined2 *)piVar1 = 0;
  FUN_00432380(param_1 + 4);
  FUN_00432380(param_1 + 3);
  FUN_00432380(param_1 + 2);
  FUN_00432380(param_1 + 1);
  local_8 = 0;
  piVar1 = (int *)*param_1;
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 8))(piVar1);
  }
  ExceptionList = local_10;
  return;
}


