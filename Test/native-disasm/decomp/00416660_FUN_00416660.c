// FUN_00416660 @ 00416660 size=84 callers=2

void * __thiscall FUN_00416660(void *this,undefined4 *param_1)

{
  int *piVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_004791a6;
  local_10 = ExceptionList;
  local_8 = 0;
  piVar1 = *(int **)this;
  if (piVar1 != (int *)0x0) {
    ExceptionList = &local_10;
    (**(code **)(*piVar1 + 8))(piVar1);
  }
  *(undefined4 *)this = *param_1;
  *param_1 = 0;
  *(undefined4 *)((int)this + 4) = param_1[1];
  ExceptionList = local_10;
  return this;
}


