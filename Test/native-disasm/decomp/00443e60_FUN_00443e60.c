// FUN_00443e60 @ 00443e60 size=94 callers=1

void __fastcall FUN_00443e60(int *param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  if (param_1[2] - param_1[1] >> 3 == 0) {
    iVar2 = param_1[1] - *param_1 >> 3;
    if (iVar2 == 0x1fffffff) {
                    /* WARNING: Subroutine does not return */
      FUN_00458ec4("vector<T> too long");
    }
    uVar3 = iVar2 + 1;
    uVar4 = param_1[2] - *param_1 >> 3;
    uVar1 = 0;
    if (uVar4 <= 0x1fffffff - (uVar4 >> 1)) {
      uVar1 = (uVar4 >> 1) + uVar4;
    }
    if (uVar3 <= uVar1) {
      uVar3 = uVar1;
    }
    FUN_00444650(param_1,uVar3);
  }
  return;
}


