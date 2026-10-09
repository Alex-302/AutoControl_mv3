// FUN_004333f0 @ 004333f0 size=81 callers=1

void __fastcall FUN_004333f0(int *param_1)

{
  if ((int *)*param_1 != (int *)0x0) {
    FUN_00447eb0((int *)*param_1,(int *)param_1[1]);
    FUN_00402430((void *)*param_1,(param_1[2] - *param_1) / 0x18,0x18);
    *param_1 = 0;
    param_1[1] = 0;
    param_1[2] = 0;
  }
  return;
}


