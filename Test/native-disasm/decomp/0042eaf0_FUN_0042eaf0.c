// FUN_0042eaf0 @ 0042eaf0 size=464 callers=1

undefined1 * __cdecl FUN_0042eaf0(undefined1 *param_1,void *param_2)

{
  POINT pt;
  undefined8 uVar1;
  undefined8 uVar2;
  char cVar3;
  char *pcVar4;
  uint uVar5;
  HWND hwnd;
  HMONITOR pHVar6;
  char *pcVar7;
  DWORD dwFlags;
  void *local_44 [4];
  undefined4 local_34;
  uint local_30;
  char local_2c [8];
  undefined8 local_24;
  undefined4 local_1c;
  tagPOINT local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047d2a4;
  local_10 = ExceptionList;
  local_1c = 0;
  ExceptionList = &local_10;
  pcVar4 = (char *)FUN_00440e70(param_2,(uint *)"point");
  local_18.y = 0x48dbdc;
  local_8 = 0;
  local_2c[0] = '\0';
  local_24 = 0;
  FUN_00451340(local_2c,&local_18.y);
  uVar5 = FUN_004441e0(pcVar4,local_2c);
  FUN_00434820(local_2c);
  local_8 = 0xffffffff;
  if ((char)uVar5 == '\0') {
    local_18.y = 0x48da3c;
    local_8 = 1;
    local_2c[0] = '\0';
    local_24 = 0;
    FUN_00451340(local_2c,&local_18.y);
    uVar5 = FUN_004441e0(pcVar4,local_2c);
    FUN_00434820(local_2c);
    local_8 = 0xffffffff;
    if ((char)uVar5 == '\0') {
      pcVar7 = (char *)FUN_00440e70(pcVar4,(uint *)&DAT_0048d65c);
      FUN_004536b0(pcVar7,(uint *)&local_18.y);
      pcVar7 = (char *)local_18.y;
      pcVar4 = (char *)FUN_00440e70(pcVar4,(uint *)&DAT_0048d660);
      FUN_004536b0(pcVar4,(uint *)&local_18.y);
    }
    else {
      GetCursorPos(&local_18);
      pcVar7 = (char *)local_18.x;
    }
    local_24 = CONCAT44(local_18.y,pcVar7);
    pt.y = local_18.y;
    pt.x = (LONG)pcVar7;
    pHVar6 = MonitorFromPoint(pt,2);
  }
  else {
    dwFlags = 2;
    hwnd = GetForegroundWindow();
    pHVar6 = MonitorFromWindow(hwnd,dwFlags);
  }
  local_30 = 0xf;
  local_34 = 0;
  local_44[0] = (void *)((uint)local_44[0] & 0xffffff00);
  FUN_0043ace0(local_44,(uint *)"relat",5);
  local_8 = 2;
  pcVar4 = (char *)FUN_00440e70(param_2,(uint *)"level");
  FUN_004536b0(pcVar4,(uint *)&local_18.y);
  cVar3 = FUN_00441100(param_2,local_44);
  uVar5 = FUN_00410230(pHVar6,(byte)local_18.y,cVar3);
  uVar1 = local_24;
  local_24 = CONCAT71(local_24._1_7_,(char)uVar5);
  uVar2 = local_24;
  *(undefined8 *)(param_1 + 8) = 0;
  *(undefined4 *)(param_1 + 8) = (undefined4)local_24;
  local_24._4_4_ = SUB84(uVar1,4);
  *param_1 = 4;
  *(undefined4 *)(param_1 + 0xc) = local_24._4_4_;
  if (0xf < local_30) {
    local_24 = uVar2;
    FUN_00402430(local_44[0],local_30 + 1,1);
  }
  ExceptionList = local_10;
  return param_1;
}


