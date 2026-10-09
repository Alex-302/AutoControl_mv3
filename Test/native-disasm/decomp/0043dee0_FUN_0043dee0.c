// FUN_0043dee0 @ 0043dee0 size=113 callers=1

ulonglong __fastcall FUN_0043dee0(uint *param_1,undefined4 param_2,uint *param_3)

{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  ulonglong uVar4;
  
  uVar4 = CONCAT44(param_2,param_3);
  if (param_1[5] < 0x10) {
    if (param_3[5] < 0x10) {
      uVar4 = FUN_00443ab0((undefined1 *)param_1,(undefined1 *)param_3);
      return uVar4;
    }
    uVar1 = *param_3;
    if (param_1[4] + 1 != 0) {
      uVar4 = FUN_0045c870(param_3,param_1,param_1[4] + 1);
    }
    *param_1 = uVar1;
    return uVar4;
  }
  if (0xf < param_3[5]) {
    uVar1 = *param_1;
    uVar2 = *param_3;
    *param_1 = uVar2;
    *param_3 = uVar1;
    return CONCAT44(uVar1,uVar2);
  }
  uVar1 = *param_1;
  uVar3 = 0;
  if (param_3[4] + 1 != 0) {
    uVar4 = FUN_0045c870(param_1,param_3,param_3[4] + 1);
    param_2 = (undefined4)(uVar4 >> 0x20);
    uVar3 = (undefined4)uVar4;
  }
  *param_3 = uVar1;
  return CONCAT44(param_2,uVar3);
}


