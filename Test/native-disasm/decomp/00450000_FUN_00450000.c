// FUN_00450000 @ 00450000 size=153 callers=1

undefined8 __fastcall FUN_00450000(uint *param_1,uint *param_2,uint *param_3)

{
  uint *puVar1;
  uint *puVar2;
  uint *puVar3;
  ulonglong uVar4;
  
  if (param_1 != param_2) {
    puVar2 = param_2;
    puVar3 = param_1 + 5;
    do {
      if (param_3 != (uint *)0x0) {
        param_3[5] = 0xf;
        param_3[4] = 0;
        *(undefined1 *)param_3 = 0;
        if (*puVar3 < 0x10) {
          if (puVar3[-1] + 1 != 0) {
            uVar4 = FUN_0045b0e0(param_3,puVar3 + -5,puVar3[-1] + 1);
            puVar2 = (uint *)(uVar4 >> 0x20);
          }
        }
        else {
          *param_3 = puVar3[-5];
          puVar3[-5] = 0;
        }
        param_3[4] = puVar3[-1];
        param_3[5] = *puVar3;
        *puVar3 = 0xf;
        puVar3[-1] = 0;
        if (*puVar3 < 0x10) {
          puVar1 = puVar3 + -5;
        }
        else {
          puVar1 = (uint *)puVar3[-5];
        }
        *(undefined1 *)puVar1 = 0;
        param_3[6] = puVar3[1];
      }
      param_3 = param_3 + 7;
      puVar1 = puVar3 + 2;
      puVar3 = puVar3 + 7;
    } while (puVar1 != param_2);
    return CONCAT44(puVar2,param_3);
  }
  return CONCAT44(param_2,param_3);
}


