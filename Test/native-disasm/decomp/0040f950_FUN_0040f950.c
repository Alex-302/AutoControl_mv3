// FUN_0040f950 @ 0040f950 size=82 callers=2

void __fastcall FUN_0040f950(int *param_1,HANDLE param_2)

{
  int *piVar1;
  void *pvStack_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047a5ee;
  pvStack_10 = ExceptionList;
  if ((char)param_1[10] == '\0') {
    ExceptionList = &pvStack_10;
    if ((param_2 != (HANDLE)0x0) && (ExceptionList = &pvStack_10, (char)param_1[10] != '\0')) {
      ExceptionList = &pvStack_10;
      SetEvent(param_2);
    }
    piVar1 = (int *)param_1[9];
    if (piVar1 != (int *)0x0) {
      (**(code **)(*piVar1 + 0x10))(piVar1 != param_1);
      param_1[9] = 0;
    }
    FUN_0045a6a4(param_1);
    ExceptionList = pvStack_10;
    return;
  }
  local_8 = 0;
  if ((int *)param_1[9] == (int *)0x0) {
    ExceptionList = &pvStack_10;
                    /* WARNING: Subroutine does not return */
    FUN_00458e87();
  }
  ExceptionList = &pvStack_10;
  (**(code **)(*(int *)param_1[9] + 8))();
  FUN_0040fa66();
  return;
}


