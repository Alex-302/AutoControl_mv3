// FUN_00427280 @ 00427280 size=167 callers=1

undefined1 * __cdecl FUN_00427280(undefined1 *param_1,char *param_2)

{
  int *piVar1;
  undefined **local_4c;
  uint local_48;
  undefined ***local_28;
  undefined4 local_20;
  undefined4 local_1c;
  uint local_18 [2];
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047c5a8;
  local_10 = ExceptionList;
  local_20 = 0;
  ExceptionList = &local_10;
  FUN_00453810(param_2,local_18);
  local_48 = local_18[0];
  local_28 = &local_4c;
  local_4c = &PTR_LAB_0048e788;
  local_8 = 0;
  piVar1 = FUN_0040f6b0(DAT_004a23dc,(int *)local_28,0);
  *(undefined8 *)(param_1 + 8) = 0;
  local_1c = CONCAT31(local_1c._1_3_,piVar1 != (int *)0x0);
  *(undefined4 *)(param_1 + 8) = local_1c;
  *param_1 = 4;
  *(uint *)(param_1 + 0xc) = local_18[0];
  if (local_28 != (undefined ***)0x0) {
    (*(code *)(*local_28)[4])(local_28 != &local_4c);
  }
  ExceptionList = local_10;
  return param_1;
}


