// FUN_0044c360 @ 0044c360 size=102 callers=1

undefined4 * __thiscall FUN_0044c360(void *this,undefined4 *param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0047e689;
  local_10 = ExceptionList;
  if (param_1 != (undefined4 *)0x0) {
    local_8 = 1;
    ExceptionList = &local_10;
    *param_1 = &PTR_FUN_0048e538;
    param_1[2] = *(undefined4 *)((int)this + 8);
    FUN_00434940(param_1 + 4,(undefined1 *)((int)this + 0x10));
  }
  ExceptionList = local_10;
  return param_1;
}


