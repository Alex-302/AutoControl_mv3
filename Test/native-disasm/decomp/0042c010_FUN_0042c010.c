// FUN_0042c010 @ 0042c010 size=208 callers=1

undefined1 * __cdecl FUN_0042c010(undefined1 *param_1,void *param_2)

{
  uint uVar1;
  char *pcVar2;
  int *piVar3;
  undefined **local_4c;
  uint local_48;
  uint local_44;
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
  pcVar2 = (char *)FUN_00440e70(param_2,(uint *)&DAT_0048d65c);
  FUN_004536b0(pcVar2,local_18);
  uVar1 = local_18[0];
  pcVar2 = (char *)FUN_00440e70(param_2,(uint *)&DAT_0048d660);
  FUN_004536b0(pcVar2,local_18);
  local_44 = local_18[0];
  local_28 = &local_4c;
  local_4c = &PTR_LAB_0048e96c;
  local_48 = uVar1;
  local_8 = 0;
  piVar3 = FUN_0040f6b0(DAT_004a2458,(int *)local_28,0);
  *(undefined8 *)(param_1 + 8) = 0;
  local_1c = CONCAT31(local_1c._1_3_,piVar3 != (int *)0x0);
  *(undefined4 *)(param_1 + 8) = local_1c;
  *param_1 = 4;
  *(uint *)(param_1 + 0xc) = local_18[0];
  if (local_28 != (undefined ***)0x0) {
    (*(code *)(*local_28)[4])(local_28 != &local_4c);
  }
  ExceptionList = local_10;
  return param_1;
}


