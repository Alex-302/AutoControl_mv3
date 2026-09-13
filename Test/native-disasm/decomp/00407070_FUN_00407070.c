// FUN_00407070 @ 00407070 size=60 callers=5

void __fastcall FUN_00407070(int param_1)

{
  if (0xf < *(uint *)(param_1 + 0x18)) {
    FUN_00402430(*(void **)(param_1 + 4),*(uint *)(param_1 + 0x18) + 1,1);
  }
  *(undefined4 *)(param_1 + 0x18) = 0xf;
  *(undefined4 *)(param_1 + 0x14) = 0;
  if (0xf < *(uint *)(param_1 + 0x18)) {
    **(undefined1 **)(param_1 + 4) = 0;
    return;
  }
  *(undefined1 *)(param_1 + 4) = 0;
  return;
}


