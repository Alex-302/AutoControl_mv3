// FUN_00457850 @ 00457850 size=108 callers=1

void FUN_00457850(undefined1 *param_1,undefined1 *param_2,uint param_3,uint *param_4)

{
  uint *puVar1;
  uint *puVar2;
  
  puVar2 = (uint *)0x0;
  if (*param_4 != 0) {
    do {
      puVar2 = (uint *)*param_4;
      if (*puVar2 <= param_3) break;
      param_4 = puVar2 + 4;
    } while (puVar2[4] != 0);
    puVar2 = (uint *)*param_4;
    if ((puVar2 != (uint *)0x0) && (param_3 == *puVar2)) goto LAB_004578a4;
  }
  puVar1 = operator_new(0x14);
  *puVar1 = param_3;
  puVar1[1] = 0;
  puVar1[2] = 0;
  puVar1[3] = 0;
  *param_4 = (uint)puVar1;
  puVar1[4] = (uint)puVar2;
LAB_004578a4:
  FUN_00457f00((void *)(*param_4 + 4),param_1,param_2);
  return;
}


