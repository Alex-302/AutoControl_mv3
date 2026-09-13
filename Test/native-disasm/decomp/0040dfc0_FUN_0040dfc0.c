// FUN_0040dfc0 @ 0040dfc0 size=106 callers=2

int * __fastcall FUN_0040dfc0(int *param_1,HWND param_2)

{
  int *piVar1;
  int *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047a2de;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_14 = param_1;
  piVar1 = FUN_0040dec0((int *)&local_14,param_2);
  local_8 = 0;
  FUN_0040b930(param_1,piVar1,5);
  local_8 = 1;
  if (local_14 != (int *)0x0) {
    (**(code **)(*local_14 + 8))(local_14);
  }
  ExceptionList = local_10;
  return param_1;
}


