// FUN_0044ddf0 @ 0044ddf0 size=147 callers=1

void FUN_0044ddf0(undefined1 *param_1,undefined4 *param_2)

{
  undefined2 *puVar1;
  undefined2 *puVar2;
  undefined4 *this;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047dbd9;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *param_1 = 2;
  puVar1 = (undefined2 *)param_2[1];
  puVar2 = (undefined2 *)*param_2;
  this = operator_new(0xc);
  local_8 = 1;
  if (this != (undefined4 *)0x0) {
    *this = 0;
    this[1] = 0;
    this[2] = 0;
    FUN_00457ba0(this,puVar2,puVar1);
  }
  *(undefined4 **)(param_1 + 8) = this;
  ExceptionList = local_10;
  return;
}


