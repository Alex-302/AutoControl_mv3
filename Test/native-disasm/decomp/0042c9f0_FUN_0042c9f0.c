// FUN_0042c9f0 @ 0042c9f0 size=1106 callers=1

void __fastcall FUN_0042c9f0(void *param_1)

{
  uint uVar1;
  char cVar2;
  LPCSTR pCVar3;
  LPWSTR pWVar4;
  LPWSTR pWVar5;
  int iVar6;
  LPSTR pCVar7;
  char *pcVar8;
  char *pcVar9;
  HWND pHVar10;
  void *in_stack_fffffeb4;
  void *local_128 [6];
  void *local_110 [4];
  undefined4 local_100;
  uint local_fc;
  void *local_f8 [4];
  undefined4 local_e8;
  uint local_e4;
  void *local_e0 [4];
  undefined4 local_d0;
  uint local_cc;
  void *local_c8 [4];
  undefined4 local_b8;
  uint local_b4;
  void *local_b0 [4];
  undefined4 local_a0;
  uint local_9c;
  void *local_98 [4];
  undefined4 local_88;
  uint local_84;
  void *local_80;
  undefined1 *puStack_7c;
  undefined4 local_78;
  void *local_74 [4];
  undefined4 local_64;
  uint local_60;
  void *local_5c [4];
  undefined4 local_4c;
  uint local_48;
  void *local_44 [2];
  char local_3c [8];
  undefined4 local_34;
  uint local_30;
  void *local_2c [2];
  char local_24 [8];
  undefined8 local_1c;
  void *local_14;
  uint local_10;
  HWND local_c;
  char local_5;
  
  local_78 = 0xffffffff;
  puStack_7c = &LAB_0047ce3c;
  local_80 = ExceptionList;
  local_c = (HWND)0x0;
  local_1c = 0xf00000000;
  local_2c[0] = (void *)((uint)local_2c[0] & 0xffffff00);
  ExceptionList = &local_80;
  local_14 = param_1;
  FUN_0043ace0(local_2c,(uint *)&DAT_0048d05c,4);
  local_78 = 0;
  pCVar3 = (LPCSTR)FUN_004342f0(param_1,local_c8,local_2c,(uint *)&DAT_0048e75c);
  local_78 = CONCAT31(local_78._1_3_,1);
  FUN_00404640((LPWSTR)local_128,pCVar3);
  if (0xf < local_b4) {
    FUN_00402430(local_c8[0],local_b4 + 1,1);
  }
  local_b4 = 0xf;
  local_b8 = 0;
  local_c8[0] = (void *)((uint)local_c8[0] & 0xffffff00);
  local_78._0_1_ = 4;
  if (0xf < local_1c._4_4_) {
    FUN_00402430(local_2c[0],local_1c._4_4_ + 1,1);
  }
  local_1c = 0xf00000000;
  local_2c[0] = (void *)((uint)local_2c[0] & 0xffffff00);
  local_9c = 0xf;
  local_a0 = 0;
  local_b0[0] = (void *)((uint)local_b0[0] & 0xffffff00);
  FUN_0043ace0(local_b0,(uint *)"saveAs",6);
  local_78._0_1_ = 5;
  local_60 = 0xf;
  local_64 = 0;
  local_74[0] = (void *)((uint)local_74[0] & 0xffffff00);
  FUN_0043ace0(local_74,(uint *)"modal",5);
  local_78 = CONCAT31(local_78._1_3_,6);
  cVar2 = FUN_00441100(param_1,local_74);
  if (cVar2 == '\0') {
    local_c = (HWND)0x0;
  }
  else {
    local_c = GetForegroundWindow();
  }
  local_48 = 0xf;
  local_4c = 0;
  local_5c[0] = (void *)((uint)local_5c[0] & 0xffffff00);
  FUN_0043ace0(local_5c,(uint *)"dfltExt",7);
  local_78._0_1_ = 7;
  local_30 = 0xf;
  local_34 = 0;
  local_44[0] = (void *)((uint)local_44[0] & 0xffffff00);
  FUN_0043ace0(local_44,(uint *)"filter",6);
  local_78._0_1_ = 8;
  pCVar3 = (LPCSTR)FUN_004342f0(param_1,local_98,local_5c,(uint *)&DAT_0048e75c);
  local_78._0_1_ = 9;
  pWVar4 = FUN_00404640((LPWSTR)local_110,pCVar3);
  local_78._0_1_ = 10;
  pCVar3 = (LPCSTR)FUN_004342f0(param_1,local_f8,local_44,(uint *)&DAT_0048e75c);
  local_78._0_1_ = 0xb;
  pWVar5 = FUN_00404640((LPWSTR)local_e0,pCVar3);
  local_78 = CONCAT31(local_78._1_3_,0xc);
  cVar2 = FUN_00441100(param_1,local_b0);
  local_5 = FUN_0040fe70(local_128,(undefined4 *)pWVar5,(undefined4 *)pWVar4,local_c,cVar2);
  if (7 < local_cc) {
    FUN_00402430(local_e0[0],local_cc + 1,2);
  }
  local_cc = 7;
  local_e0[0] = (void *)((uint)local_e0[0] & 0xffff0000);
  local_d0 = 0;
  if (0xf < local_e4) {
    FUN_00402430(local_f8[0],local_e4 + 1,1);
  }
  local_e4 = 0xf;
  local_e8 = 0;
  local_f8[0] = (void *)((uint)local_f8[0] & 0xffffff00);
  if (7 < local_fc) {
    FUN_00402430(local_110[0],local_fc + 1,2);
  }
  local_fc = 7;
  local_110[0] = (void *)((uint)local_110[0] & 0xffff0000);
  local_100 = 0;
  if (0xf < local_84) {
    FUN_00402430(local_98[0],local_84 + 1,1);
  }
  local_84 = 0xf;
  local_88 = 0;
  local_98[0] = (void *)((uint)local_98[0] & 0xffffff00);
  if (0xf < local_30) {
    FUN_00402430(local_44[0],local_30 + 1,1);
  }
  local_30 = 0xf;
  local_34 = 0;
  local_44[0] = (void *)((uint)local_44[0] & 0xffffff00);
  if (0xf < local_48) {
    FUN_00402430(local_5c[0],local_48 + 1,1);
  }
  local_48 = 0xf;
  local_4c = 0;
  local_5c[0] = (void *)((uint)local_5c[0] & 0xffffff00);
  if (0xf < local_60) {
    FUN_00402430(local_74[0],local_60 + 1,1);
  }
  local_78._0_1_ = 4;
  local_60 = 0xf;
  local_64 = 0;
  local_74[0] = (void *)((uint)local_74[0] & 0xffffff00);
  if (0xf < local_9c) {
    FUN_00402430(local_b0[0],local_9c + 1,1);
  }
  FUN_004355e0(&stack0xfffffeb4,(uint *)"callback");
  iVar6 = FUN_004341b0(param_1,in_stack_fffffeb4);
  uVar1 = local_10;
  if (iVar6 != 0) {
    if (local_5 == '\0') {
      local_10 = local_10 & 0xffffff00;
      local_24[0] = '\x04';
      local_1c = CONCAT44(local_c,uVar1) & 0xffffffffffffff00;
      pcVar8 = local_24;
      local_78._0_1_ = 0xf;
      pHVar10 = (HWND)0x4;
    }
    else {
      pCVar7 = FUN_00404580((LPSTR)local_98,(LPCWSTR)local_128,0x7fffffff);
      local_78 = CONCAT31(local_78._1_3_,0xd);
      local_c = (HWND)0x1;
      pcVar8 = FUN_00440c80(local_3c,(undefined4 *)pCVar7);
      local_78._0_1_ = 0xe;
      pHVar10 = (HWND)0x3;
    }
    local_78._1_3_ = 0;
    local_c = pHVar10;
    pcVar9 = (char *)FUN_00440dd0(local_14,(uint *)"callback");
    FUN_00453810(pcVar9,(uint *)&local_14);
    FUN_00408760((int)local_14,pcVar8);
    if (((uint)pHVar10 & 4) != 0) {
      pHVar10 = (HWND)((uint)pHVar10 & 0xfffffffb);
      FUN_00434820(local_24);
    }
    if (((uint)pHVar10 & 2) != 0) {
      pHVar10 = (HWND)((uint)pHVar10 & 0xfffffffd);
      FUN_00434820(local_3c);
    }
    if (((uint)pHVar10 & 1) != 0) {
      FUN_004061c0(local_98);
    }
  }
  FUN_00435170(local_128);
  ExceptionList = local_80;
  return;
}


