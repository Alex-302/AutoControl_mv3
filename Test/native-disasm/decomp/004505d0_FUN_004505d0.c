// FUN_004505d0 @ 004505d0 size=133 callers=1

undefined4 * __fastcall FUN_004505d0(int param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047e891;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  puVar1 = operator_new(0x30);
  if (puVar1 != (undefined4 *)0x0) {
    *puVar1 = &PTR_LAB_0048ec98;
    puVar1[0xb] = 0;
    local_8 = 3;
    if (*(undefined4 **)(param_1 + 0x2c) != (undefined4 *)0x0) {
      uVar2 = (**(code **)**(undefined4 **)(param_1 + 0x2c))(puVar1 + 2);
      puVar1[0xb] = uVar2;
    }
  }
  ExceptionList = local_10;
  return puVar1;
}


