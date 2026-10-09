// FUN_00410fb0 @ 00410fb0 size=1166 callers=5

void * __thiscall FUN_00410fb0(void *this,void *param_1,undefined4 param_2)

{
  char cVar1;
  char cVar2;
  LPCSTR pCVar3;
  char *pcVar4;
  uint *puVar5;
  uint uVar6;
  ushort uVar7;
  undefined1 local_d4 [16];
  undefined4 local_c4;
  undefined4 local_c0;
  void *local_bc [4];
  undefined4 local_ac;
  uint local_a8;
  void *local_a4 [4];
  undefined4 local_94;
  uint local_90;
  void *local_8c;
  void *local_88 [4];
  undefined4 local_78;
  uint local_74;
  undefined1 local_70 [16];
  undefined4 local_60;
  undefined4 local_5c;
  void *local_58 [4];
  undefined4 local_48;
  uint local_44;
  void *local_40 [4];
  undefined4 local_30;
  uint local_2c;
  void *local_28 [4];
  undefined4 local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047a965;
  local_10 = ExceptionList;
  local_2c = 0xf;
  local_30 = 0;
  local_40[0] = (void *)((uint)local_40[0] & 0xffffff00);
  ExceptionList = &local_10;
  local_8c = this;
  FUN_0043ace0(local_40,(uint *)"title",5);
  local_8 = 0;
  pCVar3 = (LPCSTR)FUN_004342f0(param_1,local_58,local_40,(uint *)&DAT_0048e75c);
  local_8 = CONCAT31(local_8._1_3_,1);
  FUN_00404640(this,pCVar3);
  if (0xf < local_44) {
    FUN_00402430(local_58[0],local_44 + 1,1);
  }
  local_44 = 0xf;
  local_48 = 0;
  local_58[0] = (void *)((uint)local_58[0] & 0xffffff00);
  local_8._0_1_ = 4;
  if (0xf < local_2c) {
    FUN_00402430(local_40[0],local_2c + 1,1);
  }
  local_2c = 0xf;
  local_30 = 0;
  local_40[0] = (void *)((uint)local_40[0] & 0xffffff00);
  local_74 = 0xf;
  local_78 = 0;
  local_88[0] = (void *)((uint)local_88[0] & 0xffffff00);
  FUN_0043ace0(local_88,(uint *)&DAT_0048d428,4);
  local_8._0_1_ = 5;
  pcVar4 = (char *)FUN_004342f0(param_1,local_bc,local_88,(uint *)&DAT_0048e75c);
  local_8._0_1_ = 6;
  puVar5 = FUN_00404220((uint *)local_a4,pcVar4);
  local_8 = CONCAT31(local_8._1_3_,7);
  FUN_0040a960((int *)((int)this + 0x18),puVar5);
  if (0xf < local_90) {
    FUN_00402430(local_a4[0],local_90 + 1,1);
  }
  local_90 = 0xf;
  local_94 = 0;
  local_a4[0] = (void *)((uint)local_a4[0] & 0xffffff00);
  if (0xf < local_a8) {
    FUN_00402430(local_bc[0],local_a8 + 1,1);
  }
  local_a8 = 0xf;
  local_ac = 0;
  local_bc[0] = (void *)((uint)local_bc[0] & 0xffffff00);
  local_8._0_1_ = 0xb;
  if (0xf < local_74) {
    FUN_00402430(local_88[0],local_74 + 1,1);
  }
  local_74 = 0xf;
  local_78 = 0;
  local_88[0] = (void *)((uint)local_88[0] & 0xffffff00);
  *(undefined4 *)((int)this + 0x1c) = param_2;
  local_14 = 0xf;
  local_18 = 0;
  local_28[0] = (void *)((uint)local_28[0] & 0xffffff00);
  FUN_0043ace0(local_28,(uint *)"itemType",8);
  local_8._0_1_ = 0xc;
  cVar1 = FUN_004418c0(param_1,local_28);
  *(char *)((int)this + 0x24) = cVar1;
  local_8._0_1_ = 0xb;
  if (0xf < local_14) {
    FUN_00402430(local_28[0],local_14 + 1,1);
  }
  local_14 = 0xf;
  local_18 = 0;
  local_28[0] = (void *)((uint)local_28[0] & 0xffffff00);
  FUN_0043ace0(local_28,(uint *)"thumbSize",9);
  local_8._0_1_ = 0xd;
  cVar1 = FUN_004418c0(param_1,local_28);
  *(char *)((int)this + 0x25) = cVar1;
  local_8._0_1_ = 0xb;
  if (0xf < local_14) {
    FUN_00402430(local_28[0],local_14 + 1,1);
  }
  local_5c = 0xf;
  local_60 = 0;
  local_70[0] = 0;
  FUN_0043ace0(local_70,(uint *)"subMenu",7);
  local_8._0_1_ = 0xe;
  local_c0 = 0xf;
  local_c4 = 0;
  local_d4[0] = 0;
  FUN_0043ace0(local_d4,(uint *)"break",5);
  local_8._0_1_ = 0xf;
  local_14 = 0xf;
  local_18 = 0;
  local_28[0] = (void *)((uint)local_28[0] & 0xffffff00);
  FUN_0043ace0(local_28,(uint *)"sepLine",7);
  local_8._0_1_ = 0x10;
  local_2c = 0xf;
  local_30 = 0;
  local_40[0] = (void *)((uint)local_40[0] & 0xffffff00);
  FUN_0043ace0(local_40,(uint *)"noTitle",7);
  local_8._0_1_ = 0x11;
  FUN_004355e0(local_58,(uint *)"disabled");
  local_8 = CONCAT31(local_8._1_3_,0x12);
  cVar1 = FUN_00441100(param_1,local_40);
  cVar2 = FUN_00441100(param_1,(undefined4 *)local_d4);
  uVar7 = CONCAT11(-(cVar2 != '\0'),-(cVar1 != '\0')) & 0x810;
  cVar1 = FUN_00441100(param_1,local_58);
  cVar2 = FUN_00441100(param_1,local_28);
  uVar7 = CONCAT11(-(cVar2 != '\0'),cVar1 != '\0' | (byte)(uVar7 >> 8) | (byte)uVar7) & 0x4ff;
  cVar1 = FUN_00441100(param_1,(undefined4 *)local_70);
  *(byte *)((int)this + 0x26) = -(cVar1 != '\0') & 2U | (byte)(uVar7 >> 8) | (byte)uVar7;
  if (0xf < local_44) {
    FUN_00402430(local_58[0],local_44 + 1,1);
  }
  local_44 = 0xf;
  local_48 = 0;
  local_58[0] = (void *)((uint)local_58[0] & 0xffffff00);
  if (0xf < local_2c) {
    FUN_00402430(local_40[0],local_2c + 1,1);
  }
  local_2c = 0xf;
  local_30 = 0;
  local_40[0] = (void *)((uint)local_40[0] & 0xffffff00);
  if (0xf < local_14) {
    FUN_00402430(local_28[0],local_14 + 1,1);
  }
  local_14 = 0xf;
  local_18 = 0;
  local_28[0] = (void *)((uint)local_28[0] & 0xffffff00);
  FUN_004061c0((undefined4 *)local_d4);
  local_8._0_1_ = 0xb;
  FUN_004061c0((undefined4 *)local_70);
  if (*(char *)((int)this + 0x24) == '3') {
    FUN_004355e0(local_70,(uint *)"switchId");
    local_8 = CONCAT31(local_8._1_3_,0x13);
    uVar6 = FUN_004409d0(param_1,(undefined4 *)local_70,0);
    *(short *)((int)this + 0x20) = (short)uVar6;
  }
  else {
    FUN_004355e0(local_70,(uint *)"previewId");
    local_8 = CONCAT31(local_8._1_3_,0x14);
    uVar6 = FUN_004409d0(param_1,(undefined4 *)local_70,0);
    *(uint *)((int)this + 0x20) = uVar6;
  }
  FUN_004061c0((undefined4 *)local_70);
  ExceptionList = local_10;
  return this;
}


