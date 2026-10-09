// FUN_0042c440 @ 0042c440 size=650 callers=1

void __fastcall FUN_0042c440(undefined4 *param_1)

{
  char cVar1;
  char cVar2;
  undefined1 uVar3;
  int iVar4;
  undefined4 *puVar5;
  char *pcVar6;
  char *extraout_ECX;
  uint *puVar7;
  void *local_80 [4];
  undefined4 local_70;
  uint local_6c;
  void *local_68 [4];
  undefined4 local_58;
  uint local_54;
  char local_50 [16];
  char local_40 [8];
  undefined4 local_38;
  undefined4 local_34;
  void *local_30 [2];
  char local_28 [8];
  undefined8 local_20;
  undefined8 local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047cd28;
  local_10 = ExceptionList;
  local_18 = ZEXT48((int *)local_18);
  local_54 = 0xf;
  local_58 = 0;
  local_68[0] = (void *)((uint)local_68[0] & 0xffffff00);
  ExceptionList = &local_10;
  FUN_0043ace0(local_68,(uint *)&DAT_0048da74,3);
  if (*(char *)*param_1 == '\x01') {
    FUN_004437f0(*(void **)((char *)*param_1 + 8),(int *)&local_18,(byte *)local_68);
    iVar4 = FUN_00447a70((int *)local_18,local_18._4_4_);
  }
  else {
    iVar4 = 0;
  }
  if (0xf < local_54) {
    FUN_00402430(local_68[0],local_54 + 1,1);
  }
  local_54 = 0xf;
  local_58 = 0;
  local_68[0] = (void *)((uint)local_68[0] & 0xffffff00);
  if (iVar4 == 0) {
    local_28[0] = '\0';
    local_20 = 0;
    FUN_00450f50(local_28,1);
    pcVar6 = extraout_ECX;
  }
  else {
    puVar5 = FUN_00440e70((void *)*param_1,(uint *)&DAT_0048da74);
    pcVar6 = FUN_00434940(local_50,(undefined1 *)puVar5);
  }
  local_40[0] = *pcVar6;
  local_38 = *(undefined4 *)(pcVar6 + 8);
  local_34 = *(undefined4 *)(pcVar6 + 0xc);
  local_18 = 0;
  *pcVar6 = '\0';
  pcVar6[8] = '\0';
  pcVar6[9] = '\0';
  pcVar6[10] = '\0';
  pcVar6[0xb] = '\0';
  pcVar6[0xc] = '\0';
  pcVar6[0xd] = '\0';
  pcVar6[0xe] = '\0';
  pcVar6[0xf] = '\0';
  local_8 = 0;
  if (iVar4 == 0) {
    FUN_00434820(local_28);
  }
  else {
    FUN_00434820(local_50);
  }
  local_20 = 0xf00000000;
  local_30[0] = (void *)((uint)local_30[0] & 0xffffff00);
  FUN_0043ace0(local_30,(uint *)&DAT_0048d624,4);
  if (*(char *)*param_1 == '\x01') {
    FUN_004437f0(*(void **)((char *)*param_1 + 8),(int *)&local_18,(byte *)local_30);
    iVar4 = FUN_00447a70((int *)local_18,local_18._4_4_);
  }
  else {
    iVar4 = 0;
  }
  if (0xf < local_20._4_4_) {
    FUN_00402430(local_30[0],local_20._4_4_ + 1,1);
  }
  local_6c = 0xf;
  local_70 = 0;
  puVar7 = (uint *)&DAT_0048d624;
  local_80[0] = (void *)((uint)local_80[0] & 0xffffff00);
  if (iVar4 == 0) {
    puVar7 = (uint *)&DAT_0048da78;
  }
  FUN_0043ace0(local_80,(uint *)"append",6);
  local_8._0_1_ = 1;
  local_20 = 0xf00000000;
  local_30[0] = (void *)((uint)local_30[0] & 0xffffff00);
  FUN_0043ace0(local_30,(uint *)"addFmt",6);
  local_8 = CONCAT31(local_8._1_3_,2);
  FUN_00453810(local_40,(uint *)((int)&local_18 + 4));
  puVar5 = FUN_00440e70((void *)*param_1,puVar7);
  cVar1 = FUN_00441100((void *)*param_1,local_80);
  cVar2 = FUN_00441100((void *)*param_1,local_30);
  uVar3 = FUN_00417860(puVar5,local_18._4_4_,cVar2,cVar1);
  *(undefined1 *)param_1[1] = uVar3;
  if (0xf < local_20._4_4_) {
    FUN_00402430(local_30[0],local_20._4_4_ + 1,1);
  }
  local_20 = 0xf00000000;
  local_30[0] = (void *)((uint)local_30[0] & 0xffffff00);
  if (0xf < local_6c) {
    FUN_00402430(local_80[0],local_6c + 1,1);
  }
  FUN_00434820(local_40);
  ExceptionList = local_10;
  return;
}


