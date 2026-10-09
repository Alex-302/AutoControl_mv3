// FUN_00443b20 @ 00443b20 size=48 callers=2

void __fastcall FUN_00443b20(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = 0;
  uVar2 = (uint)((int)param_2 + (3 - (int)param_1)) >> 2;
  if (param_2 < param_1) {
    uVar2 = 0;
  }
  if (uVar2 != 0) {
    do {
      uVar1 = uVar1 + 1;
      *param_1 = *param_3;
      param_1 = param_1 + 1;
    } while (uVar1 != uVar2);
  }
  return;
}


