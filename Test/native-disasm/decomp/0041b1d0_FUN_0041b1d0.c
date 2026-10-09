// FUN_0041b1d0 @ 0041b1d0 size=339 callers=2

undefined2 * __fastcall FUN_0041b1d0(undefined2 *param_1,undefined4 *param_2)

{
  uint *puVar1;
  void **ppvVar2;
  uint uVar3;
  void *local_60 [5];
  uint local_4c;
  void *local_48 [4];
  undefined4 local_38;
  uint local_34;
  void *local_30 [4];
  undefined4 local_20;
  uint local_1c;
  undefined2 *local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047b6cb;
  local_10 = ExceptionList;
  local_14 = 0;
  local_18 = param_1;
  if ((uint)param_2[4] < 0x6f) {
    local_1c = 7;
    local_20 = 0;
    local_30[0] = (void *)((uint)local_30[0] & 0xffff0000);
    ExceptionList = &local_10;
    FUN_0043a750(local_30,param_2,0,0xffffffff);
    ppvVar2 = local_30;
    local_8 = 2;
    uVar3 = 4;
  }
  else {
    ExceptionList = &local_10;
    puVar1 = (uint *)FUN_00434e10(param_2,(undefined2 *)local_60,0,0x6e);
    local_8 = 0;
    local_14 = 1;
    ppvVar2 = (void **)FUN_00441ee0((undefined2 *)local_48,puVar1,(uint *)&DAT_0048d690);
    local_8 = 1;
    uVar3 = 3;
  }
  *(undefined4 *)(param_1 + 10) = 7;
  *(undefined4 *)(param_1 + 8) = 0;
  *param_1 = 0;
  local_14 = uVar3;
  FUN_0043a750(param_1,ppvVar2,0,0xffffffff);
  if ((uVar3 & 4) != 0) {
    uVar3 = uVar3 & 0xfffffffb;
    if (7 < local_1c) {
      FUN_00402430(local_30[0],local_1c + 1,2);
    }
    local_1c = 7;
    local_20 = 0;
    local_30[0] = (void *)((uint)local_30[0] & 0xffff0000);
  }
  if ((uVar3 & 2) != 0) {
    uVar3 = uVar3 & 0xfffffffd;
    if (7 < local_34) {
      FUN_00402430(local_48[0],local_34 + 1,2);
    }
    local_34 = 7;
    local_38 = 0;
    local_48[0] = (void *)((uint)local_48[0] & 0xffff0000);
  }
  if (((uVar3 & 1) != 0) && (7 < local_4c)) {
    FUN_00402430(local_60[0],local_4c + 1,2);
  }
  ExceptionList = local_10;
  return param_1;
}


