// FUN_004473e0 @ 004473e0 size=127 callers=1

void FUN_004473e0(uint *param_1,int param_2)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  
  uVar2 = param_2 - (int)param_1;
  DAT_004a3370 = (uint *)0x0;
  uVar3 = (int)uVar2 >> 1;
  DAT_004a3374 = (uint *)0x0;
  DAT_004a3378 = 0;
  if (uVar3 != 0) {
    if (0x7fffffff < uVar3) {
                    /* WARNING: Subroutine does not return */
      FUN_00458ec4("vector<T> too long");
    }
    puVar1 = FUN_0043ec70(uVar3);
    DAT_004a3378 = (int)puVar1 + uVar3 * 2;
    DAT_004a3370 = puVar1;
    DAT_004a3374 = puVar1;
    FUN_0045b0e0(puVar1,param_1,uVar2);
    DAT_004a3374 = (uint *)(uVar2 + (int)puVar1);
  }
  return;
}


