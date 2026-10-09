// FUN_00443bb0 @ 00443bb0 size=53 callers=1

void __fastcall FUN_00443bb0(int param_1)

{
  void *pvVar1;
  
  pvVar1 = *(void **)(param_1 + 0x14);
  if (pvVar1 != (void *)0x0) {
    FUN_00402430(pvVar1,*(int *)(param_1 + 0x1c) - (int)pvVar1 >> 2,4);
    *(undefined4 *)(param_1 + 0x14) = 0;
    *(undefined4 *)(param_1 + 0x18) = 0;
    *(undefined4 *)(param_1 + 0x1c) = 0;
  }
  return;
}


