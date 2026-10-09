// FUN_004290e0 @ 004290e0 size=187 callers=3

void __fastcall FUN_004290e0(undefined4 *param_1)

{
  void *pvVar1;
  
  pvVar1 = (void *)param_1[0xf];
  if (pvVar1 != (void *)0x0) {
    FUN_00402430(pvVar1,param_1[0x11] - (int)pvVar1 >> 2,4);
    param_1[0xf] = 0;
    param_1[0x10] = 0;
    param_1[0x11] = 0;
  }
  FUN_0043e550(param_1 + 0xd);
  FID_conflict__free((void *)param_1[0xd]);
  pvVar1 = (void *)param_1[7];
  if (pvVar1 != (void *)0x0) {
    FUN_00402430(pvVar1,param_1[9] - (int)pvVar1 >> 2,4);
    param_1[7] = 0;
    param_1[8] = 0;
    param_1[9] = 0;
  }
  FUN_0043edd0(param_1 + 5);
  FID_conflict__free((void *)param_1[5]);
  pvVar1 = (void *)*param_1;
  if (pvVar1 != (void *)0x0) {
    FUN_00402430(pvVar1,param_1[2] - (int)pvVar1 >> 2,4);
    *param_1 = 0;
    param_1[1] = 0;
    param_1[2] = 0;
  }
  return;
}


