// FUN_004034c0 @ 004034c0 size=83 callers=1

void __fastcall FUN_004034c0(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  *param_1 = &PTR_FUN_0048e854;
  puVar3 = (undefined4 *)param_1[6];
  while (puVar3 != (undefined4 *)0x0) {
    puVar1 = (undefined4 *)puVar3[6];
    puVar3[6] = 0;
    puVar2 = (undefined4 *)param_1[5];
    puVar4 = puVar3;
    while ((puVar3 = puVar1, puVar4 != puVar2 && (puVar4 != (undefined4 *)0x0))) {
      puVar3 = (undefined4 *)puVar4[3];
      puVar4[3] = 0;
      (**(code **)*puVar4)(1);
      puVar4 = puVar3;
    }
  }
  *param_1 = &PTR_LAB_0048ecb0;
  return;
}


