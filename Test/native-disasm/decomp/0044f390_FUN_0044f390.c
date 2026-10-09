// FUN_0044f390 @ 0044f390 size=117 callers=1

void __thiscall FUN_0044f390(void *this,undefined4 *param_1)

{
  undefined4 *puVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047e7a9;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  puVar1 = operator_new(0x5c);
  if (puVar1 != (undefined4 *)0x0) {
    local_8 = 2;
    *puVar1 = &PTR_LAB_0048ea80;
    FUN_00456c20(puVar1 + 1,param_1);
  }
  *(undefined4 **)((int)this + 0x24) = puVar1;
  ExceptionList = local_10;
  return;
}


