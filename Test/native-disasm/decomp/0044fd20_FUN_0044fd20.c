// FUN_0044fd20 @ 0044fd20 size=91 callers=1

undefined4 * __thiscall FUN_0044fd20(void *this,undefined4 param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047e810;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  puVar1 = FUN_004488f0(this);
  local_8 = 0;
  *(undefined2 *)(puVar1 + 3) = 0;
  FUN_00456070(puVar1 + 4,puVar1 + 4,param_2);
  ExceptionList = local_10;
  return puVar1;
}


