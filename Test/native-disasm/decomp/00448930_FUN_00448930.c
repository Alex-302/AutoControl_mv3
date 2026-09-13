// FUN_00448930 @ 00448930 size=78 callers=3

void FUN_00448930(void *param_1)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)((int)param_1 + 0x10);
  FUN_00434820((char *)((int)param_1 + 0x28));
  if (0xf < *(uint *)((int)param_1 + 0x24)) {
    FUN_00402430((void *)*puVar1,*(uint *)((int)param_1 + 0x24) + 1,1);
  }
  *(undefined4 *)((int)param_1 + 0x24) = 0xf;
  *(undefined4 *)((int)param_1 + 0x20) = 0;
  if (0xf < *(uint *)((int)param_1 + 0x24)) {
    puVar1 = (undefined4 *)*puVar1;
  }
  *(undefined1 *)puVar1 = 0;
  FID_conflict__free(param_1);
  return;
}


