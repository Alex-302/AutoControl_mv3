// FUN_00435170 @ 00435170 size=61 callers=91

void __fastcall FUN_00435170(undefined4 *param_1)

{
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


