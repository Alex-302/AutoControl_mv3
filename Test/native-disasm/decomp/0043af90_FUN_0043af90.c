// FUN_0043af90 @ 0043af90 size=288 callers=5

undefined8 __fastcall FUN_0043af90(uint *param_1,uint *param_2,uint *param_3,uint param_4)

{
  uint uVar1;
  uint *puVar2;
  uint *extraout_EDX;
  undefined8 uVar3;
  ulonglong uVar4;
  
  if (param_3 != (uint *)0x0) {
    uVar1 = param_1[5];
    puVar2 = param_1;
    if (0xf < uVar1) {
      puVar2 = (uint *)*param_1;
    }
    if (puVar2 <= param_3) {
      param_2 = param_1;
      if (0xf < uVar1) {
        param_2 = (uint *)*param_1;
      }
      if (param_3 < (uint *)(param_1[4] + (int)param_2)) {
        if (uVar1 < 0x10) {
          uVar3 = FUN_0043b0c0(param_1,param_1,(int)param_3 - (int)param_1,param_4);
          return uVar3;
        }
        uVar3 = FUN_0043b0c0(param_1,param_1,(int)param_3 - *param_1,param_4);
        return uVar3;
      }
    }
  }
  if (~param_1[4] <= param_4) {
                    /* WARNING: Subroutine does not return */
    FUN_00458ec4("string too long");
  }
  uVar1 = param_1[4] + param_4;
  if (param_4 != 0) {
    if (uVar1 == 0xffffffff) {
                    /* WARNING: Subroutine does not return */
      FUN_00458ec4("string too long");
    }
    if (param_1[5] < uVar1) {
      FUN_0043f5f0(param_1,uVar1);
      param_2 = extraout_EDX;
      if (uVar1 == 0) goto LAB_0043b093;
    }
    else if (uVar1 == 0) {
      param_1[4] = 0;
      if (param_1[5] < 0x10) {
        *(undefined1 *)param_1 = 0;
        return CONCAT44(param_2,param_1);
      }
      *(undefined1 *)*param_1 = 0;
      return CONCAT44(param_2,param_1);
    }
    puVar2 = param_1;
    if (0xf < param_1[5]) {
      puVar2 = (uint *)*param_1;
    }
    if (param_4 != 0) {
      uVar4 = FUN_0045c870((uint *)(param_1[4] + (int)puVar2),param_3,param_4);
      param_2 = (uint *)(uVar4 >> 0x20);
    }
    param_1[4] = uVar1;
    if (0xf < param_1[5]) {
      *(undefined1 *)(*param_1 + uVar1) = 0;
      return CONCAT44(param_2,param_1);
    }
    *(undefined1 *)((int)param_1 + uVar1) = 0;
  }
LAB_0043b093:
  return CONCAT44(param_2,param_1);
}


