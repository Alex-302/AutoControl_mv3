// FUN_00437230 @ 00437230 size=93 callers=2

int * FUN_00437230(int *param_1,int *param_2,int *param_3)

{
  int *piVar1;
  int local_4;
  
  if ((param_2 == (int *)*DAT_004a27d4) && (param_3 == DAT_004a27d4)) {
    FUN_0043c900();
    *param_1 = *DAT_004a27d4;
    return param_1;
  }
  while (param_2 != param_3) {
    piVar1 = (int *)*param_2;
    FUN_00431c40(&DAT_004a27d0,&local_4,param_2);
    param_2 = piVar1;
  }
  *param_1 = (int)param_2;
  return param_1;
}


