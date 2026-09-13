// FUN_0042ad60 @ 0042ad60 size=1815 callers=1

void * __cdecl FUN_0042ad60(void *param_1,char *param_2)

{
  undefined1 uVar1;
  LONG LVar2;
  LONG LVar3;
  char *pcVar4;
  HWND pHVar5;
  HMONITOR pHVar6;
  float *pfVar7;
  float fVar8;
  undefined4 *puVar9;
  uint uVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float10 fVar14;
  float10 fVar15;
  float in_XMM0_Da;
  UINT gaFlags;
  char local_18c [16];
  undefined1 local_17c [16];
  undefined1 local_16c [16];
  undefined1 local_15c [16];
  char local_14c [16];
  undefined1 local_13c [16];
  char local_12c [8];
  undefined8 local_124;
  undefined1 local_11c [16];
  char local_10c [16];
  char local_fc [8];
  undefined8 local_f4;
  undefined1 local_ec [8];
  undefined8 local_e4;
  char local_dc [8];
  undefined8 local_d4;
  undefined1 local_cc [8];
  undefined8 local_c4;
  char local_bc [8];
  undefined8 local_b4;
  undefined1 local_ac [8];
  undefined8 local_a4;
  char local_9c [8];
  undefined8 local_94;
  undefined1 local_8c [8];
  undefined8 local_84;
  char local_7c [8];
  undefined8 local_74;
  undefined1 local_6c [8];
  undefined8 local_64;
  char local_5c [8];
  undefined8 local_54;
  undefined1 local_4c [8];
  undefined8 local_44;
  char local_3c [4];
  undefined4 local_38;
  undefined8 local_34;
  float local_2c;
  float fStack_28;
  POINT PStack_24;
  float local_18;
  float local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_0047cb7a;
  local_10 = ExceptionList;
  local_8 = 0;
  local_38 = 0;
  ExceptionList = &local_10;
  FUN_00453810(param_2,(uint *)&local_18);
  uVar10 = (uint)local_18 >> 5;
  if (((uint)local_18 & 0x10) == 0) {
    local_34 = FUN_00410800('\0');
  }
  else {
    local_34 = CONCAT44(DAT_004a23e4,DAT_004a23e0);
  }
  pcVar4 = (char *)local_34;
  param_2 = (char *)local_34;
  PStack_24.x = (LONG)(char *)local_34;
  local_14 = local_34._4_4_;
  PStack_24.y = (LONG)local_34._4_4_;
  if (((uint)local_18 & 8) == 0) {
    gaFlags = 3;
    pHVar5 = GetForegroundWindow();
    pHVar5 = GetAncestor(pHVar5,gaFlags);
  }
  else {
    pHVar5 = FUN_0042aae0(&PStack_24);
  }
  if ((uVar10 & 1) != 0) {
    if (pHVar5 != DAT_004a2430) {
      DAT_004a2430 = pHVar5;
      pHVar6 = MonitorFromWindow(pHVar5,2);
      FUN_00406610(pHVar6);
      DAT_0049d9e0 = in_XMM0_Da;
    }
    fVar8 = DAT_0049d9e0;
    fVar14 = roundf((float)(int)pcVar4 / DAT_0049d9e0);
    param_2 = (char *)(int)fVar14;
    local_14 = (float)(int)local_14;
    if (pHVar5 != DAT_004a2430) {
      DAT_004a2430 = pHVar5;
      pHVar6 = MonitorFromWindow(pHVar5,2);
      FUN_00406610(pHVar6);
      DAT_0049d9e0 = fVar8;
    }
    fVar14 = roundf(local_14 / DAT_0049d9e0);
    local_14 = (float)(int)fVar14;
  }
  local_12c[0] = '\0';
  local_124 = 0;
  FUN_00451110(local_12c,(uint *)"mouse");
  local_8 = 1;
  local_5c[0] = '\0';
  local_54 = 0;
  FUN_00451110(local_5c,(uint *)&DAT_0048d65c);
  local_4c[0] = 0;
  local_44 = 0;
  FUN_00450f50(local_4c,(int)param_2);
  local_8._0_1_ = 2;
  FUN_00434b50(local_14c,local_5c,local_3c,'\x01','\x02');
  local_8._0_1_ = 4;
  _eh_vector_destructor_iterator_(local_5c,0x10,2,FUN_00434820);
  local_7c[0] = '\0';
  local_74 = 0;
  FUN_00451110(local_7c,(uint *)&DAT_0048d660);
  local_6c[0] = 0;
  local_64 = 0;
  FUN_00450f50(local_6c,(int)local_14);
  local_8._0_1_ = 5;
  FUN_00434b50(local_13c,local_7c,local_5c,'\x01','\x02');
  local_8._0_1_ = 7;
  _eh_vector_destructor_iterator_(local_7c,0x10,2,FUN_00434820);
  local_8._0_1_ = 8;
  FUN_00434b50(local_11c,local_14c,local_12c,'\x01','\x02');
  local_8 = CONCAT31(local_8._1_3_,10);
  _eh_vector_destructor_iterator_(local_14c,0x10,2,FUN_00434820);
  local_8 = 0xb;
  FUN_00434b50(local_10c,local_12c,local_10c,'\x01','\x02');
  local_8 = CONCAT31(local_8._1_3_,0xd);
  _eh_vector_destructor_iterator_(local_12c,0x10,2,FUN_00434820);
  local_8 = 0xe;
  FUN_00434b50(param_1,local_10c,local_fc,'\x01','\x02');
  local_38 = 1;
  local_8 = local_8 & 0xffffff00;
  _eh_vector_destructor_iterator_(local_10c,0x10,1,FUN_00434820);
  if (((uint)local_18 & 0xb) != 0) {
    pfVar7 = (float *)FUN_0040e9b0(pHVar5,'\x01',(int *)&local_2c);
    fVar8 = *pfVar7;
    fVar13 = pfVar7[1];
    fVar11 = pfVar7[2];
    fVar12 = pfVar7[3];
    local_2c = fVar8;
    fStack_28 = fVar13;
    PStack_24.x = (LONG)fVar11;
    PStack_24.y = (LONG)fVar12;
    local_18 = fVar8;
    if ((uVar10 & 1) != 0) {
      if (pHVar5 != DAT_004a2430) {
        DAT_004a2430 = pHVar5;
        pHVar6 = MonitorFromWindow(pHVar5,2);
        FUN_00406610(pHVar6);
        DAT_0049d9e0 = fVar8;
      }
      fVar8 = DAT_0049d9e0;
      fVar14 = roundf((float)(int)local_2c / DAT_0049d9e0);
      local_18 = (float)(int)fVar14;
      if (pHVar5 != DAT_004a2430) {
        DAT_004a2430 = pHVar5;
        pHVar6 = MonitorFromWindow(pHVar5,2);
        FUN_00406610(pHVar6);
        DAT_0049d9e0 = fVar8;
      }
      fVar8 = DAT_0049d9e0;
      fVar15 = roundf((float)(int)fStack_28 / DAT_0049d9e0);
      local_34 = CONCAT44((float)fVar15,(char *)local_34);
      if (pHVar5 != DAT_004a2430) {
        DAT_004a2430 = pHVar5;
        pHVar6 = MonitorFromWindow(pHVar5,2);
        FUN_00406610(pHVar6);
        DAT_0049d9e0 = fVar8;
      }
      fVar8 = DAT_0049d9e0;
      fVar15 = roundf((float)PStack_24.x / DAT_0049d9e0);
      local_14 = (float)fVar15;
      fVar11 = (float)(int)fVar15;
      if (pHVar5 != DAT_004a2430) {
        DAT_004a2430 = pHVar5;
        pHVar6 = MonitorFromWindow(pHVar5,2);
        FUN_00406610(pHVar6);
        DAT_0049d9e0 = fVar8;
      }
      fVar15 = roundf((float)PStack_24.y / DAT_0049d9e0);
      fVar13 = (float)(int)local_34._4_4_;
      fVar8 = (float)(int)fVar14;
      local_14 = (float)fVar15;
      fVar12 = (float)(int)fVar15;
    }
    local_9c[0] = '\0';
    local_94 = 0;
    FUN_00451110(local_9c,(uint *)&DAT_0048d65c);
    local_8c[0] = 0;
    local_84 = 0;
    FUN_00450f50(local_8c,(int)local_18);
    local_8 = 0xf;
    FUN_00434b50(local_18c,local_9c,local_7c,'\x01','\x02');
    local_8._0_1_ = 0x11;
    _eh_vector_destructor_iterator_(local_9c,0x10,2,FUN_00434820);
    local_bc[0] = '\0';
    local_b4 = 0;
    FUN_00451110(local_bc,(uint *)&DAT_0048d660);
    local_ac[0] = 0;
    local_a4 = 0;
    FUN_00450f50(local_ac,(int)fVar13);
    local_8._0_1_ = 0x12;
    FUN_00434b50(local_17c,local_bc,local_9c,'\x01','\x02');
    local_8._0_1_ = 0x14;
    _eh_vector_destructor_iterator_(local_bc,0x10,2,FUN_00434820);
    local_dc[0] = '\0';
    local_d4 = 0;
    FUN_00451110(local_dc,(uint *)&DAT_0048d870);
    local_cc[0] = 0;
    local_c4 = 0;
    FUN_00450f50(local_cc,(int)fVar11 - (int)fVar8);
    local_8._0_1_ = 0x15;
    FUN_00434b50(local_16c,local_dc,local_bc,'\x01','\x02');
    local_8._0_1_ = 0x17;
    _eh_vector_destructor_iterator_(local_dc,0x10,2,FUN_00434820);
    local_fc[0] = '\0';
    local_f4 = 0;
    FUN_00451110(local_fc,(uint *)&DAT_0048d874);
    local_ec[0] = 0;
    local_e4 = 0;
    FUN_00450f50(local_ec,(int)fVar12 - (int)fVar13);
    local_8._0_1_ = 0x18;
    FUN_00434b50(local_15c,local_fc,local_dc,'\x01','\x02');
    local_8 = CONCAT31(local_8._1_3_,0x1a);
    _eh_vector_destructor_iterator_(local_fc,0x10,2,FUN_00434820);
    local_8 = 0x1b;
    FUN_00434b50(&local_2c,local_18c,local_14c,'\x01','\x02');
    local_8._0_1_ = 0x1c;
    puVar9 = FUN_00440e70(param_1,(uint *)&DAT_0048d814);
    uVar1 = *(undefined1 *)puVar9;
    *(undefined1 *)puVar9 = local_2c._0_1_;
    local_2c = (float)CONCAT31(local_2c._1_3_,uVar1);
    LVar2 = puVar9[2];
    LVar3 = puVar9[3];
    puVar9[2] = PStack_24.x;
    puVar9[3] = PStack_24.y;
    PStack_24.x = LVar2;
    PStack_24.y = LVar3;
    FUN_00434820((char *)&local_2c);
    local_8 = (uint)local_8._1_3_ << 8;
    _eh_vector_destructor_iterator_(local_18c,0x10,4,FUN_00434820);
  }
  ExceptionList = local_10;
  return param_1;
}


