// FUN_0044b4b0 @ 0044b4b0 size=108 callers=1

undefined4 * __thiscall FUN_0044b4b0(void *this,undefined4 *param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0047e689;
  local_10 = ExceptionList;
  if (param_1 != (undefined4 *)0x0) {
    local_8 = 1;
    ExceptionList = &local_10;
    *param_1 = &PTR_FUN_0048e7d0;
    param_1[1] = *(undefined4 *)((int)this + 4);
    param_1[2] = *(undefined4 *)((int)this + 8);
    FUN_00457260(param_1 + 3,(int *)((int)this + 0xc));
  }
  ExceptionList = local_10;
  return param_1;
}


