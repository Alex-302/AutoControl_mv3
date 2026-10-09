// FUN_0044f050 @ 0044f050 size=113 callers=2

void __fastcall FUN_0044f050(char *param_1,char *param_2,uint *param_3)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  uint uVar6;
  
  do {
    if (param_3 == (uint *)0x0) {
      return;
    }
    uVar4 = param_3[2];
    uVar6 = 0;
    if (uVar4 != 0) {
      uVar2 = *param_3;
      do {
        uVar3 = 0;
        pcVar5 = param_1;
        if (uVar2 != 0) {
          do {
            cVar1 = *pcVar5;
            pcVar5 = pcVar5 + 1;
            if (cVar1 != *(char *)(param_3[3] + uVar6 + uVar3)) break;
            uVar3 = uVar3 + 1;
          } while (uVar3 < uVar2);
          uVar4 = param_3[2];
        }
        if (pcVar5 == param_2) {
          return;
        }
        uVar6 = uVar6 + uVar2;
      } while (uVar6 < uVar4);
    }
    param_3 = (uint *)param_3[4];
  } while( true );
}


