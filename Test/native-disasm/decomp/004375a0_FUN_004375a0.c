// FUN_004375a0 @ 004375a0 size=91 callers=8

void __fastcall FUN_004375a0(int *param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  if (param_1[2] - param_1[1] >> 1 == 0) {
    iVar2 = param_1[1] - *param_1 >> 1;
    if (iVar2 == 0x7fffffff) {
                    /* WARNING: Subroutine does not return */
      FUN_00458ec4("vector<T> too long");
    }
    uVar3 = iVar2 + 1;
    uVar4 = param_1[2] - *param_1 >> 1;
    uVar1 = 0;
    if (uVar4 <= 0x7fffffff - (uVar4 >> 1)) {
      uVar1 = (uVar4 >> 1) + uVar4;
    }
    if (uVar3 <= uVar1) {
      uVar3 = uVar1;
    }
    FUN_0043c9b0(param_1,uVar3);
  }
  return;
}


