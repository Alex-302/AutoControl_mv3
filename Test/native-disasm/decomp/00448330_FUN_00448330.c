// FUN_00448330 @ 00448330 size=101 callers=19

void __fastcall FUN_00448330(int param_1)

{
  void *pvVar1;
  
  pvVar1 = *(void **)(param_1 + 0x14);
  if (pvVar1 != (void *)0x0) {
    FUN_00402430(pvVar1,*(int *)(param_1 + 0x1c) - (int)pvVar1 >> 3,8);
    *(undefined4 *)(param_1 + 0x14) = 0;
    *(undefined4 *)(param_1 + 0x18) = 0;
    *(undefined4 *)(param_1 + 0x1c) = 0;
  }
  pvVar1 = *(void **)(param_1 + 4);
  if (pvVar1 != (void *)0x0) {
    FUN_00402430(pvVar1,*(int *)(param_1 + 0xc) - (int)pvVar1 >> 2,4);
    *(undefined4 *)(param_1 + 4) = 0;
    *(undefined4 *)(param_1 + 8) = 0;
    *(undefined4 *)(param_1 + 0xc) = 0;
  }
  return;
}


