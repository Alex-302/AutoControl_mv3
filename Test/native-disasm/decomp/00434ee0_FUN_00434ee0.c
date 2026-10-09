// FUN_00434ee0 @ 00434ee0 size=131 callers=3

void __fastcall FUN_00434ee0(void **param_1)

{
  void *pvVar1;
  void *pvVar2;
  undefined4 extraout_EDX;
  void *local_1c [4];
  void *local_c;
  void *local_8;
  
  if ((void *)((uint)param_1[4] | 7) < param_1[5]) {
    local_8 = (void *)0x7;
    local_c = (void *)0x0;
    local_1c[0] = (void *)((uint)local_1c[0] & 0xffff0000);
    FUN_0043a750(local_1c,param_1,0,0xffffffff);
    if (param_1 != local_1c) {
      FUN_0043d9a0((uint *)param_1,extraout_EDX,(uint *)local_1c);
      pvVar1 = param_1[4];
      param_1[4] = local_c;
      pvVar2 = param_1[5];
      param_1[5] = local_8;
      local_c = pvVar1;
      local_8 = pvVar2;
    }
    if ((void *)0x7 < local_8) {
      FUN_00402430(local_1c[0],(int)local_8 + 1,2);
    }
  }
  return;
}


