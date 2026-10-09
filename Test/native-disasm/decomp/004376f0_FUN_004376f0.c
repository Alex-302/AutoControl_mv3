// FUN_004376f0 @ 004376f0 size=130 callers=2

undefined4 * FUN_004376f0(undefined4 *param_1,byte *param_2)

{
  undefined4 *puVar1;
  uint uVar2;
  undefined4 *puVar3;
  
  uVar2 = DAT_004a2a08 & ((*param_2 ^ 0x811c9dc5) * 0x1000193 ^ (uint)param_2[1]) * 0x1000193;
  puVar1 = *(undefined4 **)(DAT_004a29fc + uVar2 * 8);
  while( true ) {
    puVar3 = DAT_004a29f4;
    if (*(undefined4 **)(DAT_004a29fc + uVar2 * 8) != DAT_004a29f4) {
      puVar3 = (undefined4 *)**(undefined4 **)(DAT_004a29fc + uVar2 * 8 + 4);
    }
    if (puVar1 == puVar3) break;
    if (*(short *)(puVar1 + 2) == *(short *)param_2) {
      if (*(short *)param_2 != *(short *)(puVar1 + 2)) {
        puVar1 = DAT_004a29f4;
      }
      *param_1 = puVar1;
      return param_1;
    }
    puVar1 = (undefined4 *)*puVar1;
  }
  *param_1 = DAT_004a29f4;
  return param_1;
}


