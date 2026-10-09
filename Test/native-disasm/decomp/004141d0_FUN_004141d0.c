// FUN_004141d0 @ 004141d0 size=390 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int * __fastcall FUN_004141d0(int *param_1,HWND param_2)

{
  HMONITOR pHVar1;
  int *piVar2;
  uint uVar3;
  float10 fVar4;
  float in_XMM0_Da;
  float fVar5;
  int *local_24;
  uint local_20;
  float local_1c;
  int *local_18;
  int *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047aca9;
  local_10 = ExceptionList;
  local_20 = 0;
  ExceptionList = &local_10;
  local_24 = param_1;
  if (param_2 != DAT_004a2430) {
    DAT_004a2430 = param_2;
    ExceptionList = &local_10;
    pHVar1 = MonitorFromWindow(param_2,2);
    FUN_00406610(pHVar1);
    DAT_0049d9e0 = in_XMM0_Da;
  }
  fVar5 = DAT_0049d9e0;
  fVar4 = roundf(DAT_0049d9e0);
  local_18 = (int *)(float)fVar4;
  if (param_2 != DAT_004a2430) {
    DAT_004a2430 = param_2;
    pHVar1 = MonitorFromWindow(param_2,2);
    FUN_00406610(pHVar1);
    DAT_0049d9e0 = fVar5;
  }
  fVar4 = roundf(DAT_0049d9e0 * _DAT_0048f26c);
  local_1c = (float)fVar4;
  FUN_0040b700(&local_14,param_2,(int)fVar4,(int)(float)local_18,'\0');
  local_8 = 0;
  if (DAT_004a23a4 < 0x5c) {
    piVar2 = FUN_0040b930(&local_18,(int *)&local_14,5);
    uVar3 = 2;
  }
  else {
    piVar2 = FUN_0040bb70(&local_24,&local_14,0x10,1,0x32);
    uVar3 = 1;
  }
  *param_1 = 0;
  *param_1 = *piVar2;
  *piVar2 = 0;
  if ((uVar3 & 2) != 0) {
    uVar3 = uVar3 & 0xfffffffd | 4;
    local_8 = 3;
    local_20 = uVar3;
    if (local_18 != (int *)0x0) {
      (**(code **)(*local_18 + 8))(local_18);
    }
  }
  if (((uVar3 & 1) != 0) && (local_8 = 4, local_24 != (int *)0x0)) {
    (**(code **)(*local_24 + 8))(local_24);
  }
  local_8 = 5;
  if (local_14 != (int *)0x0) {
    (**(code **)(*local_14 + 8))(local_14);
  }
  ExceptionList = local_10;
  return param_1;
}


