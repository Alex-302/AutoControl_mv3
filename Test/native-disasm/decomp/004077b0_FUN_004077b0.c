// FUN_004077b0 @ 004077b0 size=330 callers=2

int * __fastcall FUN_004077b0(int *param_1,HANDLE param_2)

{
  int *piVar1;
  uint uVar2;
  undefined4 extraout_ECX;
  uint local_1c [2];
  byte local_14 [4];
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00479369;
  local_10 = ExceptionList;
  local_8 = 0;
  local_1c[1] = 0;
  ExceptionList = &local_10;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[5] = 0xf;
  param_1[4] = 0;
  piVar1 = param_1;
  if (0xf < (uint)param_1[5]) {
    piVar1 = (int *)*param_1;
  }
  *(undefined1 *)piVar1 = 0;
  if ((uint)param_1[5] < 200) {
    FUN_0043f5f0(param_1,200);
  }
  piVar1 = param_1;
  if (0xf < (uint)param_1[5]) {
    piVar1 = (int *)*param_1;
  }
  _memset(piVar1,0,200);
  param_1[4] = 200;
  piVar1 = param_1;
  if (0xf < (uint)param_1[5]) {
    piVar1 = (int *)*param_1;
  }
  *(undefined1 *)(piVar1 + 0x32) = 0;
  local_8 = 0;
  local_1c[0] = param_1[4];
  local_1c[1] = 1;
  piVar1 = param_1;
  if (0xf < (uint)param_1[5]) {
    piVar1 = (int *)*param_1;
  }
  GetRawInputDeviceInfoA(param_2,0x20000007,piVar1,local_1c);
  local_14[0] = 0;
  uVar2 = FUN_0043ab50(param_1,local_14,extraout_ECX,1);
  if ((uint)param_1[4] < uVar2) {
    FUN_0043aef0(param_1,uVar2 - param_1[4],'\0');
    ExceptionList = local_10;
    return param_1;
  }
  param_1[4] = uVar2;
  if ((uint)param_1[5] < 0x10) {
    *(undefined1 *)((int)param_1 + uVar2) = 0;
    ExceptionList = local_10;
    return param_1;
  }
  *(undefined1 *)(*param_1 + uVar2) = 0;
  ExceptionList = local_10;
  return param_1;
}


