// FUN_0040b9e0 @ 0040b9e0 size=131 callers=7

undefined4 * __fastcall FUN_0040b9e0(undefined4 *param_1,int *param_2)

{
  int *piVar1;
  int iVar2;
  int *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00479e29;
  local_10 = ExceptionList;
  local_14 = (int *)0x0;
  ExceptionList = &local_10;
  *param_1 = 0;
  local_8 = 0;
  piVar1 = (int *)*param_2;
  if (piVar1 != (int *)0x0) {
    iVar2 = (**(code **)(*piVar1 + 0x1c))(piVar1,&local_14);
    if ((iVar2 == 0) && (local_14 != (int *)0x0)) {
      (**(code **)*local_14)(local_14,&DAT_0048ec70,param_1);
      (**(code **)(*local_14 + 8))(local_14);
    }
  }
  ExceptionList = local_10;
  return param_1;
}


