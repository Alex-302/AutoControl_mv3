// FUN_0040dec0 @ 0040dec0 size=254 callers=2

int * __fastcall FUN_0040dec0(int *param_1,HWND param_2)

{
  int iVar1;
  undefined4 *puVar2;
  int *local_1c;
  int *local_18;
  int *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047a2be;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_18 = param_1;
  FUN_0040dbc0(&local_18,param_2);
  local_8 = 0;
  FUN_0040bb70(&local_14,&local_18,0x3c,1,3);
  local_8._0_1_ = 1;
  if (local_14 == (int *)0x0) {
    if ((DAT_004a23c4 == '\0') || (iVar1 = 0x16, 0x56 < DAT_004a23a4)) {
      iVar1 = 0x10;
    }
    puVar2 = FUN_0040bb70(&local_1c,&local_18,iVar1,1,0x32);
    local_8._0_1_ = 2;
    if (local_14 != (int *)0x0) {
      (**(code **)(*local_14 + 8))(local_14);
    }
    local_14 = (int *)*puVar2;
    *puVar2 = 0;
    local_8._0_1_ = 3;
    if (local_1c != (int *)0x0) {
      (**(code **)(*local_1c + 8))(local_1c);
    }
  }
  local_8._0_1_ = 1;
  *param_1 = (int)local_14;
  if (local_14 != (int *)0x0) {
    (**(code **)(*local_14 + 4))(local_14);
  }
  local_8 = CONCAT31(local_8._1_3_,5);
  if (local_14 != (int *)0x0) {
    (**(code **)(*local_14 + 8))(local_14);
  }
  local_8 = 6;
  if (local_18 != (int *)0x0) {
    (**(code **)(*local_18 + 8))(local_18);
  }
  ExceptionList = local_10;
  return param_1;
}


