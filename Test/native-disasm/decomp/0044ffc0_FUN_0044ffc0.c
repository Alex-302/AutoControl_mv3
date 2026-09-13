// FUN_0044ffc0 @ 0044ffc0 size=62 callers=1

void __fastcall FUN_0044ffc0(uint param_1,uint param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  uVar3 = 0;
  uVar4 = (param_2 - param_1) + 3 >> 2;
  if (param_2 < param_1) {
    uVar4 = 0;
  }
  if (uVar4 != 0) {
    iVar2 = param_1 - (int)param_3;
    do {
      if (param_3 != (undefined4 *)0x0) {
        uVar1 = *(undefined4 *)(iVar2 + (int)param_3);
        *(undefined4 *)(iVar2 + (int)param_3) = 0;
        *param_3 = uVar1;
      }
      uVar3 = uVar3 + 1;
      param_3 = param_3 + 1;
    } while (uVar3 != uVar4);
  }
  return;
}


