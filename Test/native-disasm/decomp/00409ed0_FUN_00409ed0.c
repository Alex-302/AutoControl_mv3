// FUN_00409ed0 @ 00409ed0 size=1438 callers=1

void * __cdecl FUN_00409ed0(void *param_1,void *param_2)

{
  undefined8 uVar1;
  byte bVar2;
  char cVar3;
  uint *puVar4;
  uint *puVar5;
  LPCSTR pCVar6;
  uint uVar7;
  char *pcVar8;
  undefined4 *this;
  LPCWSTR **pppWVar9;
  LPWSTR **pppWVar10;
  char cVar11;
  undefined1 *puVar12;
  undefined4 uVar13;
  void **ppvVar14;
  undefined4 uVar15;
  LPWSTR *local_134 [5];
  uint local_120;
  LPCWSTR *local_11c [5];
  uint local_108;
  undefined4 local_104 [2];
  undefined4 local_fc;
  int local_f8;
  LPCWSTR *local_f4 [5];
  uint local_e0;
  void *local_dc [4];
  undefined4 local_cc;
  uint local_c8;
  void *local_c4 [4];
  undefined4 local_b4;
  uint local_b0;
  void *local_ac [4];
  undefined4 local_9c;
  uint local_98;
  void *local_94 [4];
  undefined4 local_84;
  uint local_80;
  void *local_7c [4];
  undefined4 local_6c;
  uint local_68;
  void *local_64 [4];
  undefined4 local_54;
  uint local_50;
  undefined4 local_4c;
  undefined1 *local_48;
  void *local_44 [2];
  char local_3c [8];
  undefined8 local_34;
  void *local_2c [4];
  undefined4 local_1c;
  uint local_18;
  char local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00479d4e;
  local_10 = ExceptionList;
  local_8 = 0;
  local_4c = 0;
  local_18 = 0xf;
  local_1c = 0;
  local_2c[0] = (void *)((uint)local_2c[0] & 0xffffff00);
  ExceptionList = &local_10;
  FUN_0043ace0(local_2c,(uint *)&DAT_0048d064,4);
  local_8 = 1;
  local_34 = 0xf00000000;
  local_44[0] = (void *)((uint)local_44[0] & 0xffffff00);
  FUN_0043ace0(local_44,(uint *)&DAT_0048d074,4);
  local_8._0_1_ = 2;
  puVar4 = FUN_004342f0(param_2,local_dc,local_2c,(uint *)&DAT_0048e75c);
  local_8._0_1_ = 3;
  puVar5 = FUN_004342f0(param_2,local_c4,local_44,(uint *)&DAT_0048d070);
  local_8._0_1_ = 4;
  puVar5 = (uint *)FUN_004412a0((undefined1 *)local_ac,puVar5,(uint *)&DAT_0048d06c);
  local_8._0_1_ = 5;
  pCVar6 = FUN_00441300((undefined1 *)local_94,puVar5,puVar4);
  local_8 = CONCAT31(local_8._1_3_,6);
  FUN_00404640((LPWSTR)local_134,pCVar6);
  if (0xf < local_80) {
    FUN_00402430(local_94[0],local_80 + 1,1);
  }
  local_80 = 0xf;
  local_84 = 0;
  local_94[0] = (void *)((uint)local_94[0] & 0xffffff00);
  if (0xf < local_98) {
    FUN_00402430(local_ac[0],local_98 + 1,1);
  }
  local_98 = 0xf;
  local_9c = 0;
  local_ac[0] = (void *)((uint)local_ac[0] & 0xffffff00);
  if (0xf < local_b0) {
    FUN_00402430(local_c4[0],local_b0 + 1,1);
  }
  local_b0 = 0xf;
  local_b4 = 0;
  local_c4[0] = (void *)((uint)local_c4[0] & 0xffffff00);
  if (0xf < local_c8) {
    FUN_00402430(local_dc[0],local_c8 + 1,1);
  }
  local_c8 = 0xf;
  local_cc = 0;
  local_dc[0] = (void *)((uint)local_dc[0] & 0xffffff00);
  if (0xf < local_34._4_4_) {
    FUN_00402430(local_44[0],local_34._4_4_ + 1,1);
  }
  local_34 = 0xf00000000;
  local_44[0] = (void *)((uint)local_44[0] & 0xffffff00);
  local_8._0_1_ = 0xd;
  if (0xf < local_18) {
    FUN_00402430(local_2c[0],local_18 + 1,1);
  }
  local_18 = 0xf;
  local_1c = 0;
  local_2c[0] = (void *)((uint)local_2c[0] & 0xffffff00);
  local_68 = 0xf;
  local_6c = 0;
  local_7c[0] = (void *)((uint)local_7c[0] & 0xffffff00);
  FUN_0043ace0(local_7c,(uint *)&DAT_0048d07c,3);
  local_8._0_1_ = 0xe;
  pCVar6 = (LPCSTR)FUN_004342f0(param_2,local_64,local_7c,(uint *)&DAT_0048d070);
  local_8 = CONCAT31(local_8._1_3_,0xf);
  FUN_00404640((LPWSTR)local_11c,pCVar6);
  if (0xf < local_50) {
    FUN_00402430(local_64[0],local_50 + 1,1);
  }
  local_50 = 0xf;
  local_54 = 0;
  local_64[0] = (void *)((uint)local_64[0] & 0xffffff00);
  local_8._0_1_ = 0x12;
  if (0xf < local_68) {
    FUN_00402430(local_7c[0],local_68 + 1,1);
  }
  local_68 = 0xf;
  local_6c = 0;
  local_7c[0] = (void *)((uint)local_7c[0] & 0xffffff00);
  local_18 = 0xf;
  local_1c = 0;
  local_2c[0] = (void *)((uint)local_2c[0] & 0xffffff00);
  FUN_0043ace0(local_2c,(uint *)"getStdout",9);
  local_8._0_1_ = 0x13;
  local_11 = FUN_00441100(param_2,local_2c);
  local_8._0_1_ = 0x12;
  if (0xf < local_18) {
    FUN_00402430(local_2c[0],local_18 + 1,1);
  }
  local_18 = 0xf;
  local_1c = 0;
  local_2c[0] = (void *)((uint)local_2c[0] & 0xffffff00);
  FUN_0043ace0(local_2c,(uint *)"showWin",7);
  local_8._0_1_ = 0x14;
  uVar7 = FUN_004409d0(param_2,local_2c,0);
  local_48 = (undefined1 *)(uVar7 & 0xffff);
  local_8._0_1_ = 0x12;
  if (0xf < local_18) {
    FUN_00402430(local_2c[0],local_18 + 1,1);
  }
  FUN_004355e0(local_2c,(uint *)&DAT_0048d094);
  local_8._0_1_ = 0x15;
  pppWVar9 = local_11c;
  if (7 < local_108) {
    pppWVar9 = (LPCWSTR **)local_11c[0];
  }
  pppWVar10 = local_134;
  if (7 < local_120) {
    pppWVar10 = (LPWSTR **)local_134[0];
  }
  bVar2 = -(local_11 != '\0') & 4;
  uVar7 = FUN_004409d0(param_2,local_2c,0);
  puVar12 = local_48;
  FUN_00405040(local_104,(LPWSTR)pppWVar10,(LPCWSTR)pppWVar9,(WORD)local_48,uVar7,bVar2);
  cVar11 = (char)puVar12;
  local_8._0_1_ = 0x17;
  if (0xf < local_18) {
    cVar11 = -0x4e;
    FUN_00402430(local_2c[0],local_18 + 1,1);
  }
  local_18 = 0xf;
  local_1c = 0;
  local_2c[0] = (void *)((uint)local_2c[0] & 0xffffff00);
  FUN_00434a40(param_1,(char *)0x0,(char *)0x0);
  local_4c = 1;
  local_3c[0] = '\0';
  local_34 = 0;
  if (local_f8 == 0) {
    FUN_00451040(local_3c,local_fc);
    local_8._0_1_ = 0x19;
    pcVar8 = (char *)FUN_00440e70(param_1,(uint *)"exitCode");
    local_8._0_1_ = 0x17;
    cVar3 = *pcVar8;
    *pcVar8 = local_3c[0];
    uVar1 = *(undefined8 *)(pcVar8 + 8);
    *(undefined4 *)(pcVar8 + 8) = (undefined4)local_34;
    *(uint *)(pcVar8 + 0xc) = local_34._4_4_;
    local_3c[0] = cVar3;
    local_34 = uVar1;
    FUN_00434820(local_3c);
    if (local_11 != '\0') {
      FUN_004355e0(local_64,(uint *)"wideOutput");
      ppvVar14 = local_64;
      local_8._0_1_ = 0x1a;
      uVar13 = 0x40a3b0;
      cVar3 = FUN_00441100(param_2,ppvVar14);
      local_8 = CONCAT31(local_8._1_3_,0x17);
      uVar15 = 0x40a3be;
      FUN_004061c0(local_64);
      if (cVar3 != '\0') {
        FUN_0043aef0(local_f4,1,'\0');
        pppWVar9 = local_f4;
        if (0xf < local_e0) {
          pppWVar9 = (LPCWSTR **)local_f4[0];
        }
        uVar13 = 0x40a3f4;
        puVar4 = (uint *)FUN_004044f0((LPSTR)local_64,(LPCWSTR)pppWVar9,-1,0x7fffffff);
        ppvVar14 = (void **)0x40a403;
        FUN_00435570(local_f4,puVar4);
        uVar15 = 0x40a40b;
        FUN_004061c0(local_64);
      }
      local_48 = &stack0xfffffeac;
      FUN_00440c80(&stack0xfffffeac,local_f4);
      local_8._0_1_ = 0x1b;
      this = FUN_00440e70(param_1,(uint *)"stdout");
      local_8._0_1_ = 0x17;
      FUN_004348c0(this,cVar11,uVar13,ppvVar14,uVar15);
    }
  }
  else {
    FUN_00451040(local_3c,local_f8);
    local_8._0_1_ = 0x18;
    pcVar8 = (char *)FUN_00440e70(param_1,(uint *)"error");
    cVar11 = *pcVar8;
    *pcVar8 = local_3c[0];
    uVar1 = *(undefined8 *)(pcVar8 + 8);
    *(undefined4 *)(pcVar8 + 8) = (undefined4)local_34;
    *(uint *)(pcVar8 + 0xc) = local_34._4_4_;
    local_3c[0] = cVar11;
    local_34 = uVar1;
    FUN_00434820(local_3c);
  }
  FUN_00405280((int)local_104);
  FUN_00435170(local_11c);
  FUN_00435170(local_134);
  ExceptionList = local_10;
  return param_1;
}


