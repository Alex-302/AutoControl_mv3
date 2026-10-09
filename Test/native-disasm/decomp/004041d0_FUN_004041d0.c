// FUN_004041d0 @ 004041d0 size=68 callers=5

void __fastcall FUN_004041d0(int param_1)

{
  void *pvVar1;
  
  pvVar1 = *(void **)(param_1 + 8);
  if (pvVar1 != (void *)0x0) {
    FUN_00402430(pvVar1,(*(int *)(param_1 + 0x10) - (int)pvVar1) / 0xc,0xc);
    *(undefined4 *)(param_1 + 8) = 0;
    *(undefined4 *)(param_1 + 0xc) = 0;
    *(undefined4 *)(param_1 + 0x10) = 0;
  }
  return;
}


