// FUN_00458340 @ 00458340 size=215 callers=1

undefined1 * __fastcall FUN_00458340(undefined4 *param_1,undefined4 *param_2,undefined1 *param_3)

{
  undefined4 *this;
  undefined4 *puVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined1 local_8;
  undefined3 uStack_7;
  
  puStack_c = &LAB_0047ecea;
  local_10 = ExceptionList;
  uStack_7 = 0;
  ExceptionList = &local_10;
  for (; param_1 != param_2; param_1 = param_1 + 6) {
    local_8 = 1;
    if (param_3 != (undefined1 *)0x0) {
      *(undefined8 *)(param_3 + 8) = 0;
      *param_3 = 3;
      this = operator_new(0x18);
      local_8 = 3;
      if (this != (undefined4 *)0x0) {
        this[5] = 0xf;
        this[4] = 0;
        puVar1 = this;
        if (0xf < (uint)this[5]) {
          puVar1 = (undefined4 *)*this;
        }
        *(undefined1 *)puVar1 = 0;
        FUN_0043ade0(this,param_1,0,0xffffffff);
      }
      *(undefined4 *)(param_3 + 0xc) = 0;
      *(undefined4 **)(param_3 + 8) = this;
    }
    param_3 = param_3 + 0x10;
  }
  ExceptionList = local_10;
  return param_3;
}


