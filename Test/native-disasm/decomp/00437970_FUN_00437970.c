// FUN_00437970 @ 00437970 size=151 callers=1

/* WARNING: Removing unreachable block (ram,0x004379ee) */

undefined4 * FUN_00437970(undefined4 *param_1)

{
  undefined4 *puVar1;
  uint uVar2;
  undefined4 *puVar3;
  
  uVar2 = DAT_004a2838 &
          ((((DAT_0049da0c & 0xff ^ 0x811c9dc5) * 0x1000193 ^ DAT_0049da0c >> 8 & 0xff) * 0x1000193
           ^ DAT_0049da0c >> 0x10 & 0xff) * 0x1000193 ^ DAT_0049da0c >> 0x18) * 0x1000193;
  puVar1 = *(undefined4 **)(DAT_004a282c + uVar2 * 8);
  while( true ) {
    puVar3 = DAT_004a2824;
    if (*(undefined4 **)(DAT_004a282c + uVar2 * 8) != DAT_004a2824) {
      puVar3 = (undefined4 *)**(undefined4 **)(DAT_004a282c + uVar2 * 8 + 4);
    }
    if (puVar1 == puVar3) break;
    if (DAT_0049da0c == puVar1[2]) {
      *param_1 = puVar1;
      return param_1;
    }
    puVar1 = (undefined4 *)*puVar1;
  }
  *param_1 = DAT_004a2824;
  return param_1;
}


