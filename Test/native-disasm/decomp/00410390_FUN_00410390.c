// FUN_00410390 @ 00410390 size=125 callers=1

uint __fastcall FUN_00410390(undefined4 *param_1)

{
  byte bVar1;
  uint uVar2;
  undefined4 *puVar3;
  uint uVar4;
  
  uVar2 = 0;
  uVar4 = 0;
  if (param_1[4] != 0) {
    do {
      puVar3 = param_1;
      if (0xf < (uint)param_1[5]) {
        puVar3 = (undefined4 *)*param_1;
      }
      bVar1 = *(byte *)((int)puVar3 + uVar4);
      if (uVar2 == 0) {
        if ((char)bVar1 < '\0') {
          if ((bVar1 & 0xe0) == 0xc0) {
            uVar2 = 1;
          }
          else if ((bVar1 & 0xf0) == 0xe0) {
            uVar2 = 2;
          }
          else {
            uVar2 = (uint)((bVar1 & 0xf8) == 0xf0) * 4 - 1;
            if (uVar2 == 0xffffffff) goto LAB_004103bf;
          }
        }
        else {
          uVar2 = 0;
        }
      }
      else {
        uVar2 = uVar2 - 1;
        if ((bVar1 & 0xc0) != 0x80) {
LAB_004103bf:
          return uVar2 & 0xffffff00;
        }
      }
      uVar4 = uVar4 + 1;
    } while (uVar4 < (uint)param_1[4]);
  }
  return CONCAT31((int3)(uVar2 >> 8),1);
}


