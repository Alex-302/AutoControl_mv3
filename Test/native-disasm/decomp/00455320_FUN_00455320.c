// FUN_00455320 @ 00455320 size=99 callers=1

void __fastcall FUN_00455320(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_0048e7d0;
  if ((uint *)param_1[3] != (uint *)0x0) {
    FUN_00447db0((uint *)param_1[3],(uint *)param_1[4]);
    FUN_00402430((void *)param_1[3],(int)(param_1[5] - param_1[3]) / 0x1c,0x1c);
    param_1[3] = 0;
    param_1[4] = 0;
    param_1[5] = 0;
  }
  *param_1 = &PTR_FUN_0048ed18;
  return;
}


