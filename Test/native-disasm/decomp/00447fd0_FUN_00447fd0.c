// FUN_00447fd0 @ 00447fd0 size=84 callers=1

void __fastcall FUN_00447fd0(void *param_1,byte *param_2,byte *param_3)

{
  byte *pbVar1;
  byte *pbVar2;
  int iVar3;
  int iVar4;
  
  pbVar1 = _memchr(param_1,(uint)*param_3,(int)param_2 - (int)param_1);
  pbVar2 = param_2;
  if (pbVar1 != (byte *)0x0) {
    pbVar2 = pbVar1;
  }
  if (pbVar2 != param_2) {
    pbVar1 = pbVar2 + 1;
    iVar4 = (int)param_2 - (int)pbVar1;
    iVar3 = 0;
    if (param_2 < pbVar1) {
      iVar4 = 0;
    }
    if (iVar4 != 0) {
      do {
        if (*pbVar1 != *param_3) {
          *pbVar2 = *pbVar1;
          pbVar2 = pbVar2 + 1;
        }
        iVar3 = iVar3 + 1;
        pbVar1 = pbVar1 + 1;
      } while (iVar3 != iVar4);
    }
  }
  return;
}


