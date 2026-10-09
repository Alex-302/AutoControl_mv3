// FUN_0040da40 @ 0040da40 size=113 callers=5

void __fastcall FUN_0040da40(int param_1)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)(param_1 + 0x1c);
  if (0xf < *(uint *)(param_1 + 0x30)) {
    FUN_00402430((void *)*puVar1,*(uint *)(param_1 + 0x30) + 1,1);
  }
  *(undefined4 *)(param_1 + 0x30) = 0xf;
  *(undefined4 *)(param_1 + 0x2c) = 0;
  if (0xf < *(uint *)(param_1 + 0x30)) {
    puVar1 = (undefined4 *)*puVar1;
  }
  *(undefined1 *)puVar1 = 0;
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


