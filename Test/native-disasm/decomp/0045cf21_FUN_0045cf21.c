// FUN_0045cf21 @ 0045cf21 size=119 callers=2

int __cdecl FUN_0045cf21(int param_1,int param_2,int param_3,uint *param_4,uint *param_5)

{
  int iVar1;
  int *piVar2;
  uint uVar3;
  uint uVar4;
  uint local_8;
  
  uVar3 = *(uint *)(param_1 + 0xc);
  iVar1 = *(int *)(param_1 + 0x10);
  uVar4 = uVar3;
  if (-1 < param_2) {
    piVar2 = (int *)(uVar3 * 0x14 + 8 + iVar1);
    local_8 = uVar3;
    do {
      if (uVar3 == 0xffffffff) goto LAB_0045cf93;
      uVar3 = uVar3 - 1;
      if (((piVar2[-6] < param_3) && (param_3 <= piVar2[-5])) || (uVar3 == 0xffffffff)) {
        param_2 = param_2 + -1;
        uVar4 = local_8;
        local_8 = uVar3;
      }
      piVar2 = piVar2 + -5;
    } while (-1 < param_2);
  }
  uVar3 = uVar3 + 1;
  *param_4 = uVar3;
  *param_5 = uVar4;
  if ((uVar4 <= *(uint *)(param_1 + 0xc)) && (uVar3 <= uVar4)) {
    return uVar3 * 0x14 + iVar1;
  }
LAB_0045cf93:
                    /* WARNING: Subroutine does not return */
  FUN_00464131();
}


