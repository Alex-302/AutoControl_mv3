// FUN_00419ca0 @ 00419ca0 size=74 callers=4

void __fastcall FUN_00419ca0(undefined4 *param_1)

{
  if ((undefined4 *)param_1[6] != (undefined4 *)0x0) {
    (*(code *)**(undefined4 **)param_1[6])(1);
  }
  if (7 < (uint)param_1[5]) {
    FUN_00402430((void *)*param_1,param_1[5] + 1,2);
  }
  param_1[5] = 7;
  param_1[4] = 0;
  if (7 < (uint)param_1[5]) {
    *(undefined2 *)*param_1 = 0;
    return;
  }
  *(undefined2 *)param_1 = 0;
  return;
}


