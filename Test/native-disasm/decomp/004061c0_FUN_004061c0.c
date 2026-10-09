// FUN_004061c0 @ 004061c0 size=57 callers=413

void __fastcall FUN_004061c0(undefined4 *param_1)

{
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


