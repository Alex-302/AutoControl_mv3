// FUN_0044dd50 @ 0044dd50 size=147 callers=2

void FUN_0044dd50(undefined1 *param_1,undefined4 *param_2)

{
  int *piVar1;
  int *piVar2;
  undefined4 *this;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047dbd9;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *param_1 = 2;
  piVar1 = (int *)param_2[1];
  piVar2 = (int *)*param_2;
  this = operator_new(0xc);
  local_8 = 1;
  if (this != (undefined4 *)0x0) {
    *this = 0;
    this[1] = 0;
    this[2] = 0;
    FUN_00457b20(this,piVar2,piVar1);
  }
  *(undefined4 **)(param_1 + 8) = this;
  ExceptionList = local_10;
  return;
}


