// FUN_0041de20 @ 0041de20 size=439 callers=1

void __fastcall FUN_0041de20(void *param_1,uint param_2,int param_3,int param_4,UINT *param_5)

{
  void *this;
  byte *pbVar1;
  HMENU hMenu;
  HHOOK hhk;
  void **ppvVar2;
  void *local_50 [4];
  undefined4 local_40;
  uint local_3c;
  undefined1 local_38 [12];
  UINT UStack_2c;
  HBRUSH pHStack_28;
  DWORD DStack_24;
  ULONG_PTR UStack_20;
  tagPOINT local_1c;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047b888;
  local_10 = ExceptionList;
  ppvVar2 = local_50;
  DAT_004a29bc = 0;
  DAT_004a29c0 = 0;
  DAT_004a29c4 = 0;
  ExceptionList = &local_10;
  local_14 = param_2;
  this = (void *)FUN_00440dd0(param_1,(uint *)"style");
  pbVar1 = (byte *)FUN_00440d90(this,ppvVar2);
  local_8 = 0;
  pbVar1 = FUN_00432630(&DAT_004a296c,pbVar1);
  hMenu = FUN_0041dab0((void *)0x0,*(uint *)(pbVar1 + 0x70));
  local_8 = 0xffffffff;
  if (0xf < local_3c) {
    FUN_00402430(local_50[0],local_3c + 1,1);
  }
  local_3c = 0xf;
  local_40 = 0;
  local_50[0] = (void *)((uint)local_50[0] & 0xffffff00);
  DAT_004a2998 = hMenu;
  FUN_0041db40(hMenu,param_1);
  if ((param_3 == -0x80000000) || (param_4 == -0x80000000)) {
    GetCursorPos(&local_1c);
    param_3 = local_1c.x;
    param_4 = local_1c.y;
  }
  DAT_004a2994 = GetForegroundWindow();
  DAT_0049d9f5 = 0;
  hhk = SetWindowsHookExA(-1,FUN_0041fa40,(HINSTANCE)0x0,DAT_004a2450);
  local_38._8_4_ = 0x14;
  UStack_2c = *param_5;
  pHStack_28 = (HBRUSH)param_5[1];
  DStack_24 = param_5[2];
  UStack_20 = param_5[3];
  TrackPopupMenuEx(hMenu,local_14 | 0x100,param_3,param_4,
                   *(HWND *)(&DAT_004a2470 + *(int *)(*(int *)ThreadLocalStoragePointer + 4) * 4),
                   (LPTPMPARAMS)(local_38 + 8));
  UnhookWindowsHookEx(hhk);
  DAT_0049d9f5 = 1;
  local_38._0_4_ = 0x1c;
  local_38._4_4_ = 2;
  local_38._8_4_ = 0;
  UStack_2c = 0;
  pHStack_28 = (HBRUSH)0x0;
  DStack_24 = 0;
  UStack_20 = 0;
  GetMenuInfo(hMenu,(LPMENUINFO)local_38);
  if (pHStack_28 != (HBRUSH)0x0) {
    DeleteObject(pHStack_28);
  }
  DestroyMenu(hMenu);
  DAT_004a2998 = (HMENU)0x0;
  FUN_00432530();
  FUN_0041a0b0();
  ExceptionList = local_10;
  return;
}


