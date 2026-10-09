// FUN_004407f0 @ 004407f0 size=151 callers=1

undefined1 * __fastcall FUN_004407f0(undefined1 *param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  uint *puVar3;
  uint *puVar4;
  undefined1 local_5 [5];
  
  puVar4 = (uint *)(local_5 + 2);
  if ((int)param_2 < 0) {
    uVar2 = -param_2;
    do {
      puVar3 = puVar4;
      puVar4 = (uint *)((int)puVar3 + -1);
      uVar1 = uVar2 / 10;
      *(char *)puVar4 = (char)uVar2 + (char)uVar1 * -10 + '0';
      uVar2 = uVar1;
    } while (uVar1 != 0);
    puVar4 = (uint *)((int)puVar3 + -2);
    *(char *)puVar4 = '-';
  }
  else {
    do {
      puVar4 = (uint *)((int)puVar4 + -1);
      uVar2 = param_2 / 10;
      *(char *)puVar4 = (char)param_2 + (char)uVar2 * -10 + '0';
      param_2 = uVar2;
    } while (uVar2 != 0);
  }
  *(undefined4 *)(param_1 + 0x14) = 0xf;
  *(undefined4 *)(param_1 + 0x10) = 0;
  *param_1 = 0;
  if (puVar4 != (uint *)(local_5 + 2)) {
    FUN_0043ace0(param_1,puVar4,(int)(local_5 + 2) - (int)puVar4);
  }
  return param_1;
}


