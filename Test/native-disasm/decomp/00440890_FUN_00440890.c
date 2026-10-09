// FUN_00440890 @ 00440890 size=106 callers=1

undefined1 * __fastcall FUN_00440890(undefined1 *param_1,uint param_2)

{
  uint uVar1;
  uint *puVar2;
  undefined1 local_4 [4];
  
  puVar2 = (uint *)(local_4 + 1);
  do {
    puVar2 = (uint *)((int)puVar2 + -1);
    uVar1 = param_2 / 10;
    *(char *)puVar2 = (char)param_2 + (char)uVar1 * -10 + '0';
    param_2 = uVar1;
  } while (uVar1 != 0);
  *(undefined4 *)(param_1 + 0x14) = 0xf;
  *(undefined4 *)(param_1 + 0x10) = 0;
  *param_1 = 0;
  if (puVar2 != (uint *)(local_4 + 1)) {
    FUN_0043ace0(param_1,puVar2,(int)(local_4 + 1) - (int)puVar2);
  }
  return param_1;
}


