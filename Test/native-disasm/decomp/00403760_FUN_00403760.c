// FUN_00403760 @ 00403760 size=95 callers=1

int * __fastcall FUN_00403760(int *param_1,short *param_2)

{
  short sVar1;
  uint uVar2;
  int *piVar3;
  int iVar4;
  short *psVar5;
  
  if (*param_2 == 0) {
    iVar4 = 0;
    piVar3 = param_1;
  }
  else {
    piVar3 = (int *)(param_2 + 1);
    psVar5 = param_2;
    do {
      sVar1 = *psVar5;
      psVar5 = psVar5 + 1;
    } while (sVar1 != 0);
    iVar4 = (int)psVar5 - (int)piVar3 >> 1;
  }
  iVar4 = FUN_0043a160(param_1,param_2,piVar3,iVar4);
  uVar2 = iVar4 + 1;
  if (uVar2 <= (uint)param_1[4]) {
    param_1[4] = uVar2;
    if (7 < (uint)param_1[5]) {
      *(undefined2 *)(*param_1 + uVar2 * 2) = 0;
      return param_1;
    }
    *(undefined2 *)((int)param_1 + uVar2 * 2) = 0;
    return param_1;
  }
                    /* WARNING: Subroutine does not return */
  FUN_00458ee4("invalid string position");
}


