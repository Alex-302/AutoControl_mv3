// FUN_004561a0 @ 004561a0 size=46 callers=1

void __fastcall FUN_004561a0(undefined8 *param_1,undefined8 *param_2,undefined8 *param_3)

{
  for (; param_1 != param_2; param_1 = (undefined8 *)((int)param_1 + 0xc)) {
    if (param_3 != (undefined8 *)0x0) {
      *param_3 = *param_1;
      *(undefined4 *)(param_3 + 1) = *(undefined4 *)(param_1 + 1);
    }
    param_3 = (undefined8 *)((int)param_3 + 0xc);
  }
  return;
}


