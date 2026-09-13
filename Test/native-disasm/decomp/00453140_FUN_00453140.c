// FUN_00453140 @ 00453140 size=102 callers=2

undefined4 * __thiscall FUN_00453140(void *this,undefined4 *param_1)

{
  undefined4 *puVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047e9b1;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  puVar1 = FUN_004488f0(this);
  *(undefined2 *)(puVar1 + 3) = 0;
  local_8 = 1;
  if (puVar1 + 4 != (undefined4 *)0x0) {
    FUN_00456ba0(puVar1 + 4,param_1);
  }
  ExceptionList = local_10;
  return puVar1;
}


