// FUN_00428b20 @ 00428b20 size=807 callers=1

undefined1 * __cdecl FUN_00428b20(undefined1 *param_1,void *param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  bool bVar3;
  undefined1 *puVar4;
  char *pcVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  undefined4 local_fc [23];
  undefined4 local_a0;
  undefined **local_9c [2];
  undefined4 local_94;
  undefined1 local_8c;
  undefined4 local_84;
  undefined4 local_80;
  undefined ***local_78;
  undefined4 local_74;
  void *local_70;
  undefined4 local_6c;
  void *local_68;
  uint local_64;
  int local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  void *local_50;
  void *local_4c;
  void *local_48;
  undefined4 local_44;
  int local_40;
  undefined4 local_3c;
  uint local_38;
  void *local_34;
  undefined4 local_30;
  int local_2c [3];
  undefined4 *local_20;
  undefined8 local_1c;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047c842;
  local_10 = ExceptionList;
  local_a0 = 0;
  ExceptionList = &local_10;
  FUN_00442330(&local_20,param_2);
  local_8 = 0;
  local_38 = 0xf;
  local_3c = 0;
  local_4c = (void *)((uint)local_4c & 0xffffff00);
  FUN_0043ace0(&local_4c,(uint *)"extEvtNames",0xb);
  local_8._0_1_ = 2;
  local_34 = (void *)((uint)local_34 & 0xffffff00);
  FUN_004381d0(local_2c,'\0');
  local_8._0_1_ = 3;
  puVar4 = (undefined1 *)FUN_004343d0(param_2,(byte *)&local_4c);
  pcVar5 = (char *)FUN_00440e70(param_2,(uint *)"neededCaretSt");
  FUN_004536b0(pcVar5,(uint *)((int)&local_1c + 4));
  local_6c = local_1c._4_4_;
  local_8c = *puVar4;
  local_84 = *(undefined4 *)(puVar4 + 8);
  local_80 = *(undefined4 *)(puVar4 + 0xc);
  *puVar4 = 0;
  *(undefined4 *)(puVar4 + 8) = 0;
  *(undefined4 *)(puVar4 + 0xc) = 0;
  local_1c = 0;
  local_5c = 0;
  local_58 = 0;
  local_78 = local_9c;
  local_9c[0] = &PTR_FUN_0048e538;
  local_94 = local_6c;
  local_64 = local_64 & 0xffffff00;
  FUN_00434820((char *)&local_64);
  local_8 = CONCAT31(local_8._1_3_,4);
  FUN_0040f6b0(DAT_004a23dc,(int *)local_9c,0);
  if (local_78 != (undefined ***)0x0) {
    (*(code *)(*local_78)[4])(local_78 != local_9c);
    local_78 = (undefined ***)0x0;
  }
  FUN_00434820((char *)&local_34);
  local_8 = local_8 & 0xffffff00;
  if (0xf < local_38) {
    FUN_00402430(local_4c,local_38 + 1,1);
  }
  pcVar5 = (char *)FUN_00440e70(param_2,(uint *)"gestures");
  puVar6 = FUN_00419480(&local_54,pcVar5);
  local_8._0_1_ = 5;
  puVar7 = FUN_00440e70(param_2,(uint *)"combinSequences");
  puVar7 = FUN_00405a40(&local_74,puVar7);
  local_8._0_1_ = 6;
  puVar8 = FUN_00422160(local_20,&local_34,0x4a2650);
  local_8._0_1_ = 7;
  FUN_00429030(local_fc,puVar8,puVar7,puVar6,&local_20,param_2);
  local_78 = (undefined ***)0x0;
  local_8._0_1_ = 9;
  FUN_0044f390(local_9c,local_fc);
  FUN_004290e0(local_fc);
  local_8 = CONCAT31(local_8._1_3_,10);
  bVar3 = FUN_0040f7a0(DAT_004a2458,(int *)local_9c);
  uVar1 = local_1c;
  local_1c = CONCAT71(local_1c._1_7_,bVar3);
  uVar2 = local_1c;
  *(undefined8 *)(param_1 + 8) = 0;
  *(undefined4 *)(param_1 + 8) = (undefined4)local_1c;
  local_1c._4_4_ = SUB84(uVar1,4);
  *param_1 = 4;
  *(undefined4 *)(param_1 + 0xc) = local_1c._4_4_;
  local_1c = uVar2;
  if (local_78 != (undefined ***)0x0) {
    (*(code *)(*local_78)[4])(local_78 != local_9c);
  }
  if (local_34 != (void *)0x0) {
    FUN_00402430(local_34,local_2c[0] - (int)local_34 >> 2,4);
    local_34 = (void *)0x0;
    local_30 = 0;
    local_2c[0] = 0;
  }
  if (local_68 != (void *)0x0) {
    FUN_00402430(local_68,local_60 - (int)local_68 >> 2,4);
    local_68 = (void *)0x0;
    local_64 = 0;
    local_60 = 0;
  }
  FUN_0043edd0((int *)&local_70);
  FID_conflict__free(local_70);
  if (local_48 != (void *)0x0) {
    FUN_00402430(local_48,local_40 - (int)local_48 >> 2,4);
    local_48 = (void *)0x0;
    local_44 = 0;
    local_40 = 0;
  }
  FUN_0043e550((int *)&local_50);
  FID_conflict__free(local_50);
  if (local_20 != (undefined4 *)0x0) {
    FUN_0043c010(local_20);
    FUN_0045a6a4(local_20);
  }
  ExceptionList = local_10;
  return param_1;
}


