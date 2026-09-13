// FUN_00432b50 @ 00432b50 size=69 callers=12

void __fastcall FUN_00432b50(undefined4 *param_1)

{
  void *pvVar1;
  
  pvVar1 = (void *)*param_1;
  if (pvVar1 != (void *)0x0) {
    FUN_00402430(pvVar1,(param_1[2] - (int)pvVar1) / 0x1c,0x1c);
    *param_1 = 0;
    param_1[1] = 0;
    param_1[2] = 0;
  }
  return;
}


