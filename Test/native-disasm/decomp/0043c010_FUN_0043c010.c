// FUN_0043c010 @ 0043c010 size=229 callers=3

void __fastcall FUN_0043c010(undefined4 *param_1)

{
  void *pvVar1;
  
  if ((int *)param_1[0xb] != (int *)0x0) {
    FUN_00447eb0((int *)param_1[0xb],(int *)param_1[0xc]);
    FUN_00402430((void *)param_1[0xb],(param_1[0xd] - (int)param_1[0xb]) / 0x18,0x18);
    param_1[0xb] = 0;
    param_1[0xc] = 0;
    param_1[0xd] = 0;
  }
  pvVar1 = (void *)param_1[6];
  if (pvVar1 != (void *)0x0) {
    FUN_00402430(pvVar1,param_1[8] - (int)pvVar1 >> 2,4);
    param_1[6] = 0;
    param_1[7] = 0;
    param_1[8] = 0;
  }
  FUN_0043eb70(param_1 + 4);
  FID_conflict__free((void *)param_1[4]);
  if ((uint *)*param_1 != (uint *)0x0) {
    FUN_00447f50((uint *)*param_1,(uint *)param_1[1]);
    FUN_00402430((void *)*param_1,(param_1[2] - (int)*param_1) / 0x24,0x24);
    *param_1 = 0;
    param_1[1] = 0;
    param_1[2] = 0;
  }
  return;
}


