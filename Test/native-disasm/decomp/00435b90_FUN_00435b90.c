// FUN_00435b90 @ 00435b90 size=94 callers=6

void __fastcall FUN_00435b90(int *param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  if (param_1[2] - param_1[1] >> 2 == 0) {
    iVar2 = param_1[1] - *param_1 >> 2;
    if (iVar2 == 0x3fffffff) {
                    /* WARNING: Subroutine does not return */
      FUN_00458ec4("vector<T> too long");
    }
    uVar3 = iVar2 + 1;
    uVar4 = param_1[2] - *param_1 >> 2;
    uVar1 = 0;
    if (uVar4 <= 0x3fffffff - (uVar4 >> 1)) {
      uVar1 = (uVar4 >> 1) + uVar4;
    }
    if (uVar3 <= uVar1) {
      uVar3 = uVar1;
    }
    FUN_0043c290(param_1,uVar3);
  }
  return;
}


