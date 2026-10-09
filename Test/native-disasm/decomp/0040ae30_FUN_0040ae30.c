// FUN_0040ae30 @ 0040ae30 size=268 callers=2

undefined4 __fastcall FUN_0040ae30(int param_1,char param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint local_1c;
  uint local_18;
  uint local_14;
  int local_10;
  uint local_c;
  uint local_8;
  uint local_4;
  
  local_1c = 0;
  iVar1 = GdipGetImageWidth(*(undefined4 *)(param_1 + 4),&local_1c);
  if (iVar1 != 0) {
    *(int *)(param_1 + 8) = iVar1;
  }
  uVar4 = local_1c - 8;
  local_1c = 0;
  iVar1 = GdipGetImageHeight(*(undefined4 *)(param_1 + 4),&local_1c);
  if (iVar1 != 0) {
    *(int *)(param_1 + 8) = iVar1;
  }
  uVar5 = 0xff000000;
  local_18 = local_1c - 8;
  uVar2 = 0xff000000;
  local_4 = local_18;
  if (local_18 < uVar4) {
    local_4 = uVar4;
  }
  if (param_2 == '\0') {
    uVar2 = 0xffffffff;
  }
  local_4 = local_4 * uVar4;
  uVar3 = 0;
  local_1c = uVar2;
  if (local_4 != 0) {
    do {
      local_c = uVar3 % uVar4;
      local_10 = (int)(((ulonglong)uVar3 / (ulonglong)uVar4) % (ulonglong)local_18) + 4;
      uVar2 = GdipBitmapGetPixel(*(undefined4 *)(param_1 + 4),local_c + 4,local_10,&local_14);
      uVar6 = local_14;
      if (uVar2 != 0) {
        *(uint *)(param_1 + 8) = uVar2;
        uVar6 = uVar5;
      }
      if (uVar6 != local_1c) {
LAB_0040af32:
        return uVar2 & 0xffffff00;
      }
      uVar2 = GdipBitmapGetPixel(*(undefined4 *)(param_1 + 4),(uVar4 - local_c) + 3,local_10,
                                 &local_8);
      uVar5 = local_8;
      if (uVar2 != 0) {
        *(uint *)(param_1 + 8) = uVar2;
        uVar5 = uVar6;
      }
      if (uVar5 != local_1c) goto LAB_0040af32;
      uVar3 = uVar3 + 1 + uVar4;
    } while (uVar3 < local_4);
  }
  return CONCAT31((int3)(uVar2 >> 8),1);
}


