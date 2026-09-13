// FUN_004033e0 @ 004033e0 size=46 callers=8

void __fastcall FUN_004033e0(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  
  while ((param_1 != param_2 && (param_1 != (undefined4 *)0x0))) {
    puVar1 = (undefined4 *)param_1[3];
    param_1[3] = 0;
    (**(code **)*param_1)(1);
    param_1 = puVar1;
  }
  return;
}


