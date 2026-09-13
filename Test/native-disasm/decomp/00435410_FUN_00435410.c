// FUN_00435410 @ 00435410 size=136 callers=1

void __fastcall FUN_00435410(void **param_1)

{
  void *pvVar1;
  undefined1 *puVar2;
  undefined4 extraout_EDX;
  void *local_20 [4];
  void *local_10;
  undefined1 *local_c;
  
  if ((void *)((uint)param_1[4] | 0xf) < param_1[5]) {
    local_c = &DAT_0000000f;
    local_10 = (void *)0x0;
    local_20[0] = (void *)((uint)local_20[0] & 0xffffff00);
    FUN_0043ade0(local_20,param_1,0,0xffffffff);
    if (param_1 != local_20) {
      FUN_0043dee0((uint *)param_1,extraout_EDX,(uint *)local_20);
      pvVar1 = param_1[4];
      param_1[4] = local_10;
      puVar2 = param_1[5];
      param_1[5] = local_c;
      local_10 = pvVar1;
      local_c = puVar2;
    }
    if (&DAT_0000000f < local_c) {
      FUN_00402430(local_20[0],(uint)(local_c + 1),1);
    }
  }
  return;
}


