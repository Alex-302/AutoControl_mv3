// FUN_0040b030 @ 0040b030 size=663 callers=1

HDC __fastcall
FUN_0040b030(HDC param_1,HWND param_2,int *param_3,int *param_4,int param_5,HDC param_6)

{
  int iVar1;
  undefined4 *puVar2;
  int *piVar3;
  HDC pHVar4;
  bool bVar5;
  HDC pHVar6;
  undefined4 uVar7;
  HDC pHVar8;
  RECT local_3c;
  undefined4 local_2c;
  HDC local_28;
  HDC local_24;
  int local_20;
  int local_1c;
  HDC local_18;
  HWND local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  piVar3 = param_4;
  puStack_c = &LAB_00479df9;
  local_10 = ExceptionList;
  param_4 = (int *)((param_4[3] * param_5) / param_4[2]);
  if ((int)param_6 < (int)param_4) {
    param_5 = (param_5 * (int)param_6) / (int)param_4;
    param_4 = &param_6->unused;
  }
  iVar1 = param_5;
  local_20 = *piVar3 - *param_3;
  local_1c = piVar3[1] - param_3[1];
  ExceptionList = &local_10;
  param_1->unused = 0;
  local_8 = 0;
  local_3c.left = *piVar3;
  local_3c.top = piVar3[1];
  local_3c.right = piVar3[2] + local_3c.left;
  local_3c.bottom = piVar3[3] + local_3c.top;
  local_2c = 1;
  local_28 = param_1;
  local_14 = param_2;
  bVar5 = FUN_00406c50(param_2,&local_3c);
  if (bVar5) {
    local_28 = GetDC((HWND)0x0);
    pHVar6 = (HDC)FUN_0040af40(&param_6,local_28,*piVar3,piVar3[1],piVar3[2],piVar3[3],iVar1,
                               (int)param_4);
    if (param_1 != pHVar6) {
      iVar1 = pHVar6->unused;
      pHVar6->unused = 0;
      puVar2 = (undefined4 *)param_1->unused;
      param_1->unused = iVar1;
      if (puVar2 != (undefined4 *)0x0) {
        (**(code **)*puVar2)(1);
      }
    }
    if (param_6 != (HDC)0x0) {
      (**(code **)param_6->unused)(1);
    }
    ReleaseDC((HWND)0x0,local_28);
  }
  else {
    bVar5 = FUN_00404da0();
    if (bVar5) {
      local_28 = GetWindowDC(local_14);
      pHVar6 = (HDC)FUN_0040af40(&param_6,local_28,local_20,local_1c,piVar3[2],piVar3[3],iVar1,
                                 (int)param_4);
      if (param_1 != pHVar6) {
        iVar1 = pHVar6->unused;
        pHVar6->unused = 0;
        puVar2 = (undefined4 *)param_1->unused;
        param_1->unused = iVar1;
        if (puVar2 != (undefined4 *)0x0) {
          (**(code **)*puVar2)(1);
        }
      }
      if (param_6 != (HDC)0x0) {
        (**(code **)param_6->unused)(1);
      }
      ReleaseDC(local_14,local_28);
      uVar7 = FUN_0040ae30(param_1->unused,'\x01');
      if ((char)uVar7 != '\0') {
        puVar2 = (undefined4 *)param_1->unused;
        param_1->unused = 0;
        if (puVar2 == (undefined4 *)0x0) goto LAB_0040b1d4;
        (**(code **)*puVar2)(1);
      }
    }
  }
  if (param_1->unused != 0) {
    ExceptionList = local_10;
    return param_1;
  }
LAB_0040b1d4:
  param_6 = (HDC)0x26200a;
  FUN_00441420(&local_24,param_3 + 2,param_3 + 3,&param_6);
  pHVar6 = local_24;
  local_28 = (HDC)0x0;
  param_6 = (HDC)0x0;
  if (local_24 != (HDC)0x0) {
    GdipGetImageGraphicsContext(local_24[1].unused,&param_6);
    local_28 = param_6;
  }
  local_18 = (HDC)0x0;
  param_6 = local_28;
  GdipGetDC(local_28,&local_18);
  local_24 = local_18;
  uVar7 = FUN_0040ad80(local_14,local_18,param_3[2],param_3[3]);
  pHVar4 = local_24;
  if ((char)uVar7 != '\0') {
    pHVar8 = (HDC)FUN_0040af40(&param_3,local_24,local_20,local_1c,piVar3[2],piVar3[3],param_5,
                               (int)param_4);
    if (param_1 != pHVar8) {
      iVar1 = pHVar8->unused;
      pHVar8->unused = 0;
      puVar2 = (undefined4 *)param_1->unused;
      param_1->unused = iVar1;
      if (puVar2 != (undefined4 *)0x0) {
        (**(code **)*puVar2)(1);
      }
    }
    if (param_3 != (int *)0x0) {
      (**(code **)*param_3)(1);
    }
  }
  pHVar8 = local_28;
  GdipReleaseDC(local_28,pHVar4);
  GdipDeleteGraphics(pHVar8);
  if (pHVar6 != (HDC)0x0) {
    (**(code **)pHVar6->unused)(1);
  }
  ExceptionList = local_10;
  return param_1;
}


