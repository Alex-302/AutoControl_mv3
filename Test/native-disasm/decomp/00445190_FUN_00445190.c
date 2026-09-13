// FUN_00445190 @ 00445190 size=345 callers=3

undefined8 __fastcall
FUN_00445190(uint *param_1,uint *param_2,undefined4 param_3,uint *param_4,uint param_5,uint param_6)

{
  uint uVar1;
  uint *puVar2;
  int iVar3;
  uint *extraout_EDX;
  ulonglong uVar4;
  
  if (param_4[4] < param_5) {
                    /* WARNING: Subroutine does not return */
    FUN_00458ee4("invalid string position");
  }
  uVar1 = param_4[4] - param_5;
  if (uVar1 < param_6) {
    param_6 = uVar1;
  }
  if (~param_1[4] <= param_6) {
                    /* WARNING: Subroutine does not return */
    FUN_00458ec4("string too long");
  }
  uVar1 = param_1[4] + param_6;
  if (param_6 != 0) {
    if (uVar1 == 0xffffffff) {
                    /* WARNING: Subroutine does not return */
      FUN_00458ec4("string too long");
    }
    if (param_1[5] < uVar1) {
      FUN_0043f5f0(param_1,uVar1);
      param_2 = extraout_EDX;
      if (uVar1 == 0) goto LAB_004452c2;
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
      uVar4 = FUN_0045b0e0((uint *)((int)puVar2 + param_6),param_2,param_1[4]);
      param_2 = (uint *)(uVar4 >> 0x20);
    }
    if (param_1 == param_4) {
      iVar3 = param_5 + param_6;
      if (param_5 == 0) {
        iVar3 = 0;
      }
      param_2 = param_1;
      puVar2 = param_1;
      if (0xf < param_1[5]) {
        param_2 = (uint *)*param_1;
        puVar2 = (uint *)*param_1;
      }
      if (param_6 != 0) {
        uVar4 = FUN_0045b0e0(param_2,(uint *)(iVar3 + (int)puVar2),param_6);
        param_2 = (uint *)(uVar4 >> 0x20);
      }
    }
    else {
      if (0xf < param_4[5]) {
        param_4 = (uint *)*param_4;
      }
      puVar2 = param_1;
      if (0xf < param_1[5]) {
        puVar2 = (uint *)*param_1;
      }
      if (param_6 != 0) {
        uVar4 = FUN_0045c870(puVar2,(uint *)(param_5 + (int)param_4),param_6);
        param_2 = (uint *)(uVar4 >> 0x20);
      }
    }
    param_1[4] = uVar1;
    if (0xf < param_1[5]) {
      *(undefined1 *)(*param_1 + uVar1) = 0;
      return CONCAT44(param_2,param_1);
    }
    *(undefined1 *)((int)param_1 + uVar1) = 0;
  }
LAB_004452c2:
  return CONCAT44(param_2,param_1);
}


