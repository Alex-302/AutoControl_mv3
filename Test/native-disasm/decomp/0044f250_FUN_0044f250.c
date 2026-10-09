// FUN_0044f250 @ 0044f250 size=104 callers=1

void __thiscall FUN_0044f250(void *this,int *param_1)

{
  void *this_00;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047e761;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  this_00 = operator_new(0x30);
  local_8 = 1;
  if (this_00 != (void *)0x0) {
    FUN_00456100(this_00,param_1);
  }
  *(void **)((int)this + 0x24) = this_00;
  ExceptionList = local_10;
  return;
}


