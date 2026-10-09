// FUN_0043d9a0 @ 0043d9a0 size=119 callers=1

undefined8 __fastcall FUN_0043d9a0(uint *param_1,undefined4 param_2,uint *param_3)

{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  ulonglong uVar4;
  undefined8 uVar5;
  
  if (param_1[5] < 8) {
    if (param_3[5] < 8) {
      uVar5 = FUN_00443a70((undefined2 *)param_1,(undefined2 *)param_3);
      return uVar5;
    }
    uVar1 = *param_3;
    uVar3 = 0;
    if (param_1[4] + 1 != 0) {
      uVar4 = FUN_0045c870(param_3,param_1,(param_1[4] + 1) * 2);
      param_2 = (undefined4)(uVar4 >> 0x20);
      uVar3 = (undefined4)uVar4;
    }
    *param_1 = uVar1;
    return CONCAT44(param_2,uVar3);
  }
  if (7 < param_3[5]) {
    uVar1 = *param_1;
    uVar2 = *param_3;
    *param_1 = uVar2;
    *param_3 = uVar1;
    return CONCAT44(uVar1,uVar2);
  }
  uVar1 = *param_1;
  uVar3 = 0;
  if (param_3[4] + 1 != 0) {
    uVar4 = FUN_0045c870(param_1,param_3,(param_3[4] + 1) * 2);
    param_2 = (undefined4)(uVar4 >> 0x20);
    uVar3 = (undefined4)uVar4;
  }
  *param_3 = uVar1;
  return CONCAT44(param_2,uVar3);
}


