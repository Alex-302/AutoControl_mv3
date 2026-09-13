// FUN_004369f0 @ 004369f0 size=163 callers=1

int * FUN_004369f0(int *param_1,int *param_2,int *param_3)

{
  int *piVar1;
  void **ppvVar2;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004791a6;
  local_10 = ExceptionList;
  ppvVar2 = &local_10;
  if ((param_2 == (int *)*DAT_004a2f94) && (param_3 == DAT_004a2f94)) {
    local_8 = 0;
    ExceptionList = &local_10;
    FUN_0043e700((int *)&DAT_004a2f94);
    FUN_00435e50(&DAT_004a2f90,8);
    *param_1 = *DAT_004a2f94;
    ExceptionList = local_10;
    return param_1;
  }
  while (ExceptionList = ppvVar2, param_2 != param_3) {
    piVar1 = (int *)*param_2;
    FUN_0043c670(&DAT_004a2f90,&local_14,param_2);
    param_2 = piVar1;
    ppvVar2 = ExceptionList;
  }
  *param_1 = (int)param_2;
  ExceptionList = local_10;
  return param_1;
}


