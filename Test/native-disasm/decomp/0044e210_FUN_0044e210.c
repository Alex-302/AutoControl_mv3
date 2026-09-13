// FUN_0044e210 @ 0044e210 size=53 callers=2

uint __fastcall FUN_0044e210(int param_1)

{
  uint uVar1;
  
  uVar1 = *(uint *)(*(int *)(param_1 + 4) + 4);
  if ((((uVar1 != 0x14) && (uVar1 != 8)) && (uVar1 != 0xd)) &&
     ((uVar1 != 2 ||
      (((uVar1 = *(uint *)(*(int *)(*(int *)(param_1 + 4) + 0x10) + 4), uVar1 != 0x14 &&
        (uVar1 != 8)) && (uVar1 != 0xd)))))) {
    return uVar1 & 0xffffff00;
  }
  return CONCAT31((int3)(uVar1 >> 8),1);
}


