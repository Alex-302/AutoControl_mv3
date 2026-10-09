// FUN_00435b00 @ 00435b00 size=136 callers=2

void __fastcall FUN_00435b00(int *param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  
  iVar4 = param_1[2] - param_1[1];
  iVar1 = iVar4 >> 0x1f;
  if (iVar4 / 0x14 + iVar1 == iVar1) {
    iVar1 = (param_1[1] - *param_1) / 0x14;
    if (iVar1 == 0xccccccc) {
                    /* WARNING: Subroutine does not return */
      FUN_00458ec4("vector<T> too long");
    }
    uVar5 = iVar1 + 1;
    uVar2 = (param_1[2] - *param_1) / 0x14;
    uVar3 = 0;
    if (uVar2 <= 0xccccccc - (uVar2 >> 1)) {
      uVar3 = (uVar2 >> 1) + uVar2;
    }
    if (uVar5 <= uVar3) {
      uVar5 = uVar3;
    }
    FUN_0043c200(param_1,uVar5);
  }
  return;
}


