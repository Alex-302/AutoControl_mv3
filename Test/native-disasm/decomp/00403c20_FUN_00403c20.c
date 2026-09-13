// FUN_00403c20 @ 00403c20 size=220 callers=11

void __fastcall FUN_00403c20(undefined4 *param_1)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + 0x12;
  if (7 < (uint)param_1[0x17]) {
    FUN_00402430((void *)*puVar1,param_1[0x17] + 1,2);
  }
  param_1[0x17] = 7;
  param_1[0x16] = 0;
  if (7 < (uint)param_1[0x17]) {
    puVar1 = (undefined4 *)*puVar1;
  }
  *(undefined2 *)puVar1 = 0;
  puVar1 = param_1 + 0xc;
  if (7 < (uint)param_1[0x11]) {
    FUN_00402430((void *)*puVar1,param_1[0x11] + 1,2);
  }
  param_1[0x11] = 7;
  param_1[0x10] = 0;
  if (7 < (uint)param_1[0x11]) {
    puVar1 = (undefined4 *)*puVar1;
  }
  *(undefined2 *)puVar1 = 0;
  puVar1 = param_1 + 6;
  if (7 < (uint)param_1[0xb]) {
    FUN_00402430((void *)*puVar1,param_1[0xb] + 1,2);
  }
  param_1[0xb] = 7;
  param_1[10] = 0;
  if (7 < (uint)param_1[0xb]) {
    puVar1 = (undefined4 *)*puVar1;
  }
  *(undefined2 *)puVar1 = 0;
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


