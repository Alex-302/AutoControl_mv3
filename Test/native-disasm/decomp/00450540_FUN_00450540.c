// FUN_00450540 @ 00450540 size=117 callers=1

undefined4 * __fastcall FUN_00450540(int param_1)

{
  undefined4 *puVar1;
  undefined4 extraout_EDX;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047e859;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  puVar1 = operator_new(0x5c);
  if (puVar1 != (undefined4 *)0x0) {
    local_8 = 2;
    *puVar1 = &PTR_LAB_0048ea80;
    FUN_00457150(puVar1 + 1,extraout_EDX,(int *)(param_1 + 4));
  }
  ExceptionList = local_10;
  return puVar1;
}


