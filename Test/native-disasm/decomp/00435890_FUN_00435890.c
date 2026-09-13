// FUN_00435890 @ 00435890 size=60 callers=1

void __fastcall FUN_00435890(int param_1)

{
  if (0xf < *(uint *)(param_1 + 0x60)) {
    FUN_00402430(*(void **)(param_1 + 0x4c),*(uint *)(param_1 + 0x60) + 1,1);
  }
  *(undefined4 *)(param_1 + 0x60) = 0xf;
  *(undefined4 *)(param_1 + 0x5c) = 0;
  if (0xf < *(uint *)(param_1 + 0x60)) {
    **(undefined1 **)(param_1 + 0x4c) = 0;
    return;
  }
  *(undefined1 *)(param_1 + 0x4c) = 0;
  return;
}


