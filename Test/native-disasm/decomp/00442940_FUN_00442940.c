// FUN_00442940 @ 00442940 size=107 callers=1

undefined4 * FUN_00442940(void)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047dbd9;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  puVar1 = operator_new(8);
  local_8 = 1;
  if (puVar1 != (undefined4 *)0x0) {
    *puVar1 = 0;
    puVar1[1] = 0;
    uVar2 = FUN_00449130();
    *puVar1 = uVar2;
  }
  ExceptionList = local_10;
  return puVar1;
}


