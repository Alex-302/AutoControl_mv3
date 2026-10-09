// FUN_004297a0 @ 004297a0 size=743 callers=1

undefined1 * __cdecl FUN_004297a0(undefined1 *param_1,HWND param_2)

{
  HWND pHVar1;
  char cVar2;
  int iVar3;
  char *pcVar4;
  void *pvVar5;
  undefined1 *extraout_ECX;
  ulonglong uVar6;
  undefined4 *in_stack_ffffff08;
  uint uVar7;
  undefined4 local_d0 [24];
  undefined4 local_70;
  undefined **local_6c;
  HWND local_68;
  uint local_64;
  HWND pHStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined ***local_48;
  uint local_40;
  int *local_3c;
  int *local_38;
  void *local_34;
  void *local_30;
  uint local_2c;
  HWND pHStack_28;
  undefined4 uStack_24;
  uint uStack_20;
  uint local_1c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047c929;
  local_10 = ExceptionList;
  local_70 = 0;
  uStack_20 = 0xf;
  uStack_24 = 0;
  local_34 = (void *)((uint)local_34 & 0xffffff00);
  ExceptionList = &local_10;
  FUN_0043ace0(&local_34,(uint *)&DAT_0048d814,3);
  pHVar1 = param_2;
  if ((char)param_2->unused == '\x01') {
    FUN_004437f0((void *)param_2[2].unused,(int *)&local_3c,(byte *)&local_34);
    iVar3 = FUN_00447a70(local_3c,local_38);
  }
  else {
    iVar3 = 0;
  }
  if (0xf < uStack_20) {
    FUN_00402430(local_34,uStack_20 + 1,1);
  }
  if (iVar3 == 0) {
    *param_1 = 0;
    *(undefined8 *)(param_1 + 8) = 0;
    FUN_00450f50(param_1,0);
    ExceptionList = local_10;
    return extraout_ECX;
  }
  pcVar4 = (char *)FUN_00440e70(pHVar1,(uint *)&DAT_0048d814);
  FUN_004536b0(pcVar4,(uint *)&param_2);
  pcVar4 = (char *)FUN_00440e70(pHVar1,(uint *)"tabId");
  FUN_004536b0(pcVar4,&local_40);
  local_1c = 0xf;
  uStack_20 = 0;
  local_30 = (void *)((uint)local_30 & 0xffffff00);
  FUN_0043ace0(&local_30,(uint *)&DAT_0048da08,4);
  local_8 = 0;
  uVar6 = FUN_004411d0(pHVar1,&local_30);
  local_38 = (int *)(uVar6 >> 0x20);
  local_8 = 0xffffffff;
  if (0xf < local_1c) {
    FUN_00402430(local_30,local_1c + 1,1);
  }
  local_1c = 0xf;
  uStack_20 = 0;
  local_30 = (void *)((uint)local_30 & 0xffffff00);
  FUN_0043ace0(&local_30,(uint *)"popup",5);
  local_8 = 1;
  cVar2 = FUN_00441100(pHVar1,&local_30);
  local_8 = 0xffffffff;
  if (0xf < local_1c) {
    FUN_00402430(local_30,local_1c + 1,1);
  }
  pHVar1 = param_2;
  if (DAT_004a2460 == 0) {
    DAT_004a2460 = GetWindowThreadProcessId(param_2,(LPDWORD)&DAT_004a2454);
    if (DAT_004a2446 == '\0') {
      uVar7 = 0x7fffffff;
      local_34 = DAT_004a2454;
      FUN_00404a40((LPWSTR)&stack0xffffff08,(DWORD)DAT_004a2454);
      pvVar5 = FUN_00403a70(local_d0,in_stack_ffffff08);
      local_8 = 2;
      FUN_00404580((LPSTR)&local_30,(LPCWSTR)((int)pvVar5 + 0x18),uVar7);
      FUN_00403c20(local_d0);
      local_8 = 3;
      FUN_0040d060((DWORD *)&local_34);
      FUN_00407070((int)&local_34);
    }
  }
  local_1c = CONCAT31(local_1c._1_3_,cVar2);
  local_64 = local_1c;
  local_48 = &local_6c;
  local_6c = &PTR_LAB_0048ed50;
  local_68 = pHVar1;
  local_8 = 4;
  FUN_0040f6b0(DAT_004a2458,(int *)local_48,0);
  if (local_48 != (undefined ***)0x0) {
    (*(code *)(*local_48)[4])();
  }
  if (local_40 != 0) {
    local_2c = local_40;
    uStack_20 = (uint)local_38;
    local_48 = &local_6c;
    pHStack_28 = pHVar1;
    local_6c = &PTR_LAB_0048f054;
    local_64 = local_40;
    pHStack_60 = pHVar1;
    uStack_58 = local_38;
    local_8 = 5;
    uStack_5c = (int)uVar6;
    uStack_24 = (int)uVar6;
    FUN_0040f6b0(DAT_004a23dc,(int *)local_48,0);
    if (local_48 != (undefined ***)0x0) {
      (*(code *)(*local_48)[4])();
    }
  }
  local_8 = 6;
  *param_1 = 0;
  FUN_004381d0(param_1 + 8,'\0');
  ExceptionList = local_10;
  return param_1;
}


