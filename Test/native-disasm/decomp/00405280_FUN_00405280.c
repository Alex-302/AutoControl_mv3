// FUN_00405280 @ 00405280 size=60 callers=3

void __fastcall FUN_00405280(int param_1)

{
  if (0xf < *(uint *)(param_1 + 0x24)) {
    FUN_00402430(*(void **)(param_1 + 0x10),*(uint *)(param_1 + 0x24) + 1,1);
  }
  *(undefined4 *)(param_1 + 0x24) = 0xf;
  *(undefined4 *)(param_1 + 0x20) = 0;
  if (0xf < *(uint *)(param_1 + 0x24)) {
    **(undefined1 **)(param_1 + 0x10) = 0;
    return;
  }
  *(undefined1 *)(param_1 + 0x10) = 0;
  return;
}


