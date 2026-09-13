// FUN_00438070 @ 00438070 size=105 callers=1

void * __thiscall FUN_00438070(void *this,int *param_1)

{
  void *this_00;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047dbd9;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  this_00 = operator_new(0xc);
  local_8 = 1;
  if (this_00 != (void *)0x0) {
    FUN_00448980(this_00,param_1);
  }
  *(void **)this = this_00;
  ExceptionList = local_10;
  return this;
}


