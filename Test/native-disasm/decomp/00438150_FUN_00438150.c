// FUN_00438150 @ 00438150 size=126 callers=1

void * __thiscall FUN_00438150(void *this,undefined4 *param_1)

{
  undefined1 *this_00;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047dbd9;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  this_00 = operator_new(0x18);
  local_8 = 1;
  if (this_00 != (undefined1 *)0x0) {
    *(undefined4 *)(this_00 + 0x14) = 0xf;
    *(undefined4 *)(this_00 + 0x10) = 0;
    *this_00 = 0;
    FUN_0043ade0(this_00,param_1,0,0xffffffff);
  }
  *(undefined1 **)this = this_00;
  ExceptionList = local_10;
  return this;
}


