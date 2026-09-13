// FUN_0040e150 @ 0040e150 size=348 callers=1

undefined4 * __fastcall FUN_0040e150(undefined4 *param_1,HWND param_2)

{
  undefined4 *puVar1;
  uint uVar2;
  int *piVar3;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 *local_24;
  int *local_20;
  int *local_1c;
  uint local_18;
  int *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047a365;
  local_10 = ExceptionList;
  local_18 = 0;
  local_24 = param_1;
  if (param_2 == DAT_004a2844) {
    ExceptionList = &local_10;
    *param_1 = 0;
    piVar3 = DAT_004a2840;
    local_8 = 0xffffffff;
    *param_1 = DAT_004a2840;
    if (piVar3 != (int *)0x0) {
      (**(code **)(*piVar3 + 4))(piVar3);
      ExceptionList = local_10;
      return param_1;
    }
  }
  else {
    ExceptionList = &local_10;
    FUN_0040dfc0((int *)&local_14,param_2);
    local_8 = 1;
    if (DAT_004a23a4 < 0x74) {
      local_34 = 0x14;
      local_30 = 1;
      local_2c = 0x2a;
      local_28 = 1;
      local_8 = 2;
      piVar3 = local_14;
      if (local_14 != (int *)0x0) {
        (**(code **)(*local_14 + 4))(local_14);
      }
      puVar1 = FUN_00441810(&local_1c,(int)&local_34,piVar3);
      uVar2 = 4;
    }
    else {
      puVar1 = FUN_0040e030(&local_20,(int *)&local_14);
      uVar2 = 2;
    }
    *param_1 = 0;
    *param_1 = *puVar1;
    *puVar1 = 0;
    if ((uVar2 & 4) != 0) {
      uVar2 = uVar2 & 0xfffffffb | 1;
      local_8 = 5;
      local_18 = uVar2;
      if (local_1c != (int *)0x0) {
        (**(code **)(*local_1c + 8))(local_1c);
      }
    }
    if ((uVar2 & 2) != 0) {
      local_8 = 6;
      if (local_20 != (int *)0x0) {
        (**(code **)(*local_20 + 8))(local_20);
      }
    }
    local_8 = 7;
    if (local_14 != (int *)0x0) {
      (**(code **)(*local_14 + 8))(local_14);
    }
  }
  ExceptionList = local_10;
  return param_1;
}


