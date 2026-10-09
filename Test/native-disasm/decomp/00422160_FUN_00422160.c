// FUN_00422160 @ 00422160 size=215 callers=2

undefined4 * __thiscall FUN_00422160(void *this,undefined4 *param_1,int param_2)

{
  byte *pbVar1;
  int *piVar2;
  byte *pbVar3;
  int *piVar4;
  undefined4 local_18;
  undefined1 local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0047bce9;
  local_10 = ExceptionList;
  local_8 = 0;
  local_18 = 0;
  ExceptionList = &local_10;
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  FUN_0043ef20(param_1,0,&local_18);
  param_1[3] = 0;
  local_8 = 0;
  piVar2 = *(int **)((int)this + 0x30);
  for (piVar4 = *(int **)((int)this + 0x2c); piVar4 != piVar2; piVar4 = piVar4 + 6) {
    pbVar1 = (byte *)(param_2 + (char)piVar4[5] * 0x18);
    pbVar3 = pbVar1;
    if (0xf < *(uint *)(param_2 + 0x14 + (char)piVar4[5] * 0x18)) {
      pbVar3 = *(byte **)pbVar1;
    }
    local_11 = FUN_00446870(pbVar3,pbVar3 + *(int *)(pbVar1 + 0x10),pbVar3,piVar4,0x10);
    FUN_00433920(param_1,&local_11);
  }
  ExceptionList = local_10;
  return param_1;
}


