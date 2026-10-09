// FUN_00404670 @ 00404670 size=287 callers=11

int * __fastcall FUN_00404670(int *param_1,HWND param_2)

{
  int *piVar1;
  uint uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_004792d9;
  local_10 = ExceptionList;
  local_8 = 0;
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
  if ((uint)param_1[5] < 0x32) {
    FUN_0043f5f0(param_1,0x32);
  }
  piVar1 = param_1;
  if (0xf < (uint)param_1[5]) {
    piVar1 = (int *)*param_1;
  }
  _memset(piVar1,0,0x32);
  param_1[4] = 0x32;
  piVar1 = param_1;
  if (0xf < (uint)param_1[5]) {
    piVar1 = (int *)*param_1;
  }
  *(undefined1 *)((int)piVar1 + 0x32) = 0;
  local_8 = 0;
  piVar1 = param_1;
  if (0xf < (uint)param_1[5]) {
    piVar1 = (int *)*param_1;
  }
  uVar2 = GetClassNameA(param_2,(LPSTR)piVar1,0x32);
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


