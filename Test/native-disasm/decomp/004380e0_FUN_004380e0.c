// FUN_004380e0 @ 004380e0 size=106 callers=1

void * __thiscall FUN_004380e0(void *this,int *param_1)

{
  void *this_00;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047dbd9;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  this_00 = operator_new(8);
  local_8 = 1;
  if (this_00 != (void *)0x0) {
    FUN_0044b120(this_00,param_1);
  }
  *(void **)this = this_00;
  ExceptionList = local_10;
  return this;
}


