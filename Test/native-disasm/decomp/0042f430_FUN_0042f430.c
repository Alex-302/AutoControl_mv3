// FUN_0042f430 @ 0042f430 size=994 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_0042f430(undefined4 *param_1)

{
  undefined1 uVar1;
  VARIANT varChild;
  VARIANT varChild_00;
  undefined8 uVar2;
  undefined8 uVar3;
  uint uVar4;
  HRESULT HVar5;
  undefined4 *puVar6;
  int *piVar7;
  int iVar8;
  LPCWSTR pWVar9;
  LPSTR pCVar10;
  VARIANT *unaff_EDI;
  char cVar11;
  undefined4 uVar12;
  undefined4 uVar13;
  IAccessible *pIVar14;
  undefined4 uVar15;
  undefined4 local_70 [6];
  CHAR local_58 [24];
  HRESULT local_40;
  int *local_3c;
  void *local_38 [2];
  uint local_30 [2];
  undefined8 uStack_28;
  int *local_20;
  undefined4 *local_1c;
  IAccessible *local_18;
  char local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047d468;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  uVar4 = FUN_00414760(*param_1,*(HWND *)param_1[1],10);
  if ((char)uVar4 == '\0') {
    ExceptionList = local_10;
    return;
  }
  uVar12 = 0x42f472;
  HVar5 = CoInitializeEx((LPVOID)0x0,2);
  local_8 = 0;
  local_40 = HVar5;
  FUN_0040b610(&local_18,(POINT *)*param_1);
  local_8._0_1_ = 1;
  if (0x68 < DAT_004a23a4) {
    puVar6 = FUN_0040b9e0(&local_3c,(int *)&local_18);
    local_8._0_1_ = 2;
    piVar7 = FUN_0040b880((undefined4 *)((int)&uStack_28 + 4),puVar6,0);
    local_8._0_1_ = 3;
    uVar12 = 0x42f4c4;
    local_1c = FUN_0040b650(&local_20,piVar7,(undefined4 *)*param_1);
    local_8._0_1_ = 4;
    if (local_18 != (IAccessible *)0x0) {
      (*local_18->lpVtbl->Release)(local_18);
    }
    local_18 = (IAccessible *)*local_1c;
    *local_1c = 0;
    local_8._0_1_ = 5;
    if (local_20 != (int *)0x0) {
      (**(code **)(*local_20 + 8))();
    }
    local_8._0_1_ = 6;
    if (uStack_28._4_4_ != (int *)0x0) {
      (**(code **)(*uStack_28._4_4_ + 8))();
    }
    local_8._0_1_ = 7;
    if (local_3c != (int *)0x0) {
      (**(code **)(*local_3c + 8))();
    }
  }
  local_8._0_1_ = 1;
  local_30[0] = 0;
  local_30[1] = 0;
  uStack_28 = 0;
  if (local_18 != (IAccessible *)0x0) {
    varChild.n1.decVal.Hi32 = _UNK_0048e620;
    varChild.n1._0_4_ = _UNK_0048e61c;
    varChild.n1._8_4_ = _UNK_0048e624;
    varChild.n1._12_4_ = local_30;
    uVar12 = _UNK_0048e620;
    (*local_18->lpVtbl->get_accRole)(local_18,varChild,unaff_EDI);
  }
  if ((int)uStack_28 == 0x3c) {
    local_3c = FUN_0040b930((undefined4 *)((int)&uStack_28 + 4),(int *)&local_18,5);
    local_8._0_1_ = 8;
    if (local_18 != (IAccessible *)0x0) {
      (*local_18->lpVtbl->Release)(local_18);
    }
    local_18 = (IAccessible *)*local_3c;
    *local_3c = 0;
    local_8._0_1_ = 9;
    if (uStack_28._4_4_ != (int *)0x0) {
      (**(code **)(*uStack_28._4_4_ + 8))();
    }
    local_8._0_1_ = 1;
    local_30[0] = 0;
    local_30[1] = 0;
    uStack_28 = 0;
    if (local_18 != (IAccessible *)0x0) {
      varChild_00.n1.decVal.Hi32 = _UNK_0048e620;
      varChild_00.n1._0_4_ = _UNK_0048e61c;
      varChild_00.n1._8_4_ = _UNK_0048e624;
      varChild_00.n1._12_4_ = local_30;
      uVar12 = _UNK_0048e620;
      (*local_18->lpVtbl->get_accRole)(local_18,varChild_00,unaff_EDI);
    }
    uVar2 = uStack_28;
    if ((int)uStack_28 != 0x25) {
LAB_0042f763:
      local_8 = CONCAT31(local_8._1_3_,0xf);
      goto LAB_0042f7ee;
    }
    local_3c = (int *)&stack0xffffff78;
    uStack_28 = CONCAT71(uStack_28._1_7_,1);
    uVar3 = uStack_28;
    uStack_28._4_4_ = SUB84(uVar2,4);
    cVar11 = '\x04';
    local_8._0_1_ = 0xb;
    uVar13 = (int)uStack_28;
    uVar15 = uStack_28._4_4_;
    uStack_28 = uVar3;
    puVar6 = FUN_00440e70((void *)param_1[2],(uint *)"group");
    local_8._0_1_ = 1;
    FUN_004348c0(puVar6,cVar11,uVar12,uVar13,uVar15);
  }
  else if ((int)uStack_28 != 0x25) {
    iVar8 = 2;
    local_8._0_1_ = 1;
    pIVar14 = local_18;
    if (local_18 != (IAccessible *)0x0) {
      (*local_18->lpVtbl->AddRef)(local_18);
    }
    local_3c = FUN_0040ba70((undefined4 *)((int)&uStack_28 + 4),0x25,(int *)pIVar14,iVar8);
    local_8._0_1_ = 0xd;
    if (local_18 != (IAccessible *)0x0) {
      (*local_18->lpVtbl->Release)(local_18);
    }
    local_18 = (IAccessible *)*local_3c;
    *local_3c = 0;
    local_8._0_1_ = 0xe;
    if (uStack_28._4_4_ != (int *)0x0) {
      (**(code **)(*uStack_28._4_4_ + 8))();
    }
    local_8._0_1_ = 1;
    if (local_18 == (IAccessible *)0x0) goto LAB_0042f763;
  }
  uStack_28 = 0xf00000000;
  local_38[0] = (void *)((uint)local_38[0] & 0xffffff00);
  FUN_0043ace0(local_38,(uint *)"getIdx",6);
  local_8._0_1_ = 0x10;
  local_11 = FUN_00441100((void *)param_1[3],local_38);
  local_8._0_1_ = 1;
  if (0xf < uStack_28._4_4_) {
    FUN_00402430(local_38[0],(int)uStack_28._4_4_ + 1,1);
  }
  if (local_11 == '\0') {
    pWVar9 = (LPCWSTR)FUN_0040bdf0(local_70,(int *)&local_18);
    local_8._0_1_ = 0x13;
    pCVar10 = FUN_00404580(local_58,pWVar9,500);
    local_8._0_1_ = 0x14;
    FUN_00440c80(local_30,(undefined4 *)pCVar10);
    local_8 = CONCAT31(local_8._1_3_,0x15);
    puVar6 = FUN_00440e70((void *)param_1[2],(uint *)"title");
    uVar1 = *(undefined1 *)puVar6;
    *(undefined1 *)puVar6 = (undefined1)local_30[0];
    local_30[0] = CONCAT31(local_30[0]._1_3_,uVar1);
    uVar2 = *(undefined8 *)(puVar6 + 2);
    puVar6[2] = (int)uStack_28;
    puVar6[3] = uStack_28._4_4_;
    uStack_28 = uVar2;
    FUN_00434820((char *)local_30);
    FUN_004061c0((undefined4 *)local_58);
    FUN_00435170(local_70);
  }
  else {
    local_8._0_1_ = 1;
    pIVar14 = local_18;
    if (local_18 != (IAccessible *)0x0) {
      (*local_18->lpVtbl->AddRef)(local_18);
    }
    iVar8 = FUN_0040ed80((int *)pIVar14);
    local_30[0] = local_30[0] & 0xffffff00;
    uStack_28 = 0;
    FUN_00450f50((undefined1 *)local_30,iVar8);
    local_8 = CONCAT31(local_8._1_3_,0x12);
    puVar6 = FUN_00440e70((void *)param_1[2],(uint *)"index");
    uVar1 = *(undefined1 *)puVar6;
    *(undefined1 *)puVar6 = (undefined1)local_30[0];
    local_30[0] = CONCAT31(local_30[0]._1_3_,uVar1);
    uVar2 = *(undefined8 *)(puVar6 + 2);
    puVar6[2] = (int)uStack_28;
    puVar6[3] = uStack_28._4_4_;
    uStack_28 = uVar2;
    FUN_00434820((char *)local_30);
  }
  local_8 = CONCAT31(local_8._1_3_,0x16);
LAB_0042f7ee:
  if (local_18 != (IAccessible *)0x0) {
    (*local_18->lpVtbl->Release)(local_18);
  }
  if (-1 < HVar5) {
    CoUninitialize();
  }
  ExceptionList = local_10;
  return;
}


