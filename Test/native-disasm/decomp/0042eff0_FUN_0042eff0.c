// FUN_0042eff0 @ 0042eff0 size=1083 callers=1

void * __cdecl FUN_0042eff0(void *param_1,char *param_2)

{
  bool bVar1;
  uint uVar2;
  char cVar3;
  char *pcVar4;
  HWND pHVar5;
  int iVar6;
  int *piVar7;
  uint uVar8;
  byte *in_stack_ffffff14;
  UINT gaFlags;
  char local_c4 [16];
  undefined1 local_b4 [16];
  undefined1 local_a4 [16];
  char local_94 [8];
  ulonglong local_8c;
  undefined1 local_84 [8];
  undefined8 local_7c;
  POINT local_74;
  undefined **local_6c;
  POINT *local_68;
  HWND *ppHStack_64;
  void *pvStack_60;
  ulonglong uStack_5c;
  undefined1 local_54 [8];
  undefined8 local_4c;
  char local_44 [8];
  undefined8 local_3c;
  POINT *local_34;
  HWND *ppHStack_30;
  undefined8 uStack_2c;
  char local_24 [4];
  HWND local_20;
  uint local_1c;
  int local_18;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_0047d3c5;
  local_10 = ExceptionList;
  local_8 = 0;
  local_1c = 0;
  ExceptionList = &local_10;
  FUN_00434a40(param_1,(char *)0x0,(char *)0x0);
  uVar8 = 1;
  bVar1 = false;
  local_8 = 0;
  local_1c = 1;
  local_7c = 0xf00000000;
  local_8c = local_8c & 0xffffffffffffff00;
  FUN_0043ace0(&local_8c,(uint *)&DAT_0048d65c,1);
  if (*param_2 == '\x01') {
    FUN_004437f0(*(void **)(param_2 + 8),(int *)&uStack_2c,(byte *)&local_8c);
    local_14 = FUN_00447a70((int *)uStack_2c,uStack_2c._4_4_);
  }
  else {
    local_14 = 0;
  }
  if (0xf < local_7c._4_4_) {
    FUN_00402430((void *)local_8c,local_7c._4_4_ + 1,1);
  }
  local_7c = 0xf00000000;
  local_8c = local_8c & 0xffffffffffffff00;
  if (local_14 == 0) {
    local_4c = 0xf00000000;
    uStack_5c = uStack_5c & 0xffffffffffffff00;
    FUN_0043ace0(&uStack_5c,(uint *)"usePrvMsPos",0xb);
    local_8 = 1;
    uVar8 = 3;
    bVar1 = true;
    local_1c = 3;
    cVar3 = FUN_00441100(param_2,(undefined4 *)&uStack_5c);
    if (cVar3 == '\0') {
      uStack_2c = FUN_00410800('\0');
    }
    else {
      uStack_2c = CONCAT44(DAT_004a23e4,DAT_004a23e0);
    }
    local_18 = (int)(int *)uStack_2c;
    piVar7 = &local_18;
    local_14 = (uint)uStack_2c._4_4_;
  }
  else {
    pcVar4 = (char *)FUN_00440e70(param_2,(uint *)&DAT_0048d65c);
    FUN_004536b0(pcVar4,&local_14);
    uVar2 = local_14;
    pcVar4 = (char *)FUN_00440e70(param_2,(uint *)&DAT_0048d660);
    FUN_004536b0(pcVar4,&local_14);
    piVar7 = (int *)&uStack_2c;
    uStack_2c = CONCAT44(local_14,uVar2);
  }
  local_74.x = *piVar7;
  local_74.y = piVar7[1];
  local_8 = 0;
  if (bVar1) {
    local_1c = uVar8 & 0xfffffffd;
    if (0xf < local_4c._4_4_) {
      FUN_00402430((void *)uStack_5c,(int)local_4c._4_4_ + 1,1);
    }
  }
  pHVar5 = FUN_00404e30(&local_74,'\0');
  iVar6 = GetWindowTextA(pHVar5,(LPSTR)&local_14,2);
  if (iVar6 == 0) {
    FUN_00404670((int *)&stack0xffffff14,pHVar5);
    cVar3 = FUN_004096c0(in_stack_ffffff14);
    if (cVar3 != '\0') {
      gaFlags = 3;
      pHVar5 = GetForegroundWindow();
      pHVar5 = GetAncestor(pHVar5,gaFlags);
    }
  }
  if (pHVar5 != (HWND)0x0) {
    local_68 = (POINT *)((int)&local_14 + 3);
    local_14 = local_14 & 0xffffff;
    ppHStack_64 = &local_20;
    local_6c = &PTR_LAB_0048f084;
    local_8 = 2;
    local_20 = pHVar5;
    local_4c._4_4_ = &local_6c;
    FUN_0040f7a0(DAT_004a2458,(int *)&local_6c);
    local_8 = local_8 & 0xffffff00;
    if (local_4c._4_4_ != (undefined ***)0x0) {
      (*(code *)(*local_4c._4_4_)[4])();
    }
    if (local_14._3_1_ != '\0') {
      local_44[0] = '\0';
      local_3c = 0;
      FUN_00451110(local_44,(uint *)&DAT_0048d7f8);
      FUN_00442050(&local_34,(int *)&local_20);
      local_8 = 3;
      FUN_00434b50(local_c4,local_44,local_24,'\x01','\x02');
      local_8._0_1_ = 5;
      _eh_vector_destructor_iterator_(local_44,0x10,2,FUN_00434820);
      ppHStack_64 = (HWND *)((uint)ppHStack_64 & 0xffffff00);
      uStack_5c = 0;
      FUN_00451110((undefined1 *)&ppHStack_64,(uint *)&DAT_0048d65c);
      local_54[0] = 0;
      local_4c = 0;
      FUN_00450f50(local_54,local_74.x);
      local_8._0_1_ = 6;
      FUN_00434b50(local_b4,(char *)&ppHStack_64,local_44,'\x01','\x02');
      local_8._0_1_ = 8;
      _eh_vector_destructor_iterator_(&ppHStack_64,0x10,2,FUN_00434820);
      local_94[0] = '\0';
      local_8c = 0;
      FUN_00451110(local_94,(uint *)&DAT_0048d660);
      local_84[0] = 0;
      local_7c = 0;
      FUN_00450f50(local_84,local_74.y);
      local_8._0_1_ = 9;
      FUN_00434b50(local_a4,local_94,(char *)&local_74,'\x01','\x02');
      local_8 = CONCAT31(local_8._1_3_,0xb);
      _eh_vector_destructor_iterator_(local_94,0x10,2,FUN_00434820);
      local_8 = 0xc;
      FUN_00433d20(param_1,local_c4,local_94);
      local_8 = local_8 & 0xffffff00;
      _eh_vector_destructor_iterator_(local_c4,0x10,3,FUN_00434820);
      local_68 = &local_74;
      ppHStack_64 = &local_20;
      uStack_2c = CONCAT44(param_2,param_1);
      local_6c = &PTR_LAB_0048e950;
      pvStack_60 = param_1;
      uStack_5c = CONCAT44(uStack_5c._4_4_,param_2);
      local_8 = 0xd;
      local_34 = local_68;
      ppHStack_30 = ppHStack_64;
      local_4c._4_4_ = &local_6c;
      FUN_0040f7a0(DAT_004a23dc,(int *)&local_6c);
      if (local_4c._4_4_ != (undefined ***)0x0) {
        (*(code *)(*local_4c._4_4_)[4])();
      }
    }
  }
  ExceptionList = local_10;
  return param_1;
}


