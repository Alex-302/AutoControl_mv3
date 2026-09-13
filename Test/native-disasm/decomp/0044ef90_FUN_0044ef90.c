// FUN_0044ef90 @ 0044ef90 size=50 callers=2

uint __fastcall FUN_0044ef90(uint param_1,int param_2)

{
  uint uVar1;
  
  uVar1 = 0;
  if (*(uint *)(param_2 + 4) != 0) {
    do {
      if ((*(byte *)(*(int *)(param_2 + 8) + uVar1) <= param_1) &&
         (param_1 <= *(byte *)(*(int *)(param_2 + 8) + 1 + uVar1))) {
        return CONCAT31((int3)(uVar1 >> 8),1);
      }
      uVar1 = uVar1 + 2;
    } while (uVar1 < *(uint *)(param_2 + 4));
  }
  return uVar1 & 0xffffff00;
}


