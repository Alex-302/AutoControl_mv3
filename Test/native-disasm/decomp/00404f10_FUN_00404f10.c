// FUN_00404f10 @ 00404f10 size=302 callers=1

int * __fastcall FUN_00404f10(int *param_1,HANDLE param_2)

{
  uint uVar1;
  int *piVar2;
  BOOL BVar3;
  uint uVar4;
  DWORD local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00479369;
  local_10 = ExceptionList;
  local_8 = 0;
  uVar4 = 0;
  ExceptionList = &local_10;
  param_1[5] = 0xf;
  local_14 = 0;
  param_1[4] = 0;
  piVar2 = param_1;
  if (0xf < (uint)param_1[5]) {
    piVar2 = (int *)*param_1;
  }
  *(undefined1 *)piVar2 = 0;
  FUN_0043ac10(param_1,100,'\0');
  local_8 = 0;
  while( true ) {
    piVar2 = param_1;
    if (0xf < (uint)param_1[5]) {
      piVar2 = (int *)*param_1;
    }
    BVar3 = ReadFile(param_2,(LPVOID)((int)piVar2 + uVar4),param_1[4] - uVar4,&local_14,
                     (LPOVERLAPPED)0x0);
    if ((BVar3 == 0) || (local_14 == 0)) break;
    uVar4 = uVar4 + local_14;
    uVar1 = uVar4 + 100;
    if ((uint)param_1[4] < uVar1) {
      FUN_0043aef0(param_1,uVar1 - param_1[4],'\0');
    }
    else {
      param_1[4] = uVar1;
      if ((uint)param_1[5] < 0x10) {
        *(undefined1 *)((int)param_1 + uVar1) = 0;
      }
      else {
        *(undefined1 *)(*param_1 + uVar1) = 0;
      }
    }
  }
  if ((uint)param_1[4] < uVar4) {
    FUN_0043aef0(param_1,uVar4 - param_1[4],'\0');
    ExceptionList = local_10;
    return param_1;
  }
  param_1[4] = uVar4;
  if ((uint)param_1[5] < 0x10) {
    *(undefined1 *)((int)param_1 + uVar4) = 0;
    ExceptionList = local_10;
    return param_1;
  }
  *(undefined1 *)(*param_1 + uVar4) = 0;
  ExceptionList = local_10;
  return param_1;
}


