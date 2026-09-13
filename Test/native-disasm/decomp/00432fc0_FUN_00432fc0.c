// FUN_00432fc0 @ 00432fc0 size=83 callers=3

void __fastcall FUN_00432fc0(int *param_1)

{
  if ((uint *)*param_1 != (uint *)0x0) {
    FUN_00447e30((uint *)*param_1,(uint *)param_1[1]);
    FUN_00402430((void *)*param_1,(param_1[2] - *param_1) / 0x1c,0x1c);
    *param_1 = 0;
    param_1[1] = 0;
    param_1[2] = 0;
  }
  return;
}


