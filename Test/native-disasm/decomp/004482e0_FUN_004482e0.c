// FUN_004482e0 @ 004482e0 size=67 callers=1

void __fastcall FUN_004482e0(int param_1)

{
  void *pvVar1;
  
  pvVar1 = *(void **)(param_1 + 0x40);
  if (pvVar1 != (void *)0x0) {
    FUN_00402430(pvVar1,*(int *)(param_1 + 0x48) - (int)pvVar1 >> 3,8);
    *(undefined4 *)(param_1 + 0x40) = 0;
    *(undefined4 *)(param_1 + 0x44) = 0;
    *(undefined4 *)(param_1 + 0x48) = 0;
  }
  FUN_00448330(param_1 + 0x20);
  FUN_00448330(param_1);
  return;
}


