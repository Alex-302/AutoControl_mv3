// FUN_00429b40 @ 00429b40 size=260 callers=1

undefined1 * __cdecl FUN_00429b40(undefined1 *param_1,void *param_2)

{
  char *pcVar1;
  int *piVar2;
  undefined **local_64;
  uint local_60;
  uint local_5c;
  undefined ***local_40;
  void *local_38 [4];
  undefined4 local_28;
  uint local_24;
  undefined4 local_20;
  undefined4 local_1c;
  uint local_18 [2];
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047c950;
  local_10 = ExceptionList;
  local_20 = 0;
  ExceptionList = &local_10;
  pcVar1 = (char *)FUN_00440e70(param_2,(uint *)"tabId");
  FUN_004536b0(pcVar1,local_18);
  local_24 = 0xf;
  local_28 = 0;
  local_38[0] = (void *)((uint)local_38[0] & 0xffffff00);
  FUN_0043ace0(local_38,(uint *)&DAT_0048d814,3);
  local_8 = 0;
  local_60 = FUN_00442390(param_2,local_38);
  if (0xf < local_24) {
    FUN_00402430(local_38[0],local_24 + 1,1);
  }
  local_5c = local_18[0];
  local_40 = &local_64;
  local_64 = &PTR_LAB_0048eac8;
  local_8 = 1;
  piVar2 = FUN_0040f6b0(DAT_004a23dc,(int *)local_40,0);
  *(undefined8 *)(param_1 + 8) = 0;
  local_1c = CONCAT31(local_1c._1_3_,piVar2 != (int *)0x0);
  *(undefined4 *)(param_1 + 8) = local_1c;
  *param_1 = 4;
  *(uint *)(param_1 + 0xc) = local_18[0];
  if (local_40 != (undefined ***)0x0) {
    (*(code *)(*local_40)[4])(local_40 != &local_64);
  }
  ExceptionList = local_10;
  return param_1;
}


