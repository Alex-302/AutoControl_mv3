// FUN_0043dbe0 @ 0043dbe0 size=292 callers=3

undefined8 __fastcall FUN_0043dbe0(uint *param_1,uint *param_2,uint *param_3,uint param_4)

{
  uint uVar1;
  uint *puVar2;
  uint *extraout_EDX;
  undefined8 uVar3;
  ulonglong uVar4;
  
  if (param_3 != (uint *)0x0) {
    uVar1 = param_1[5];
    puVar2 = param_1;
    if (7 < uVar1) {
      puVar2 = (uint *)*param_1;
    }
    if (puVar2 <= param_3) {
      param_2 = param_1;
      if (7 < uVar1) {
        param_2 = (uint *)*param_1;
      }
      if (param_3 < (uint *)((int)param_2 + param_1[4] * 2)) {
        puVar2 = param_1;
        if (7 < uVar1) {
          puVar2 = (uint *)*param_1;
        }
        uVar3 = FUN_0043dd10(param_1,param_1,(int)param_3 - (int)puVar2 >> 1,param_4);
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
    if (0x7ffffffe < uVar1) {
                    /* WARNING: Subroutine does not return */
      FUN_00458ec4("string too long");
    }
    if (param_1[5] < uVar1) {
      FUN_0043d830(param_1,uVar1);
      param_2 = extraout_EDX;
      if (uVar1 == 0) goto LAB_0043dce7;
    }
    else if (uVar1 == 0) {
      param_1[4] = 0;
      if (param_1[5] < 8) {
        *(undefined2 *)param_1 = 0;
        return CONCAT44(param_2,param_1);
      }
      *(undefined2 *)*param_1 = 0;
      return CONCAT44(param_2,param_1);
    }
    puVar2 = param_1;
    if (7 < param_1[5]) {
      puVar2 = (uint *)*param_1;
    }
    if (param_4 != 0) {
      uVar4 = FUN_0045c870((uint *)((int)puVar2 + param_1[4] * 2),param_3,param_4 * 2);
      param_2 = (uint *)(uVar4 >> 0x20);
    }
    param_1[4] = uVar1;
    if (7 < param_1[5]) {
      *(undefined2 *)(*param_1 + uVar1 * 2) = 0;
      return CONCAT44(param_2,param_1);
    }
    *(undefined2 *)((int)param_1 + uVar1 * 2) = 0;
  }
LAB_0043dce7:
  return CONCAT44(param_2,param_1);
}


