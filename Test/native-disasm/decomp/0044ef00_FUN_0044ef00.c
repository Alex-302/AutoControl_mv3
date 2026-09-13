// FUN_0044ef00 @ 0044ef00 size=140 callers=2

undefined4 * __fastcall FUN_0044ef00(undefined4 *param_1,uint *param_2,char *param_3,char *param_4)

{
  char cVar1;
  uint uVar2;
  char *pcVar3;
  uint uVar4;
  uint uVar5;
  
  do {
    if (param_2 == (uint *)0x0) {
      *param_1 = param_3;
      return param_1;
    }
    uVar5 = 0;
    if (param_2[2] != 0) {
      uVar2 = *param_2;
      do {
        uVar4 = 0;
        pcVar3 = param_3;
        if (uVar2 != 0) {
          do {
            cVar1 = *pcVar3;
            pcVar3 = pcVar3 + 1;
            if (cVar1 != *(char *)(param_2[3] + uVar5 + uVar4)) break;
            uVar4 = uVar4 + 1;
          } while (uVar4 < uVar2);
        }
        if (pcVar3 == param_4) {
          *param_1 = param_4;
          return param_1;
        }
        uVar5 = uVar5 + uVar2;
      } while (uVar5 < param_2[2]);
    }
    param_2 = (uint *)param_2[4];
  } while( true );
}


