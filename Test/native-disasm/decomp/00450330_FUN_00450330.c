// FUN_00450330 @ 00450330 size=55 callers=5

void __fastcall FUN_00450330(uint param_1,uint param_2,undefined4 *param_3)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  uVar2 = 0;
  uVar3 = (param_2 - param_1) + 3 >> 2;
  if (param_2 < param_1) {
    uVar3 = 0;
  }
  if (uVar3 != 0) {
    iVar1 = param_1 - (int)param_3;
    do {
      if (param_3 != (undefined4 *)0x0) {
        *param_3 = *(undefined4 *)(iVar1 + (int)param_3);
      }
      uVar2 = uVar2 + 1;
      param_3 = param_3 + 1;
    } while (uVar2 != uVar3);
  }
  return;
}


