// FUN_00427e50 @ 00427e50 size=246 callers=2

void __fastcall FUN_00427e50(int param_1)

{
  HRESULT HVar1;
  int *piVar2;
  int iVar3;
  int *local_1c;
  int *local_18;
  int *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047c6a2;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  HVar1 = CoInitializeEx((LPVOID)0x0,2);
  local_8._0_1_ = 0;
  local_8._1_3_ = 0;
  local_1c = (int *)0x0;
  piVar2 = (int *)CoCreateInstance((IID *)&DAT_0049da4c,(LPUNKNOWN)0x0,1,(IID *)&DAT_0049da14,
                                   &local_1c);
  if (piVar2 == (int *)0x0) {
    local_8._0_1_ = 3;
    local_18 = piVar2;
    piVar2 = (int *)(**(code **)(*local_1c + 0x10))(local_1c,0,0,&local_18);
    if (piVar2 == (int *)0x0) {
      local_8 = CONCAT31(local_8._1_3_,6);
      local_14 = piVar2;
      iVar3 = (**(code **)(*local_18 + 0xc))(local_18,&DAT_0049da34,1,0,&local_14);
      if (iVar3 == 0) {
        if (*(int **)(param_1 + 0x24) == (int *)0x0) {
                    /* WARNING: Subroutine does not return */
          FUN_00458e87();
        }
        (**(code **)(**(int **)(param_1 + 0x24) + 8))(local_14);
      }
      local_8._0_1_ = 10;
      if (local_14 != (int *)0x0) {
        (**(code **)(*local_14 + 8))(local_14);
      }
    }
    local_8._0_1_ = 0xb;
    if (local_18 != (int *)0x0) {
      (**(code **)(*local_18 + 8))(local_18);
    }
  }
  local_8 = CONCAT31(local_8._1_3_,0xc);
  if (local_1c != (int *)0x0) {
    (**(code **)(*local_1c + 8))(local_1c);
  }
  if (-1 < HVar1) {
    CoUninitialize();
  }
  ExceptionList = local_10;
  return;
}


