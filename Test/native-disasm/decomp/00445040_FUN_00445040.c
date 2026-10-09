// FUN_00445040 @ 00445040 size=334 callers=1

undefined8 __fastcall
FUN_00445040(uint *param_1,uint *param_2,undefined4 param_3,uint *param_4,uint param_5)

{
  uint uVar1;
  uint *puVar2;
  uint *extraout_EDX;
  undefined8 uVar3;
  ulonglong uVar4;
  
  if (param_4 != (uint *)0x0) {
    uVar1 = param_1[5];
    puVar2 = param_1;
    if (0xf < uVar1) {
      puVar2 = (uint *)*param_1;
    }
    if (puVar2 <= param_4) {
      param_2 = param_1;
      if (0xf < uVar1) {
        param_2 = (uint *)*param_1;
      }
      if (param_4 < (uint *)(param_1[4] + (int)param_2)) {
        if (0xf < uVar1) {
          uVar3 = FUN_00445190(param_1,param_2,uVar1,param_1,(int)param_4 - *param_1,param_5);
          return uVar3;
        }
        uVar3 = FUN_00445190(param_1,param_2,uVar1,param_1,(int)param_4 - (int)param_1,param_5);
        return uVar3;
      }
    }
  }
  if (~param_1[4] <= param_5) {
                    /* WARNING: Subroutine does not return */
    FUN_00458ec4("string too long");
  }
  uVar1 = param_1[4] + param_5;
  if (param_5 != 0) {
    if (uVar1 == 0xffffffff) {
                    /* WARNING: Subroutine does not return */
      FUN_00458ec4("string too long");
    }
    if (param_1[5] < uVar1) {
      FUN_0043f5f0(param_1,uVar1);
      param_2 = extraout_EDX;
      if (uVar1 == 0) goto LAB_00445171;
    }
    else if (uVar1 == 0) {
      param_1[4] = 0;
      if (0xf < param_1[5]) {
        *(undefined1 *)*param_1 = 0;
        return CONCAT44(param_2,param_1);
      }
      *(undefined1 *)param_1 = 0;
      return CONCAT44(param_2,param_1);
    }
    puVar2 = param_1;
    param_2 = param_1;
    if (0xf < param_1[5]) {
      param_2 = (uint *)*param_1;
      puVar2 = (uint *)*param_1;
    }
    if (param_1[4] != 0) {
      uVar4 = FUN_0045b0e0((uint *)((int)puVar2 + param_5),param_2,param_1[4]);
      param_2 = (uint *)(uVar4 >> 0x20);
    }
    puVar2 = param_1;
    if (0xf < param_1[5]) {
      puVar2 = (uint *)*param_1;
    }
    if (param_5 != 0) {
      uVar4 = FUN_0045c870(puVar2,param_4,param_5);
      param_2 = (uint *)(uVar4 >> 0x20);
    }
    param_1[4] = uVar1;
    if (0xf < param_1[5]) {
      *(undefined1 *)(*param_1 + uVar1) = 0;
      return CONCAT44(param_2,param_1);
    }
    *(undefined1 *)((int)param_1 + uVar1) = 0;
  }
LAB_00445171:
  return CONCAT44(param_2,param_1);
}


