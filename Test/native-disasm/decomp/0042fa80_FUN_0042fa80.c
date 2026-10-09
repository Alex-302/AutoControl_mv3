// FUN_0042fa80 @ 0042fa80 size=436 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_0042fa80(undefined4 *param_1)

{
  UINT UVar1;
  undefined4 uVar2;
  uint *puVar3;
  undefined4 *puVar4;
  int local_70 [9];
  int *local_4c;
  undefined **local_48;
  undefined *local_44;
  undefined4 local_34;
  undefined4 local_30;
  uint *local_2c;
  uint *local_28;
  undefined ***local_24;
  uint *local_20;
  uint *local_1c;
  int local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047d4c8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  puVar4 = FUN_00418210(&local_20);
  local_8 = 0;
  local_28 = (uint *)puVar4[1];
  local_30 = param_1[2];
  local_34 = *param_1;
  local_24 = (undefined ***)puVar4[2];
  local_2c = (uint *)*puVar4;
  *puVar4 = 0;
  puVar4[1] = 0;
  puVar4[2] = 0;
  local_4c = (int *)0x0;
  FUN_004472c0(local_70,&local_34);
  puVar3 = local_2c;
  if (local_2c != (uint *)0x0) {
    FUN_00447db0(local_2c,local_28);
    FUN_00402430(puVar3,((int)local_24 - (int)puVar3) / 0x1c,0x1c);
  }
  local_8._0_1_ = 1;
  UVar1 = param_1[1];
  uVar2 = param_1[2];
  FUN_00417e10(&DAT_004a24d0,'\0');
  FUN_00433380(&DAT_004a24d0,local_70);
  _DAT_004a2500 = uVar2;
  if (UVar1 != 0) {
    local_24 = &local_48;
    local_48 = &PTR_LAB_0048e8d8;
    local_44 = &DAT_004a24d0;
    local_8._0_1_ = 2;
    _DAT_004a24f8 = FUN_0040fd50(UVar1,(int *)local_24);
    if (local_24 != (undefined ***)0x0) {
      (*(code *)(*local_24)[4])(local_24 != &local_48);
      local_24 = (undefined ***)0x0;
    }
  }
  if (local_4c != (int *)0x0) {
    (**(code **)(*local_4c + 0x10))(local_4c != local_70);
    local_4c = (int *)0x0;
  }
  local_8 = 0xffffffff;
  if (local_20 != (uint *)0x0) {
    FUN_00447db0(local_20,local_1c);
    FUN_00402430(local_20,(local_18 - (int)local_20) / 0x1c,0x1c);
    local_20 = (uint *)0x0;
    local_1c = (uint *)0x0;
    local_18 = 0;
  }
  DAT_004a2504 = 1;
  FUN_00418490('\x01');
  ExceptionList = local_10;
  return;
}


