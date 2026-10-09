// FUN_00440dd0 @ 00440dd0 size=148 callers=36

undefined4 __thiscall FUN_00440dd0(void *this,uint *param_1)

{
  undefined4 uVar1;
  uint uVar2;
  uint *puVar3;
  void *local_2c [4];
  undefined4 local_1c;
  uint local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047cc88;
  local_10 = ExceptionList;
  local_18 = 0xf;
  local_1c = 0;
  local_2c[0] = (void *)((uint)local_2c[0] & 0xffffff00);
  if ((char)*param_1 == '\0') {
    uVar2 = 0;
  }
  else {
    puVar3 = param_1;
    do {
      uVar2 = *puVar3;
      puVar3 = (uint *)((int)puVar3 + 1);
    } while ((char)uVar2 != '\0');
    uVar2 = (int)puVar3 - ((int)param_1 + 1);
  }
  ExceptionList = &local_10;
  FUN_0043ace0(local_2c,param_1,uVar2);
  local_8 = 0;
  uVar1 = FUN_00439c60(this,(byte *)local_2c);
  if (0xf < local_18) {
    FUN_00402430(local_2c[0],local_18 + 1,1);
  }
  ExceptionList = local_10;
  return uVar1;
}


