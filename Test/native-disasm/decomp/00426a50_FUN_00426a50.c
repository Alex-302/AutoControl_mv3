// FUN_00426a50 @ 00426a50 size=1012 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_00426a50(void *param_1)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  char *pcVar4;
  byte *pbVar5;
  void *pvVar6;
  IAccessible **ppIVar7;
  int *piVar8;
  UINT *pUVar9;
  double dVar10;
  ulonglong uVar11;
  int local_d8 [20];
  void *local_88 [4];
  undefined4 local_78;
  uint local_74;
  IAccessible *local_70;
  void *local_6c;
  undefined8 local_68;
  void *local_60 [4];
  undefined4 local_50;
  uint local_4c;
  void *local_48 [2];
  UINT local_40;
  UINT UStack_3c;
  undefined8 uStack_38;
  uint *local_2c;
  uint local_28;
  char local_21;
  undefined1 *puStack_20;
  void *local_1c;
  undefined1 *puStack_18;
  undefined4 local_14;
  
  puStack_20 = &stack0xfffffffc;
  local_14 = 0xffffffff;
  puStack_18 = &LAB_0047c58b;
  local_1c = ExceptionList;
  local_2c = (uint *)0x0;
  local_28 = 0;
  local_4c = 0xf;
  local_50 = 0;
  local_60[0] = (void *)((uint)local_60[0] & 0xffffff00);
  ExceptionList = &local_1c;
  local_6c = param_1;
  FUN_0043ace0(local_60,(uint *)"alignHorz",9);
  local_14 = 0;
  uStack_38._4_4_ = 0xf;
  uStack_38._0_4_ = 0;
  local_48[0] = (void *)((uint)local_48[0] & 0xffffff00);
  FUN_0043ace0(local_48,(uint *)"alignVert",9);
  local_14 = CONCAT31(local_14._1_3_,1);
  uVar2 = FUN_004409d0(param_1,local_48,0);
  uVar3 = FUN_004409d0(param_1,local_60,0);
  uVar2 = uVar2 | uVar3;
  if (0xf < uStack_38._4_4_) {
    FUN_00402430(local_48[0],uStack_38._4_4_ + 1,1);
  }
  local_14 = 0xffffffff;
  uStack_38._4_4_ = 0xf;
  uStack_38._0_4_ = 0;
  local_48[0] = (void *)((uint)local_48[0] & 0xffffff00);
  if (0xf < local_4c) {
    FUN_00402430(local_60[0],local_4c + 1,1);
  }
  pcVar4 = (char *)FUN_00440dd0(param_1,(uint *)"position");
  FUN_00451420(pcVar4,&local_21);
  local_4c = 0xf;
  local_50 = 0;
  local_60[0] = (void *)((uint)local_60[0] & 0xffffff00);
  FUN_0043ace0(local_60,(uint *)"usePrvMsPos",0xb);
  local_14 = 2;
  cVar1 = FUN_00441100(param_1,local_60);
  local_68 = FUN_0041e220(local_21,uVar2,cVar1);
  uStack_38._4_4_ = (uint)(local_68 >> 0x20);
  local_14 = 0xffffffff;
  uVar11 = local_68;
  if (0xf < local_4c) {
    uStack_38 = local_68;
    FUN_00402430(local_60[0],local_4c + 1,1);
    uVar11 = uStack_38 & 0xffffffff;
  }
  uStack_38._0_4_ = (int)uVar11;
  FUN_00432850(&DAT_004a2900);
  local_4c = 0xf;
  local_50 = 0;
  local_60[0] = (void *)((uint)local_60[0] & 0xffffff00);
  FUN_0043ace0(local_60,(uint *)"menuSystem",10);
  local_14 = 3;
  pbVar5 = (byte *)FUN_004342f0(param_1,local_88,local_60,(uint *)&DAT_0048e75c);
  local_2c = (uint *)(pbVar5 + 0x10);
  if (0xf < *(uint *)(pbVar5 + 0x14)) {
    pbVar5 = *(byte **)pbVar5;
  }
  uVar3 = 6;
  if (*local_2c < 6) {
    uVar3 = *local_2c;
  }
  uVar3 = FUN_004023d0(pbVar5,(byte *)"simple",uVar3);
  if (uVar3 == 0) {
    if (*local_2c < 6) {
      uVar3 = 0xffffffff;
    }
    else {
      uVar3 = (uint)(6 < *local_2c);
    }
  }
  if (0xf < local_74) {
    FUN_00402430(local_88[0],local_74 + 1,1);
  }
  local_14 = 0xffffffff;
  local_74 = 0xf;
  local_78 = 0;
  local_88[0] = (void *)((uint)local_88[0] & 0xffffff00);
  uVar11 = local_68;
  if (0xf < local_4c) {
    FUN_00402430(local_60[0],local_4c + 1,1);
    uVar11 = local_68;
  }
  local_68._4_4_ = (int)(uVar11 >> 0x20);
  local_68._0_4_ = (int)uVar11;
  local_68 = uVar11;
  if (uVar3 == 0) {
    pvVar6 = (void *)FUN_00440dd0(local_6c,(uint *)"menuData");
    FUN_0041d030(pvVar6,(LONG *)&uStack_38,uVar2);
    ExceptionList = local_1c;
    return;
  }
  if (((local_21 == 'M') && (((byte)uVar2 & 0x14) != 0x14)) && (DAT_0049da48 != -0x80000000)) {
    pvVar6 = (void *)(((int)local_68 - _DAT_0049da44) * ((int)local_68 - _DAT_0049da44) +
                     (local_68._4_4_ - DAT_0049da48) * (local_68._4_4_ - DAT_0049da48));
    dVar10 = (double)(int)pvVar6;
    __libm_sse2_sqrt_precise(pvVar6);
    uVar11 = local_68;
    if (dVar10 < DAT_0048f258) {
      ppIVar7 = FUN_0040b610(&local_70,(POINT *)&DAT_0049da44);
      local_14 = 4;
      local_2c = (uint *)0x1;
      pvVar6 = FUN_00414c40(local_d8,ppIVar7);
      local_14 = 5;
      local_28 = 3;
      local_2c = (uint *)0x3;
      piVar8 = FUN_00415660(pvVar6,'\x01');
      pUVar9 = (UINT *)FUN_00414e60(piVar8);
      local_40 = *pUVar9;
      UStack_3c = pUVar9[1];
      uStack_38._0_4_ = pUVar9[2] + local_40;
      uStack_38._4_4_ = pUVar9[3] + UStack_3c;
      uVar11 = local_68;
      goto LAB_00426d99;
    }
  }
  local_40 = 0;
  UStack_3c = 0;
  uStack_38._0_4_ = 0;
  uStack_38._4_4_ = 0;
LAB_00426d99:
  local_68 = uVar11;
  if ((local_28 & 2) != 0) {
    local_28 = local_28 & 0xfffffffd;
    FUN_004151a0(local_d8);
  }
  if (((local_28 & 1) != 0) && (local_14 = 6, local_70 != (IAccessible *)0x0)) {
    (*local_70->lpVtbl->Release)(local_70);
  }
  local_14 = 0xffffffff;
  uVar3 = 0;
  _DAT_0049da44 = DAT_0048e5f0;
  DAT_0049da48 = DAT_0048e5f4;
  pUVar9 = &local_40;
  if (((byte)uVar2 & 0x14) != 0x10) {
    uVar3 = 0x40;
  }
  uVar11 = local_68;
  pvVar6 = (void *)FUN_00440dd0(local_6c,(uint *)"menuData");
  FUN_0041de20(pvVar6,uVar3 | uVar2,(int)uVar11,(int)(uVar11 >> 0x20),pUVar9);
  ExceptionList = local_1c;
  return;
}


