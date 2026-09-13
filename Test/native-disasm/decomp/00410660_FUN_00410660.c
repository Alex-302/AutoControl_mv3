// FUN_00410660 @ 00410660 size=413 callers=5

void __fastcall FUN_00410660(undefined4 param_1,undefined4 *param_2,undefined1 *param_3)

{
  undefined1 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  char local_a0 [16];
  undefined1 local_90 [16];
  char local_80 [8];
  undefined8 local_78;
  undefined1 local_70 [16];
  char local_60 [16];
  char local_50 [8];
  undefined8 local_48;
  undefined1 local_40 [8];
  undefined8 local_38;
  char local_30 [16];
  undefined4 local_20;
  undefined4 local_1c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047a6fa;
  local_10 = ExceptionList;
  local_50[0] = '\0';
  local_48 = 0;
  ExceptionList = &local_10;
  FUN_00451110(local_50,(uint *)&DAT_0048cf30);
  local_40[0] = 0;
  local_38 = 0;
  FUN_00451040(local_40,param_1);
  local_8 = 0;
  FUN_00434b50(local_a0,local_50,local_30,'\x01','\x02');
  local_8._0_1_ = 2;
  _eh_vector_destructor_iterator_(local_50,0x10,2,FUN_00434820);
  local_80[0] = '\0';
  local_78 = 0;
  FUN_00451110(local_80,(uint *)&DAT_0048cf60);
  local_8._0_1_ = 3;
  FUN_00440c80(local_70,param_2);
  local_8._0_1_ = 4;
  FUN_00434b50(local_90,local_80,local_60,'\x01','\x02');
  local_8 = CONCAT31(local_8._1_3_,6);
  _eh_vector_destructor_iterator_(local_80,0x10,2,FUN_00434820);
  local_8 = 7;
  FUN_00434b50(local_60,local_a0,local_80,'\x01','\x02');
  local_8._0_1_ = 9;
  _eh_vector_destructor_iterator_(local_a0,0x10,2,FUN_00434820);
  local_30[0] = '\0';
  local_30[1] = '\0';
  local_30[2] = '\0';
  local_30[3] = '\0';
  local_30[4] = '\0';
  local_30[5] = '\0';
  local_30[6] = '\0';
  local_30[7] = '\0';
  uVar1 = *param_3;
  uVar2 = *(undefined4 *)(param_3 + 8);
  uVar3 = *(undefined4 *)(param_3 + 0xc);
  *param_3 = 0;
  *(undefined4 *)(param_3 + 8) = 0;
  *(undefined4 *)(param_3 + 0xc) = 0;
  local_8._0_1_ = 10;
  local_30[8] = uVar1;
  local_20 = uVar2;
  local_1c = uVar3;
  puVar4 = FUN_00440e70(local_60,(uint *)"chunk");
  local_8 = CONCAT31(local_8._1_3_,9);
  local_30[8] = *(char *)puVar4;
  *(undefined1 *)puVar4 = uVar1;
  local_1c = puVar4[3];
  local_20 = puVar4[2];
  puVar4[2] = uVar2;
  puVar4[3] = uVar3;
  FUN_00434820(local_30 + 8);
  FUN_00408600(0x32a,local_60);
  FUN_00434820(local_60);
  ExceptionList = local_10;
  return;
}


