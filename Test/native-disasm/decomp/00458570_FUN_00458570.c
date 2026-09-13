// FUN_00458570 @ 00458570 size=108 callers=1

undefined1 * __fastcall FUN_00458570(undefined1 *param_1,undefined1 *param_2,undefined1 *param_3)

{
  undefined1 uVar1;
  undefined1 *puVar2;
  undefined1 *puVar3;
  
  puVar2 = param_2;
  puVar3 = param_1;
  if (param_1 != param_2) {
    do {
      puVar2 = puVar2 + -1;
      if (puVar3 == puVar2) break;
      uVar1 = *puVar3;
      *puVar3 = *puVar2;
      puVar3 = puVar3 + 1;
      *puVar2 = uVar1;
    } while (puVar3 != puVar2);
  }
  puVar2 = param_3;
  puVar3 = param_2;
  if (param_2 != param_3) {
    do {
      puVar2 = puVar2 + -1;
      if (puVar3 == puVar2) break;
      uVar1 = *puVar3;
      *puVar3 = *puVar2;
      puVar3 = puVar3 + 1;
      *puVar2 = uVar1;
    } while (puVar3 != puVar2);
  }
  puVar2 = param_3;
  puVar3 = param_1;
  if (param_1 != param_3) {
    do {
      puVar2 = puVar2 + -1;
      if (puVar3 == puVar2) break;
      uVar1 = *puVar3;
      *puVar3 = *puVar2;
      puVar3 = puVar3 + 1;
      *puVar2 = uVar1;
    } while (puVar3 != puVar2);
  }
  return param_3 + ((int)param_1 - (int)param_2);
}


