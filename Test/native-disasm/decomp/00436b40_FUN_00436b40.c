// FUN_00436b40 @ 00436b40 size=150 callers=2

undefined4 * FUN_00436b40(undefined4 *param_1,byte *param_2)

{
  undefined4 *puVar1;
  uint uVar2;
  undefined4 *puVar3;
  
  uVar2 = DAT_004a2a78 &
          ((((*param_2 ^ 0x811c9dc5) * 0x1000193 ^ (uint)param_2[1]) * 0x1000193 ^ (uint)param_2[2])
           * 0x1000193 ^ (uint)param_2[3]) * 0x1000193;
  puVar1 = *(undefined4 **)(DAT_004a2a6c + uVar2 * 8);
  while( true ) {
    puVar3 = DAT_004a2a64;
    if (*(undefined4 **)(DAT_004a2a6c + uVar2 * 8) != DAT_004a2a64) {
      puVar3 = (undefined4 *)**(undefined4 **)(DAT_004a2a6c + uVar2 * 8 + 4);
    }
    if (puVar1 == puVar3) break;
    if (puVar1[2] == *(int *)param_2) {
      if (*(int *)param_2 != puVar1[2]) {
        puVar1 = DAT_004a2a64;
      }
      *param_1 = puVar1;
      return param_1;
    }
    puVar1 = (undefined4 *)*puVar1;
  }
  *param_1 = DAT_004a2a64;
  return param_1;
}


