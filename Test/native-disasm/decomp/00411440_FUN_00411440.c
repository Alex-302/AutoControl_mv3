// FUN_00411440 @ 00411440 size=1158 callers=1

uint * __fastcall FUN_00411440(void *param_1,undefined4 *param_2,uint *param_3)

{
  ushort uVar1;
  undefined1 local_120 [16];
  undefined4 local_110;
  undefined4 local_10c;
  undefined1 local_108 [16];
  undefined4 local_f8;
  undefined4 local_f4;
  void *local_f0 [4];
  undefined4 local_e0;
  uint local_dc;
  void *local_d8 [4];
  undefined4 local_c8;
  uint local_c4;
  void *local_c0 [4];
  undefined4 local_b0;
  uint local_ac;
  void *local_a8 [4];
  undefined4 local_98;
  uint local_94;
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
  uint local_30;
  uint uStack_2c;
  uint uStack_28;
  undefined4 uStack_24;
  ushort local_20;
  ushort uStack_1e;
  ushort uStack_1c;
  ushort uStack_1a;
  uint local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047a9d5;
  local_10 = ExceptionList;
  local_10c = 0xf;
  local_110 = 0;
  local_120[0] = 0;
  ExceptionList = &local_10;
  FUN_0043ace0(local_120,(uint *)"txtColor",8);
  local_8 = 0;
  local_30 = FUN_00441990(param_1,(undefined4 *)local_120,*param_2);
  local_f4 = 0xf;
  local_f8 = 0;
  local_108[0] = 0;
  FUN_0043ace0(local_108,(uint *)"bgColor",7);
  local_8._0_1_ = 1;
  uStack_2c = FUN_00441990(param_1,(undefined4 *)local_108,param_2[1]);
  local_dc = 0xf;
  local_e0 = 0;
  local_f0[0] = (void *)((uint)local_f0[0] & 0xffffff00);
  FUN_0043ace0(local_f0,(uint *)"borderColor",0xb);
  local_8._0_1_ = 2;
  uStack_28 = FUN_00441990(param_1,local_f0,param_2[2]);
  local_c4 = 0xf;
  local_c8 = 0;
  local_d8[0] = (void *)((uint)local_d8[0] & 0xffffff00);
  FUN_0043ace0(local_d8,(uint *)"margin",6);
  local_8._0_1_ = 3;
  uVar1 = FUN_00441a60(param_1,local_d8,*(undefined2 *)(param_2 + 3));
  uStack_24 = CONCAT22(uStack_24._2_2_,uVar1);
  local_ac = 0xf;
  local_b0 = 0;
  local_c0[0] = (void *)((uint)local_c0[0] & 0xffffff00);
  FUN_0043ace0(local_c0,(uint *)"borderWidth",0xb);
  local_8._0_1_ = 4;
  uVar1 = FUN_00441a60(param_1,local_c0,*(undefined2 *)((int)param_2 + 0xe));
  uStack_24 = CONCAT22(uVar1,(undefined2)uStack_24);
  local_94 = 0xf;
  local_98 = 0;
  local_a8[0] = (void *)((uint)local_a8[0] & 0xffffff00);
  FUN_0043ace0(local_a8,(uint *)"paddingHorz",0xb);
  local_8._0_1_ = 5;
  local_20 = FUN_00441a60(param_1,local_a8,*(undefined2 *)(param_2 + 4));
  local_7c = 0xf;
  local_80 = 0;
  local_90[0] = (void *)((uint)local_90[0] & 0xffffff00);
  FUN_0043ace0(local_90,(uint *)"paddingVert",0xb);
  local_8._0_1_ = 6;
  uStack_1e = FUN_00441a60(param_1,local_90,*(undefined2 *)((int)param_2 + 0x12));
  local_64 = 0xf;
  local_68 = 0;
  local_78[0] = (void *)((uint)local_78[0] & 0xffffff00);
  FUN_0043ace0(local_78,(uint *)"titleOffsetX",0xc);
  local_8._0_1_ = 7;
  uStack_1c = FUN_00441a60(param_1,local_78,*(undefined2 *)(param_2 + 5));
  local_4c = 0xf;
  local_50 = 0;
  local_60[0] = (void *)((uint)local_60[0] & 0xffffff00);
  FUN_0043ace0(local_60,(uint *)"titleOffsetY",0xc);
  local_8._0_1_ = 8;
  uStack_1a = FUN_00441a60(param_1,local_60,*(undefined2 *)((int)param_2 + 0x16));
  local_34 = 0xf;
  local_38 = 0;
  local_48[0] = (void *)((uint)local_48[0] & 0xffffff00);
  FUN_0043ace0(local_48,(uint *)"previewOffsetY",0xe);
  local_8 = CONCAT31(local_8._1_3_,9);
  uVar1 = FUN_00441a60(param_1,local_48,*(undefined2 *)(param_2 + 6));
  local_18 = CONCAT22(local_18._2_2_,uVar1);
  *param_3 = local_30;
  param_3[1] = uStack_2c;
  param_3[2] = uStack_28;
  param_3[3] = uStack_24;
  *(ulonglong *)(param_3 + 4) = CONCAT26(uStack_1a,CONCAT24(uStack_1c,CONCAT22(uStack_1e,local_20)))
  ;
  param_3[6] = local_18;
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
  if (0xf < local_64) {
    FUN_00402430(local_78[0],local_64 + 1,1);
  }
  local_64 = 0xf;
  local_68 = 0;
  local_78[0] = (void *)((uint)local_78[0] & 0xffffff00);
  if (0xf < local_7c) {
    FUN_00402430(local_90[0],local_7c + 1,1);
  }
  local_7c = 0xf;
  local_80 = 0;
  local_90[0] = (void *)((uint)local_90[0] & 0xffffff00);
  if (0xf < local_94) {
    FUN_00402430(local_a8[0],local_94 + 1,1);
  }
  local_94 = 0xf;
  local_98 = 0;
  local_a8[0] = (void *)((uint)local_a8[0] & 0xffffff00);
  if (0xf < local_ac) {
    FUN_00402430(local_c0[0],local_ac + 1,1);
  }
  local_ac = 0xf;
  local_b0 = 0;
  local_c0[0] = (void *)((uint)local_c0[0] & 0xffffff00);
  if (0xf < local_c4) {
    FUN_00402430(local_d8[0],local_c4 + 1,1);
  }
  local_c4 = 0xf;
  local_c8 = 0;
  local_d8[0] = (void *)((uint)local_d8[0] & 0xffffff00);
  if (0xf < local_dc) {
    FUN_00402430(local_f0[0],local_dc + 1,1);
  }
  local_dc = 0xf;
  local_e0 = 0;
  local_f0[0] = (void *)((uint)local_f0[0] & 0xffffff00);
  FUN_004061c0((undefined4 *)local_108);
  FUN_004061c0((undefined4 *)local_120);
  ExceptionList = local_10;
  return param_3;
}


