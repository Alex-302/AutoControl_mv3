// FUN_004334e0 @ 004334e0 size=81 callers=1

void __fastcall FUN_004334e0(int *param_1)

{
  if ((uint *)*param_1 != (uint *)0x0) {
    FUN_00447f50((uint *)*param_1,(uint *)param_1[1]);
    FUN_00402430((void *)*param_1,(param_1[2] - *param_1) / 0x24,0x24);
    *param_1 = 0;
    param_1[1] = 0;
    param_1[2] = 0;
  }
  return;
}


