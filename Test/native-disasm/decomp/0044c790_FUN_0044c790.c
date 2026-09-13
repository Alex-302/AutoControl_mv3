// FUN_0044c790 @ 0044c790 size=92 callers=1

undefined4 * __thiscall FUN_0044c790(void *this,undefined4 *param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0047e689;
  local_10 = ExceptionList;
  if (param_1 != (undefined4 *)0x0) {
    local_8 = 1;
    ExceptionList = &local_10;
    *param_1 = &PTR_FUN_0048eea0;
    FUN_00434940(param_1 + 2,(undefined1 *)((int)this + 8));
  }
  ExceptionList = local_10;
  return param_1;
}


