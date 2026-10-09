// FUN_00443dd0 @ 00443dd0 size=136 callers=1

void __fastcall FUN_00443dd0(int *param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  
  iVar4 = param_1[2] - param_1[1];
  iVar1 = iVar4 >> 0x1f;
  if (iVar4 / 0x24 + iVar1 == iVar1) {
    iVar1 = (param_1[1] - *param_1) / 0x24;
    if (iVar1 == 0x71c71c7) {
                    /* WARNING: Subroutine does not return */
      FUN_00458ec4("vector<T> too long");
    }
    uVar5 = iVar1 + 1;
    uVar2 = (param_1[2] - *param_1) / 0x24;
    uVar3 = 0;
    if (uVar2 <= 0x71c71c7 - (uVar2 >> 1)) {
      uVar3 = (uVar2 >> 1) + uVar2;
    }
    if (uVar5 <= uVar3) {
      uVar5 = uVar3;
    }
    FUN_004374f0(param_1,uVar5);
  }
  return;
}


