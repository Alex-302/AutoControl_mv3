// FUN_00404910 @ 00404910 size=301 callers=3

int * __fastcall FUN_00404910(int *param_1)

{
  uint uVar1;
  uint uVar2;
  int *piVar3;
  LPWSTR lpFilename;
  DWORD DVar4;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00479309;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[5] = 7;
  param_1[4] = 0;
  piVar3 = param_1;
  if (7 < (uint)param_1[5]) {
    piVar3 = (int *)*param_1;
  }
  *(undefined2 *)piVar3 = 0;
  param_1[4] = 0;
  piVar3 = param_1;
  if (7 < (uint)param_1[5]) {
    piVar3 = (int *)*param_1;
  }
  *(undefined2 *)piVar3 = 0;
  local_8 = 0;
  do {
    uVar2 = param_1[4];
    uVar1 = uVar2 + 100;
    if (uVar2 < uVar1) {
      FUN_0043a870(param_1,uVar1 - uVar2,0);
    }
    else {
      param_1[4] = uVar1;
      if ((uint)param_1[5] < 8) {
        *(undefined2 *)((int)param_1 + uVar1 * 2) = 0;
      }
      else {
        *(undefined2 *)(*param_1 + uVar1 * 2) = 0;
      }
    }
    DVar4 = param_1[4];
    lpFilename = FUN_00434ec0(param_1,0);
    DVar4 = GetModuleFileNameW((HMODULE)0x0,lpFilename,DVar4);
  } while ((DVar4 == 0) || (DVar4 == param_1[4]));
  if ((uint)param_1[4] < DVar4) {
    FUN_0043a870(param_1,DVar4 - param_1[4],0);
    ExceptionList = local_10;
    return param_1;
  }
  param_1[4] = DVar4;
  if ((uint)param_1[5] < 8) {
    *(undefined2 *)((int)param_1 + DVar4 * 2) = 0;
    ExceptionList = local_10;
    return param_1;
  }
  *(undefined2 *)(*param_1 + DVar4 * 2) = 0;
  ExceptionList = local_10;
  return param_1;
}


