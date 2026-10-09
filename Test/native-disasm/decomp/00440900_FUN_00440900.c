// FUN_00440900 @ 00440900 size=107 callers=1

undefined2 * __fastcall FUN_00440900(undefined2 *param_1,uint param_2)

{
  uint uVar1;
  uint *puVar2;
  undefined2 local_4;
  undefined1 local_2 [2];
  
  puVar2 = (uint *)local_2;
  do {
    puVar2 = (uint *)((int)puVar2 + -2);
    uVar1 = param_2 / 10;
    *(short *)puVar2 = (short)param_2 + (short)uVar1 * -10 + 0x30;
    param_2 = uVar1;
  } while (uVar1 != 0);
  *(undefined4 *)(param_1 + 10) = 7;
  *(undefined4 *)(param_1 + 8) = 0;
  *param_1 = 0;
  if (puVar2 != (uint *)local_2) {
    FUN_0043a650(param_1,puVar2,(int)local_2 - (int)puVar2 >> 1);
  }
  return param_1;
}


