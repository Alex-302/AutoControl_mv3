// FUN_00409cd0 @ 00409cd0 size=507 callers=1

undefined1 * __cdecl FUN_00409cd0(undefined1 *param_1,void *param_2)

{
  char cVar1;
  undefined4 *puVar2;
  LPWSTR pWVar3;
  char *pcVar4;
  DWORD DVar5;
  ulonglong uVar6;
  void **ppvVar7;
  void *local_90 [4];
  undefined4 local_80;
  uint local_7c;
  void *local_78 [4];
  undefined4 local_68;
  uint local_64;
  void *local_60 [4];
  undefined4 local_50;
  uint local_4c;
  void *local_48 [4];
  undefined4 local_38;
  uint local_34;
  void *local_30 [4];
  undefined4 local_20;
  uint local_1c;
  undefined4 local_18;
  char local_14 [4];
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00479c7b;
  local_10 = ExceptionList;
  local_18 = 0;
  local_64 = 0xf;
  local_68 = 0;
  local_78[0] = (void *)((uint)local_78[0] & 0xffffff00);
  ExceptionList = &local_10;
  FUN_0043ace0(local_78,(uint *)"modTime",7);
  local_8 = 0;
  local_1c = 0xf;
  local_20 = 0;
  local_30[0] = (void *)((uint)local_30[0] & 0xffffff00);
  FUN_0043ace0(local_30,(uint *)&DAT_0048d054,3);
  ppvVar7 = local_60;
  local_8._0_1_ = 1;
  puVar2 = FUN_00440e70(param_2,(uint *)"content");
  FUN_00440d90(puVar2,ppvVar7);
  ppvVar7 = local_48;
  local_8._0_1_ = 2;
  puVar2 = FUN_00440e70(param_2,(uint *)&DAT_0048d05c);
  FUN_00440d90(puVar2,ppvVar7);
  local_8._0_1_ = 3;
  pWVar3 = FUN_00404640((LPWSTR)local_90,(LPCSTR)local_48);
  local_8 = CONCAT31(local_8._1_3_,4);
  pcVar4 = (char *)FUN_00440e70(param_2,(uint *)&DAT_0048d058);
  FUN_00453610(pcVar4,local_14);
  uVar6 = FUN_004411d0(param_2,local_78);
  cVar1 = FUN_00441100(param_2,local_30);
  DVar5 = FUN_00409a70(pWVar3,(char *)local_60,local_14[0],cVar1,(uint)uVar6,(int)(uVar6 >> 0x20));
  *param_1 = 0;
  *(undefined8 *)(param_1 + 8) = 0;
  FUN_00451040(param_1,DVar5);
  if (7 < local_7c) {
    FUN_00402430(local_90[0],local_7c + 1,2);
  }
  local_7c = 7;
  local_90[0] = (void *)((uint)local_90[0] & 0xffff0000);
  local_80 = 0;
  if (0xf < local_34) {
    FUN_00402430(local_48[0],local_34 + 1,1);
  }
  local_34 = 0xf;
  local_38 = 0;
  local_48[0] = (void *)((uint)local_48[0] & 0xffffff00);
  if (0xf < local_4c) {
    FUN_00402430(local_60[0],local_4c + 1,1);
  }
  local_4c = 0xf;
  local_50 = 0;
  local_60[0] = (void *)((uint)local_60[0] & 0xffffff00);
  if (0xf < local_1c) {
    FUN_00402430(local_30[0],local_1c + 1,1);
  }
  local_1c = 0xf;
  local_20 = 0;
  local_30[0] = (void *)((uint)local_30[0] & 0xffffff00);
  if (0xf < local_64) {
    FUN_00402430(local_78[0],local_64 + 1,1);
  }
  ExceptionList = local_10;
  return param_1;
}


