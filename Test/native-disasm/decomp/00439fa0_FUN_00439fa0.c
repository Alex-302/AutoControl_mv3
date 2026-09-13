// FUN_00439fa0 @ 00439fa0 size=83 callers=2

void __fastcall FUN_00439fa0(int *param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  iVar1 = param_1[1];
  if (param_1[2] == iVar1) {
    iVar2 = *param_1;
    if (iVar2 - iVar1 == 1) {
                    /* WARNING: Subroutine does not return */
      FUN_00458ec4("vector<T> too long");
    }
    uVar4 = param_1[2] - iVar2;
    uVar5 = (iVar1 - iVar2) + 1;
    uVar3 = 0;
    if (uVar4 <= ~(uVar4 >> 1)) {
      uVar3 = (uVar4 >> 1) + uVar4;
    }
    if (uVar5 <= uVar3) {
      uVar5 = uVar3;
    }
    FUN_0043d780(param_1,uVar5);
  }
  return;
}


