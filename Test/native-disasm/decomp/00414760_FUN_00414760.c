// FUN_00414760 @ 00414760 size=1224 callers=4

uint __fastcall FUN_00414760(POINT *param_1,HWND param_2,uint param_3)

{
  uint *this;
  undefined1 *puVar1;
  bool bVar2;
  uint uVar3;
  float *pfVar4;
  HMONITOR pHVar5;
  BOOL BVar6;
  float10 fVar7;
  float fVar8;
  float fVar9;
  float local_70 [4];
  RECT local_60;
  tagRECT local_50;
  POINT *local_3c;
  uint local_38;
  float local_34;
  uint *local_30;
  uint local_2c;
  uint local_28;
  char local_21;
  undefined1 *puStack_20;
  void *local_1c;
  undefined1 *puStack_18;
  undefined4 local_14;
  
  puStack_20 = &stack0xfffffffc;
  local_14 = 0xffffffff;
  puStack_18 = &LAB_0047adbc;
  local_1c = ExceptionList;
  ExceptionList = &local_1c;
  local_3c = param_1;
  puVar1 = &stack0xfffffffc;
  if ((*(int *)(*(int *)ThreadLocalStoragePointer + 8) < DAT_004a2b64) &&
     (ExceptionList = &local_1c, FUN_0045a219(&DAT_004a2b64), puVar1 = puStack_20,
     DAT_004a2b64 == -1)) {
    local_14 = 0;
    _eh_vector_constructor_iterator_(&DAT_004a2ed0,0x20,3,FUN_00432410,thunk_FUN_004323a0);
    _atexit(FUN_0047f380);
    local_14 = 0xffffffff;
    FUN_0045a1da(&DAT_004a2b64);
    puVar1 = puStack_20;
  }
  puStack_20 = puVar1;
  local_28 = GetWindowLongA(param_2,-0x10);
  uVar3 = local_28;
  if ((local_28 & 0xc40000) != 0) {
    bVar2 = FUN_0040ea50(param_2,-1);
    if (bVar2) {
      local_28 = CONCAT31(local_28._1_3_,2);
    }
    else {
      uVar3 = local_28 >> 0x18 & 0xffffff01;
      if ((char)uVar3 == '\x03') goto LAB_00414c13;
      local_28 = uVar3;
      if ((char)uVar3 != '\x02') goto LAB_00414858;
    }
    uVar3 = param_3;
    if ((param_3 != 10) && (param_3 != 0x14)) {
LAB_00414858:
      local_50.left = 0;
      local_50.top = 0;
      local_50.right = 0;
      local_50.bottom = 0;
      GetWindowRect(param_2,&local_50);
      local_30 = (uint *)(&DAT_004a2ed0 + (local_28 & 0xff) * 0x20);
      FUN_00436250(local_30,(int *)&local_2c,(byte *)&param_3);
      this = local_30;
      uVar3 = local_2c;
      if (local_2c == local_30[1]) {
        local_30 = &param_3;
        FUN_0044a400(this,(int *)&local_38,this,&local_30);
        uVar3 = local_38;
      }
      local_21 = '\0';
      fVar9 = DAT_0049d9e0;
      if ((*(float *)(uVar3 + 0x14) == 0.0) && (*(float *)(uVar3 + 0x18) == 0.0)) {
        pfVar4 = FUN_00414360(param_2,(char)local_28,local_70,param_3);
        fVar9 = *pfVar4;
        local_34 = pfVar4[1];
        fVar8 = pfVar4[3];
        local_28 = (int)pfVar4[2] + (int)fVar9;
        local_2c = (int)fVar8 + (int)local_34;
        if (((int)(local_28 - (int)fVar9) < 10) || ((int)(local_2c - (int)local_34) < 10)) {
          local_21 = '\x01';
        }
        local_30 = (uint *)(float)((int)fVar9 - local_50.left);
        if (param_2 != DAT_004a2430) {
          DAT_004a2430 = param_2;
          pHVar5 = MonitorFromWindow(param_2,2);
          FUN_00406610(pHVar5);
          DAT_0049d9e0 = fVar8;
        }
        fVar9 = DAT_0049d9e0;
        *(float *)(uVar3 + 0xc) = (float)local_30 / DAT_0049d9e0;
        local_34 = (float)((int)local_34 - local_50.top);
        if (param_2 != DAT_004a2430) {
          DAT_004a2430 = param_2;
          pHVar5 = MonitorFromWindow(param_2,2);
          FUN_00406610(pHVar5);
          DAT_0049d9e0 = fVar9;
        }
        *(float *)(uVar3 + 0x10) = local_34 / fVar9;
        local_34 = (float)(int)(local_28 - local_50.right);
        if (param_2 != DAT_004a2430) {
          DAT_004a2430 = param_2;
          pHVar5 = MonitorFromWindow(param_2,2);
          FUN_00406610(pHVar5);
          DAT_0049d9e0 = fVar9;
        }
        *(float *)(uVar3 + 0x14) = local_34 / fVar9;
        local_34 = (float)(int)(local_2c - local_50.top);
        if (param_2 != DAT_004a2430) {
          DAT_004a2430 = param_2;
          pHVar5 = MonitorFromWindow(param_2,2);
          FUN_00406610(pHVar5);
          DAT_0049d9e0 = fVar9;
        }
        *(float *)(uVar3 + 0x18) = local_34 / fVar9;
      }
      local_34 = *(float *)(uVar3 + 0xc);
      if (param_2 != DAT_004a2430) {
        DAT_004a2430 = param_2;
        pHVar5 = MonitorFromWindow(param_2,2);
        FUN_00406610(pHVar5);
        DAT_0049d9e0 = fVar9;
      }
      fVar7 = roundf(local_34 * fVar9);
      local_60.left = (int)fVar7 + local_50.left;
      local_34 = *(float *)(uVar3 + 0x10);
      if (param_2 != DAT_004a2430) {
        DAT_004a2430 = param_2;
        pHVar5 = MonitorFromWindow(param_2,2);
        FUN_00406610(pHVar5);
        DAT_0049d9e0 = fVar9;
      }
      fVar9 = DAT_0049d9e0;
      fVar7 = roundf(local_34 * DAT_0049d9e0);
      local_60.top = (int)fVar7 + local_50.top;
      local_34 = *(float *)(uVar3 + 0x14);
      if (param_2 != DAT_004a2430) {
        DAT_004a2430 = param_2;
        pHVar5 = MonitorFromWindow(param_2,2);
        FUN_00406610(pHVar5);
        DAT_0049d9e0 = fVar9;
      }
      fVar9 = DAT_0049d9e0;
      fVar7 = roundf(local_34 * DAT_0049d9e0);
      local_60.right = (int)fVar7 + local_50.right;
      local_34 = *(float *)(uVar3 + 0x18);
      if (param_2 != DAT_004a2430) {
        DAT_004a2430 = param_2;
        pHVar5 = MonitorFromWindow(param_2,2);
        FUN_00406610(pHVar5);
        DAT_0049d9e0 = fVar9;
      }
      fVar7 = roundf(local_34 * DAT_0049d9e0);
      local_34 = (float)fVar7;
      local_60.bottom = (int)fVar7 + local_50.top;
      if (local_21 != '\0') {
        *(undefined4 *)(uVar3 + 0x14) = 0;
        *(undefined4 *)(uVar3 + 0x18) = 0;
      }
      BVar6 = PtInRect(&local_60,*local_3c);
      ExceptionList = local_1c;
      return (uint)(BVar6 != 0);
    }
  }
LAB_00414c13:
  ExceptionList = local_1c;
  return uVar3 & 0xffffff00;
}


