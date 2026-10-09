// FUN_00408c90 @ 00408c90 size=1168 callers=11

void __thiscall FUN_00408c90(void *this,void *param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  bool bVar5;
  char *pcVar6;
  DWORD DVar7;
  HWND hWndChildAfter;
  char *extraout_ECX;
  uint uVar8;
  int iVar9;
  undefined1 *this_00;
  uint in_stack_00000018;
  char local_ac [8];
  undefined8 local_a4;
  char local_9c [8];
  undefined8 local_94;
  char local_8c [8];
  undefined8 local_84;
  char local_7c [8];
  undefined8 local_74;
  char local_6c [8];
  undefined4 local_64;
  undefined4 local_60;
  char local_5c [8];
  undefined4 local_54;
  undefined4 local_50;
  char local_4c [8];
  undefined4 local_44;
  undefined4 local_40;
  uint local_38;
  undefined8 local_34;
  undefined1 *local_28;
  char local_24 [8];
  undefined8 local_1c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00479acf;
  local_10 = ExceptionList;
  local_38 = 0;
  local_8 = 0;
  ExceptionList = &local_10;
  local_28 = this;
  FUN_00440c80(local_24,&param_1);
  local_8._0_1_ = 1;
  pcVar6 = (char *)FUN_00440e70(this,(uint *)&DAT_0048cf60);
  local_8._0_1_ = 0;
  cVar1 = *pcVar6;
  *pcVar6 = local_24[0];
  uVar2 = *(undefined4 *)(pcVar6 + 8);
  uVar3 = *(undefined4 *)(pcVar6 + 0xc);
  *(undefined4 *)(pcVar6 + 8) = (undefined4)local_1c;
  *(undefined4 *)(pcVar6 + 0xc) = local_1c._4_4_;
  local_24[0] = cVar1;
  local_1c._0_4_ = uVar2;
  local_1c._4_4_ = uVar3;
  FUN_00434820(local_24);
  DVar7 = GetCurrentThreadId();
  FUN_00440c80(local_24,&DAT_004a2580);
  local_8 = CONCAT31(local_8._1_3_,2);
  pcVar6 = (char *)FUN_00440e70(this,(uint *)"osLang");
  cVar1 = *pcVar6;
  *pcVar6 = local_24[0];
  uVar4 = *(undefined8 *)(pcVar6 + 8);
  *(undefined4 *)(pcVar6 + 8) = (undefined4)local_1c;
  *(undefined4 *)(pcVar6 + 0xc) = local_1c._4_4_;
  local_24[0] = cVar1;
  local_1c = uVar4;
  FUN_00434820(local_24);
  iVar9 = 0;
  for (hWndChildAfter = FindWindowExA((HWND)0xfffffffd,(HWND)0x0,"ACNH_mainMsgWin",(LPCSTR)0x0);
      hWndChildAfter != (HWND)0x0;
      hWndChildAfter = FindWindowExA((HWND)0xfffffffd,hWndChildAfter,"ACNH_mainMsgWin",(LPCSTR)0x0))
  {
    iVar9 = iVar9 + 1;
  }
  local_24[0] = '\0';
  local_1c = 0;
  FUN_00451040(local_24,iVar9);
  this_00 = local_28;
  local_8._0_1_ = 3;
  pcVar6 = (char *)FUN_00440e70(local_28,(uint *)"peers");
  cVar1 = *pcVar6;
  *pcVar6 = local_24[0];
  uVar4 = *(undefined8 *)(pcVar6 + 8);
  *(undefined4 *)(pcVar6 + 8) = (undefined4)local_1c;
  *(undefined4 *)(pcVar6 + 0xc) = local_1c._4_4_;
  local_24[0] = cVar1;
  local_1c = uVar4;
  FUN_00434820(local_24);
  local_24[0] = '\0';
  local_1c = 0;
  FUN_00450f50(local_24,DAT_0049da0c);
  local_8._0_1_ = 4;
  pcVar6 = (char *)FUN_00440e70(this_00,(uint *)"lastMsg");
  local_8._0_1_ = 0;
  cVar1 = *pcVar6;
  *pcVar6 = local_24[0];
  uVar4 = *(undefined8 *)(pcVar6 + 8);
  *(undefined4 *)(pcVar6 + 8) = (undefined4)local_1c;
  *(undefined4 *)(pcVar6 + 0xc) = local_1c._4_4_;
  local_24[0] = cVar1;
  local_1c = uVar4;
  FUN_00434820(local_24);
  bVar5 = FUN_00404da0();
  if (!bVar5) {
    bVar5 = FUN_00404da0();
    uVar3 = local_34._4_4_;
    local_34 = CONCAT71(local_34._1_7_,bVar5);
    uVar2 = (undefined4)local_34;
    local_24[0] = '\x04';
    local_1c = CONCAT44(uVar3,(undefined4)local_34);
    local_8._0_1_ = 5;
    pcVar6 = (char *)FUN_00440e70(local_28,(uint *)"DWMCompos");
    local_8._0_1_ = 0;
    local_24[0] = *pcVar6;
    *pcVar6 = '\x04';
    local_1c = *(undefined8 *)(pcVar6 + 8);
    *(undefined4 *)(pcVar6 + 8) = uVar2;
    *(undefined4 *)(pcVar6 + 0xc) = uVar3;
    FUN_00434820(local_24);
    this_00 = local_28;
  }
  if (DAT_004a27b8 != 0) {
    local_24[0] = '\0';
    local_1c = 0;
    FUN_00451040(local_24,DAT_004a27b8);
    local_8._0_1_ = 6;
    pcVar6 = (char *)FUN_00440e70(this_00,(uint *)"numJoys");
    local_8._0_1_ = 0;
    cVar1 = *pcVar6;
    *pcVar6 = local_24[0];
    uVar4 = *(undefined8 *)(pcVar6 + 8);
    *(undefined4 *)(pcVar6 + 8) = (undefined4)local_1c;
    *(undefined4 *)(pcVar6 + 0xc) = local_1c._4_4_;
    local_24[0] = cVar1;
    local_1c = uVar4;
    FUN_00434820(local_24);
  }
  if (DVar7 == DAT_004a245c) {
    local_ac[0] = '\0';
    local_a4 = 0;
    FUN_00451110(local_ac,(uint *)&DAT_0048cf9c);
    pcVar6 = local_ac;
    local_38 = 1;
  }
  else {
    if (DVar7 == DAT_004a2450) {
      local_9c[0] = '\0';
      local_94 = 0;
      FUN_00451110(local_9c,(uint *)&DAT_0048cfa4);
      pcVar6 = local_9c;
      local_38 = 2;
    }
    else {
      if (DVar7 == DAT_004a23c8) {
        local_8c[0] = '\0';
        local_84 = 0;
        FUN_00451110(local_8c,(uint *)&DAT_0048cfa8);
        pcVar6 = local_8c;
        uVar8 = 4;
      }
      else {
        local_7c[0] = '\0';
        local_74 = 0;
        FUN_00451040(local_7c,DVar7);
        uVar8 = 8;
        pcVar6 = extraout_ECX;
      }
      local_6c[0] = *pcVar6;
      local_64 = *(undefined4 *)(pcVar6 + 8);
      local_60 = *(undefined4 *)(pcVar6 + 0xc);
      local_34 = 0;
      *pcVar6 = '\0';
      pcVar6[8] = '\0';
      pcVar6[9] = '\0';
      pcVar6[10] = '\0';
      pcVar6[0xb] = '\0';
      *(uint *)(pcVar6 + 0xc) = local_34._4_4_;
      pcVar6 = local_6c;
      local_38 = uVar8 | 0x10;
    }
    local_5c[0] = *pcVar6;
    local_54 = *(undefined4 *)(pcVar6 + 8);
    local_50 = *(undefined4 *)(pcVar6 + 0xc);
    local_34 = 0;
    *pcVar6 = '\0';
    pcVar6[8] = '\0';
    pcVar6[9] = '\0';
    pcVar6[10] = '\0';
    pcVar6[0xb] = '\0';
    pcVar6[0xc] = '\0';
    pcVar6[0xd] = '\0';
    pcVar6[0xe] = '\0';
    pcVar6[0xf] = '\0';
    pcVar6 = local_5c;
    local_38 = local_38 | 0x20;
  }
  cVar1 = *pcVar6;
  uVar2 = *(undefined4 *)(pcVar6 + 8);
  uVar3 = *(undefined4 *)(pcVar6 + 0xc);
  local_1c = 0;
  *pcVar6 = '\0';
  pcVar6[8] = '\0';
  pcVar6[9] = '\0';
  pcVar6[10] = '\0';
  pcVar6[0xb] = '\0';
  pcVar6[0xc] = '\0';
  pcVar6[0xd] = '\0';
  pcVar6[0xe] = '\0';
  pcVar6[0xf] = '\0';
  local_8 = 0xd;
  local_4c[0] = cVar1;
  local_44 = uVar2;
  local_40 = uVar3;
  local_34._4_4_ = local_38;
  pcVar6 = (char *)FUN_00440e70(local_28,(uint *)"thread");
  local_4c[0] = *pcVar6;
  *pcVar6 = cVar1;
  local_40 = *(undefined4 *)(pcVar6 + 0xc);
  local_44 = *(undefined4 *)(pcVar6 + 8);
  *(undefined4 *)(pcVar6 + 8) = uVar2;
  *(undefined4 *)(pcVar6 + 0xc) = uVar3;
  FUN_00434820(local_4c);
  uVar8 = local_34._4_4_;
  if ((local_34._4_4_ & 0x20) != 0) {
    uVar8 = local_34._4_4_ & 0xffffffdf;
    FUN_00434820(local_5c);
  }
  if ((uVar8 & 0x10) != 0) {
    uVar8 = uVar8 & 0xffffffef;
    FUN_00434820(local_6c);
  }
  if ((uVar8 & 8) != 0) {
    uVar8 = uVar8 & 0xfffffff7;
    FUN_00434820(local_7c);
  }
  if ((uVar8 & 4) != 0) {
    uVar8 = uVar8 & 0xfffffffb;
    FUN_00434820(local_8c);
  }
  if ((uVar8 & 2) != 0) {
    uVar8 = uVar8 & 0xfffffffd;
    FUN_00434820(local_9c);
  }
  local_8 = 0;
  if ((uVar8 & 1) != 0) {
    FUN_00434820(local_ac);
  }
  FUN_00408600(800,local_28);
  if (0xf < in_stack_00000018) {
    FUN_00402430(param_1,in_stack_00000018 + 1,1);
  }
  ExceptionList = local_10;
  return;
}


