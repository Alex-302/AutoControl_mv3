// FUN_00406c50 @ 00406c50 size=294 callers=1

bool __fastcall FUN_00406c50(HWND param_1,RECT *param_2)

{
  void *pvVar1;
  BOOL BVar2;
  int iVar3;
  bool bVar4;
  float10 fVar5;
  float in_XMM2_Da;
  ulonglong uVar6;
  void *local_30;
  void *local_2c;
  void *local_28;
  void *local_24;
  HWND local_20;
  void **local_1c;
  void *local_18;
  float local_14;
  void *local_10;
  undefined1 *puStack_c;
  void *local_8;
  
  local_8 = (void *)0xffffffff;
  puStack_c = &LAB_00479608;
  local_10 = ExceptionList;
  iVar3 = (param_2->bottom - param_2->top) * (param_2->right - param_2->left);
  if (iVar3 < 0) {
    iVar3 = 0;
  }
  ExceptionList = &local_10;
  fVar5 = roundf((float)((double)iVar3 + (double)(&DAT_0048f2d0)[-(iVar3 >> 0x1f)]) * in_XMM2_Da);
  local_14 = (float)fVar5;
  uVar6 = FUN_00477bf0();
  pvVar1 = (void *)uVar6;
  BVar2 = IsWindowVisible(param_1);
  if (BVar2 != 0) {
    local_30 = (void *)IsIconic(param_1);
    if (local_30 == (void *)0x0) {
      local_1c = &local_30;
      local_2c = local_30;
      local_28 = local_30;
      local_24 = local_30;
      local_20 = param_1;
      local_18 = pvVar1;
      local_8 = local_30;
      EnumDisplayMonitors((HDC)0x0,param_2,FUN_00406d80,(LPARAM)&local_20);
      FUN_00406900(&local_30,param_2);
      if (local_24 < pvVar1) {
        bVar4 = false;
      }
      else {
        EnumWindows(thunk_FUN_00406da0,(LPARAM)&local_20);
        bVar4 = pvVar1 <= local_24;
      }
      if (local_30 != (void *)0x0) {
        FUN_00402430(local_30,(int)local_28 - (int)local_30 >> 4,0x10);
      }
      ExceptionList = local_10;
      return bVar4;
    }
  }
  ExceptionList = local_10;
  return pvVar1 == (void *)0x0;
}


