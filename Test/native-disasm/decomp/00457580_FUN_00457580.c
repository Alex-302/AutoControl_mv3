// FUN_00457580 @ 00457580 size=332 callers=3

uint * FUN_00457580(uint *param_1,uint *param_2,uint *param_3)

{
  byte *pbVar1;
  uint *puVar2;
  uint *puVar3;
  int iVar4;
  void *local_40 [5];
  uint local_2c;
  byte *local_28;
  int local_24;
  int local_20;
  undefined4 local_1c;
  undefined4 *local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0047ebf7;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[5] = 0xf;
  param_1[4] = 0;
  puVar2 = param_1;
  if (0xf < param_1[5]) {
    puVar2 = (uint *)*param_1;
  }
  *(undefined1 *)puVar2 = 0;
  local_8 = 0;
  local_1c = 1;
  if (param_2 != param_3) {
    local_28 = (byte *)0x0;
    local_24 = 0;
    local_20 = 0;
    FUN_00447980(&local_28,param_2,(int)param_3);
    pbVar1 = local_28;
    local_8 = 1;
    iVar4 = local_24 - (int)local_28;
    FUN_00402950((void *)local_18[1],local_28,local_28 + iVar4);
    puVar2 = (uint *)FUN_0044da90((void *)*local_18,local_40,pbVar1,pbVar1 + iVar4);
    if (param_1 != puVar2) {
      if (0xf < param_1[5]) {
        FUN_00402430((void *)*param_1,param_1[5] + 1,1);
      }
      param_1[5] = 0xf;
      param_1[4] = 0;
      puVar3 = param_1;
      if (0xf < param_1[5]) {
        puVar3 = (uint *)*param_1;
      }
      *(undefined1 *)puVar3 = 0;
      FUN_0043b1c0(param_1,puVar2);
    }
    if (0xf < local_2c) {
      FUN_00402430(local_40[0],local_2c + 1,1);
    }
    if (pbVar1 != (byte *)0x0) {
      FUN_00402430(pbVar1,local_20 - (int)pbVar1,1);
    }
  }
  ExceptionList = local_10;
  return param_1;
}


