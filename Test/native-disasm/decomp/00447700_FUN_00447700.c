// FUN_00447700 @ 00447700 size=92 callers=1

undefined4 * __thiscall FUN_00447700(void *this,undefined4 *param_1,undefined1 *param_2)

{
  undefined4 *puVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047e4f0;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  puVar1 = FUN_004488f0(this);
  local_8 = 0;
  *(undefined2 *)(puVar1 + 3) = 0;
  FUN_00452f60(puVar1 + 4,param_1,param_2);
  ExceptionList = local_10;
  return puVar1;
}


