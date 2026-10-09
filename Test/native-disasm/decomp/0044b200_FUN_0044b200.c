// FUN_0044b200 @ 0044b200 size=138 callers=3

void __fastcall FUN_0044b200(undefined4 *param_1)

{
  void *pvVar1;
  
  pvVar1 = (void *)param_1[0xe];
  if (pvVar1 != (void *)0x0) {
    FUN_00402430(pvVar1,param_1[0x10] - (int)pvVar1,1);
    param_1[0xe] = 0;
    param_1[0xf] = 0;
    param_1[0x10] = 0;
  }
  pvVar1 = (void *)param_1[7];
  if (pvVar1 != (void *)0x0) {
    FUN_00402430(pvVar1,param_1[9] - (int)pvVar1,1);
    param_1[7] = 0;
    param_1[8] = 0;
    param_1[9] = 0;
  }
  pvVar1 = (void *)*param_1;
  if (pvVar1 != (void *)0x0) {
    FUN_00402430(pvVar1,param_1[2] - (int)pvVar1,1);
    *param_1 = 0;
    param_1[1] = 0;
    param_1[2] = 0;
  }
  return;
}


