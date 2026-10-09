// FUN_00450190 @ 00450190 size=160 callers=1

undefined8 __fastcall FUN_00450190(uint *param_1,uint *param_2,uint *param_3)

{
  uint *puVar1;
  uint *puVar2;
  uint *puVar3;
  uint *puVar4;
  ulonglong uVar5;
  
  if (param_1 != param_2) {
    puVar4 = param_3 + 1;
    puVar2 = param_2;
    puVar3 = param_1 + 6;
    do {
      if (param_3 != (uint *)0x0) {
        *param_3 = puVar3[-6];
        puVar4[5] = 0xf;
        puVar4[4] = 0;
        *(undefined1 *)puVar4 = 0;
        if (*puVar3 < 0x10) {
          if (puVar3[-1] + 1 != 0) {
            uVar5 = FUN_0045b0e0(puVar4,puVar3 + -5,puVar3[-1] + 1);
            puVar2 = (uint *)(uVar5 >> 0x20);
          }
        }
        else {
          *puVar4 = puVar3[-5];
          puVar3[-5] = 0;
        }
        puVar4[4] = puVar3[-1];
        puVar4[5] = *puVar3;
        *puVar3 = 0xf;
        puVar3[-1] = 0;
        if (*puVar3 < 0x10) {
          puVar1 = puVar3 + -5;
        }
        else {
          puVar1 = (uint *)puVar3[-5];
        }
        *(undefined1 *)puVar1 = 0;
      }
      param_3 = param_3 + 7;
      puVar4 = puVar4 + 7;
      puVar1 = puVar3 + 1;
      puVar3 = puVar3 + 7;
    } while (puVar1 != param_2);
    return CONCAT44(puVar2,param_3);
  }
  return CONCAT44(param_2,param_3);
}


