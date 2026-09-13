// FUN_00429cd0 @ 00429cd0 size=223 callers=1

undefined1 * __cdecl FUN_00429cd0(undefined1 *param_1,undefined1 *param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  int *piVar3;
  undefined **local_54 [2];
  undefined1 local_4c;
  undefined4 local_44;
  undefined4 local_40;
  undefined ***local_30;
  char local_2c [8];
  undefined4 local_24;
  undefined4 local_20;
  undefined8 local_1c;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047b308;
  local_10 = ExceptionList;
  local_4c = *param_2;
  local_44 = *(undefined4 *)(param_2 + 8);
  local_40 = *(undefined4 *)(param_2 + 0xc);
  ExceptionList = &local_10;
  *param_2 = 0;
  *(undefined4 *)(param_2 + 8) = 0;
  *(undefined4 *)(param_2 + 0xc) = 0;
  local_1c = 0;
  local_24 = 0;
  local_20 = 0;
  local_30 = local_54;
  local_14 = 0;
  local_54[0] = &PTR_FUN_0048e938;
  local_2c[0] = '\0';
  FUN_00434820(local_2c);
  local_8 = 0;
  piVar3 = FUN_0040f6b0(DAT_004a23dc,(int *)local_54,0);
  uVar1 = local_1c;
  *(undefined8 *)(param_1 + 8) = 0;
  local_1c = CONCAT71(local_1c._1_7_,piVar3 != (int *)0x0);
  uVar2 = local_1c;
  *(undefined4 *)(param_1 + 8) = (undefined4)local_1c;
  local_1c._4_4_ = SUB84(uVar1,4);
  *param_1 = 4;
  *(undefined4 *)(param_1 + 0xc) = local_1c._4_4_;
  if (local_30 != (undefined ***)0x0) {
    local_1c = uVar2;
    (*(code *)(*local_30)[4])(local_30 != local_54);
  }
  ExceptionList = local_10;
  return param_1;
}


