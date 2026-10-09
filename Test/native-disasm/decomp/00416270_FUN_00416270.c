// FUN_00416270 @ 00416270 size=998 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_00416270(uint *param_1)

{
  uint uVar1;
  VARIANT varChild;
  VARIANT varChild_00;
  int *piVar2;
  uint *puVar3;
  char cVar4;
  bool bVar5;
  HRESULT HVar6;
  HWND pHVar7;
  int iVar8;
  BOOL BVar9;
  VARIANT *unaff_ESI;
  VARIANT *unaff_EDI;
  IAccessible *pIVar10;
  UINT UVar11;
  byte local_70 [24];
  _union_2683 local_58;
  undefined4 local_48;
  undefined4 uStack_44;
  int *piStack_40;
  int *piStack_3c;
  HWND local_34;
  uint *local_30;
  uint local_2c;
  IAccessible *local_28;
  char local_21;
  undefined1 *puStack_20;
  void *local_1c;
  undefined1 *puStack_18;
  undefined4 local_14;
  
  puStack_20 = &stack0xfffffffc;
  puStack_18 = &LAB_0047afc2;
  local_1c = ExceptionList;
  local_28 = (IAccessible *)0x0;
  local_14 = 0;
  ExceptionList = &local_1c;
  local_30 = param_1;
  HVar6 = AccessibleObjectFromEvent
                    ((HWND)param_1[1],param_1[2],param_1[3],&local_28,(VARIANT *)&local_58.n2);
  if ((HVar6 != 0) || (local_28 == (IAccessible *)0x0)) {
    if ((*param_1 == 0x8003) && ((HWND)param_1[1] == DAT_0049fc40)) {
      BVar9 = IsWindow(DAT_0049fc40);
      DAT_004a23c5 = DAT_004a23c5 & -(BVar9 != 0);
    }
    goto LAB_0041662f;
  }
  uVar1 = *param_1;
  local_48 = 0;
  uStack_44 = 0;
  piStack_40 = (int *)0x0;
  piStack_3c = (int *)0x0;
  varChild.n1.decVal.Hi32 = local_58._8_4_;
  varChild.n1._0_4_ = local_58.decVal.Hi32;
  varChild.n1._8_4_ = local_58._12_4_;
  varChild.n1._12_4_ = &local_48;
  pIVar10 = local_28;
  local_2c = uVar1;
  (*local_28->lpVtbl->get_accRole)(local_28,varChild,unaff_EDI);
  if (piStack_40 == (int *)0x0) {
    local_58._0_4_ = _DAT_0048e618;
    local_58.decVal.Hi32 = _UNK_0048e61c;
    local_58._8_4_ = _UNK_0048e620;
    local_58._12_4_ = _UNK_0048e624;
    local_48 = 0;
    uStack_44 = 0;
    piStack_40 = (int *)0x0;
    piStack_3c = (int *)0x0;
    if (local_28 != (IAccessible *)0x0) {
      pIVar10 = (IAccessible *)0x416335;
      varChild_00.n1.decVal.Hi32 = _UNK_0048e620;
      varChild_00.n1._0_4_ = _UNK_0048e61c;
      varChild_00.n1._8_4_ = _UNK_0048e624;
      varChild_00.n1._12_4_ = &local_48;
      (*local_28->lpVtbl->get_accRole)(local_28,varChild_00,unaff_ESI);
    }
  }
  if ((((piStack_40 == (int *)0xc) || (piStack_40 == (int *)0x22)) || (piStack_40 == (int *)0x2)) ||
     (((piStack_40 == (int *)0x15 || (piStack_40 == (int *)0xb)) || (piStack_40 == (int *)0x14)))) {
    bVar5 = true;
  }
  else {
    bVar5 = false;
  }
  piStack_3c = piStack_40;
  if (((uVar1 != 0x8005) || (bVar5)) && (piStack_40 != (int *)0x7)) {
    if ((*param_1 == 0x8003) && (piStack_40 == (int *)0x9)) {
      if ((HWND)param_1[1] == DAT_0049fc40) {
        DAT_004a23c5 = 0;
      }
      else {
        bVar5 = FUN_00404e90((HWND)param_1[1]);
        if (bVar5) {
          FUN_00404670((int *)&stack0xffffff70,DAT_0049fc40);
          cVar4 = FUN_004096c0((byte *)pIVar10);
          if (cVar4 != '\0') {
            _DAT_0049fc48 = param_1[4];
          }
        }
      }
    }
    else if ((*param_1 == 0x11b) && (piStack_40 == (int *)0x2a)) {
      iVar8 = FUN_0040bdb0((int *)&local_28,(undefined4 *)&local_58);
      if (iVar8 == 0x100004) {
        _DAT_004a2a34 = param_1[4];
      }
      else if ((iVar8 == 0x100000) && (0x32 < param_1[4] - _DAT_004a2a34)) {
        DAT_004a23c5 = 0;
      }
    }
    goto LAB_0041662f;
  }
  local_34 = GetAncestor((HWND)param_1[1],3);
  UVar11 = 3;
  pHVar7 = GetForegroundWindow();
  GetAncestor(pHVar7,UVar11);
  UVar11 = 3;
  pHVar7 = GetForegroundWindow();
  pHVar7 = GetAncestor(pHVar7,UVar11);
  if (local_34 != pHVar7) goto LAB_0041662f;
  if (local_2c == 0x8005) {
    local_2c = FUN_0040bdb0((int *)&local_28,(undefined4 *)&local_58);
    puVar3 = local_30;
    FUN_00404670((int *)local_70,(HWND)local_30[1]);
    local_14 = CONCAT31(local_14._1_3_,1);
    local_30 = (uint *)FUN_00435380(local_70,PTR_s_Chrome__0049da10);
    piVar2 = piStack_3c;
    if ((((piStack_3c == (int *)0x2a) || (piStack_3c == (int *)0x2e)) || (piStack_3c == (int *)0x34)
        ) || ((piStack_3c == (int *)0x32 || (local_21 = '\0', piStack_3c == (int *)0x3f)))) {
      local_21 = '\x01';
    }
    if (piStack_3c == (int *)&DAT_0000000f) {
      if ((local_2c & 4) == 0) goto LAB_00416478;
      cVar4 = FUN_00440970(local_70,PTR_s_Chrome_RenderWidgetHostHWND_0049d9f0);
LAB_0041646a:
      if (cVar4 == '\0') goto LAB_00416478;
    }
    else {
      if (((piStack_3c == (int *)0x10) && (local_2c == 0)) &&
         (puVar3[4] - _DAT_0049fc64 < (-(uint)(puVar3[4] - _DAT_0049fc48 < 300) & 0x96) + 0x32)) {
        FUN_00435680(&stack0xffffff70,(undefined4 *)local_70);
        cVar4 = FUN_004096c0((byte *)pIVar10);
        goto LAB_0041646a;
      }
LAB_00416478:
      if ((((byte)local_2c & 0x44) == 4) && (local_21 != '\0')) {
        DAT_004a23c5 = 1;
        if (((local_30 != (uint *)0x0) || (piVar2 != (int *)0x2a)) ||
           (cVar4 = FUN_00415e80((int *)&local_28,(HWND)puVar3[1]), cVar4 == '\0'))
        goto LAB_004164d7;
        DAT_004a23a1 = 1;
        FUN_00432bf0(&piStack_40,(int *)&local_28);
        piStack_3c = (int *)puVar3[1];
        FUN_00416660(&DAT_004a2840,&piStack_40);
        local_14 = CONCAT31(local_14._1_3_,2);
      }
      else {
        DAT_004a23c5 = 0;
LAB_004164d7:
        DAT_004a23a1 = 0;
        if (DAT_004a2844 == 0) goto LAB_00416514;
        piStack_40 = (int *)0x0;
        piStack_3c = (int *)0x0;
        FUN_00416660(&DAT_004a2840,&piStack_40);
        local_14 = CONCAT31(local_14._1_3_,3);
      }
      if (piStack_40 != (int *)0x0) {
        (**(code **)(*piStack_40 + 8))();
      }
    }
LAB_00416514:
    FUN_004061c0((undefined4 *)local_70);
  }
  else {
    DAT_004a23c5 = *local_30 == 0x8002;
    if ((bool)DAT_004a23c5) {
      _DAT_0049fc64 = local_30[4];
    }
    else {
      DAT_004a23a1 = 0;
      _DAT_004a23b8 = GetTickCount();
    }
  }
  if (DAT_004a23c5 != 0) {
    DAT_0049fc40 = local_34;
  }
LAB_0041662f:
  local_14 = 4;
  if (local_28 != (IAccessible *)0x0) {
    (*local_28->lpVtbl->Release)(local_28);
  }
  ExceptionList = local_1c;
  return;
}


