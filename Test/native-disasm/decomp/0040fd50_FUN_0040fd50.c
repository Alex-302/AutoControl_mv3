// FUN_0040fd50 @ 0040fd50 size=237 callers=12

UINT_PTR __fastcall FUN_0040fd50(UINT param_1,int *param_2)

{
  int *piVar1;
  UINT_PTR UVar2;
  int local_64 [9];
  int *local_40;
  int local_3c [9];
  int *local_18;
  int *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0047a620;
  local_10 = ExceptionList;
  local_14 = local_3c;
  local_18 = (int *)0x0;
  local_8 = 0;
  piVar1 = (int *)param_2[9];
  ExceptionList = &local_10;
  if (piVar1 != (int *)0x0) {
    ExceptionList = &local_10;
    if (piVar1 == param_2) {
      ExceptionList = &local_10;
      local_18 = (int *)(**(code **)(*piVar1 + 4))(local_3c);
      piVar1 = (int *)param_2[9];
      if (piVar1 == (int *)0x0) goto LAB_0040fdbd;
      (**(code **)(*piVar1 + 0x10))(piVar1 != param_2);
      piVar1 = local_18;
    }
    local_18 = piVar1;
    param_2[9] = 0;
  }
LAB_0040fdbd:
  local_40 = (int *)0x0;
  local_8 = 2;
  FUN_0044f250(local_64,local_3c);
  if (local_18 != (int *)0x0) {
    (**(code **)(*local_18 + 0x10))(local_18 != local_3c);
    local_18 = (int *)0x0;
  }
  local_8 = 3;
  UVar2 = FUN_0040fca0(param_1,local_64);
  if (local_40 != (int *)0x0) {
    (**(code **)(*local_40 + 0x10))(local_40 != local_64);
  }
  ExceptionList = local_10;
  return UVar2;
}


