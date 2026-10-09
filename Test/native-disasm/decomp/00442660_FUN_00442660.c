// FUN_00442660 @ 00442660 size=242 callers=2

uint * __fastcall FUN_00442660(uint *param_1,uint *param_2,undefined4 *param_3)

{
  bool bVar1;
  uint *puVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint *puVar6;
  uint *extraout_EDX;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_004792d9;
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
  if ((char)*param_2 == '\0') {
    iVar4 = 0;
    puVar2 = param_2;
  }
  else {
    puVar2 = (uint *)((int)param_2 + 1);
    puVar6 = param_2;
    do {
      uVar5 = *puVar6;
      puVar6 = (uint *)((int)puVar6 + 1);
    } while ((char)uVar5 != '\0');
    iVar4 = (int)puVar6 - (int)puVar2;
  }
  uVar5 = param_1[4];
  uVar3 = param_3[4] + iVar4;
  if (((uVar5 <= uVar3) && (param_1[5] != uVar3)) &&
     (bVar1 = FUN_0043de20(param_1,uVar3,'\x01'), puVar2 = extraout_EDX, bVar1)) {
    param_1[4] = uVar5;
    puVar6 = param_1;
    if (0xf < param_1[5]) {
      puVar6 = (uint *)*param_1;
    }
    *(undefined1 *)((int)puVar6 + uVar5) = 0;
  }
  if ((char)*param_2 == '\0') {
    uVar5 = 0;
  }
  else {
    puVar2 = (uint *)((int)param_2 + 1);
    puVar6 = param_2;
    do {
      uVar5 = *puVar6;
      puVar6 = (uint *)((int)puVar6 + 1);
    } while ((char)uVar5 != '\0');
    uVar5 = (int)puVar6 - (int)puVar2;
  }
  FUN_0043af90(param_1,puVar2,param_2,uVar5);
  FUN_0043b0c0(param_1,param_3,0,0xffffffff);
  ExceptionList = local_10;
  return param_1;
}


