// FUN_0044c250 @ 0044c250 size=92 callers=1

undefined4 * __thiscall FUN_0044c250(void *this,undefined4 *param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0047e689;
  local_10 = ExceptionList;
  if (param_1 != (undefined4 *)0x0) {
    local_8 = 1;
    ExceptionList = &local_10;
    *param_1 = &PTR_LAB_0048ea80;
    FUN_00456c20(param_1 + 1,(undefined4 *)((int)this + 4));
  }
  ExceptionList = local_10;
  return param_1;
}


