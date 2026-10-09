// FUN_004335b0 @ 004335b0 size=50 callers=16

void __fastcall FUN_004335b0(undefined4 *param_1)

{
  void *pvVar1;
  
  pvVar1 = (void *)*param_1;
  if (pvVar1 != (void *)0x0) {
    FUN_00402430(pvVar1,param_1[2] - (int)pvVar1 >> 1,2);
    *param_1 = 0;
    param_1[1] = 0;
    param_1[2] = 0;
  }
  return;
}


