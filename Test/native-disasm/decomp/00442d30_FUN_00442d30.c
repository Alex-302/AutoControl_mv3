// FUN_00442d30 @ 00442d30 size=118 callers=1

undefined1 * FUN_00442d30(void)

{
  undefined1 *this;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047dbd9;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  this = operator_new(0x18);
  local_8 = 1;
  if (this != (undefined1 *)0x0) {
    *(undefined4 *)(this + 0x14) = 0xf;
    *(undefined4 *)(this + 0x10) = 0;
    *this = 0;
    FUN_0043ace0(this,(uint *)&DAT_0048e75c,0);
  }
  ExceptionList = local_10;
  return this;
}


