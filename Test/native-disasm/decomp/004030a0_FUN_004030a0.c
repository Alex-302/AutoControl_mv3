// FUN_004030a0 @ 004030a0 size=68 callers=1

int __thiscall FUN_004030a0(void *this,int param_1)

{
  int *piVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_004791a6;
  local_10 = ExceptionList;
  local_8 = 0;
  piVar1 = *(int **)(*(int *)((int)this + 0x30) + 4);
  ExceptionList = &local_10;
  *(int **)(param_1 + 4) = piVar1;
  (**(code **)(*piVar1 + 4))();
  ExceptionList = local_10;
  return param_1;
}


