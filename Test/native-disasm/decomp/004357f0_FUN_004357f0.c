// FUN_004357f0 @ 004357f0 size=65 callers=2

void __fastcall FUN_004357f0(undefined4 *param_1)

{
  FUN_00434820((char *)(param_1 + 6));
  if (0xf < (uint)param_1[5]) {
    FUN_00402430((void *)*param_1,param_1[5] + 1,1);
  }
  param_1[5] = 0xf;
  param_1[4] = 0;
  if (0xf < (uint)param_1[5]) {
    *(undefined1 *)*param_1 = 0;
    return;
  }
  *(undefined1 *)param_1 = 0;
  return;
}


