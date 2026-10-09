// FUN_00442b50 @ 00442b50 size=126 callers=1

void FUN_00442b50(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  int iVar2;
  int local_10 [3];
  
  while( true ) {
    if (param_1 == param_2) {
      return;
    }
    puVar1 = (undefined4 *)*DAT_004a2824;
    iVar2 = FUN_00452ff0(puVar1,(undefined4 *)puVar1[1],param_1);
    if (DAT_004a2828 == 0xffffffe) break;
    DAT_004a2828 = DAT_004a2828 + 1;
    puVar1[1] = iVar2;
    **(int **)(iVar2 + 4) = iVar2;
    FUN_0044aad0(&DAT_004a2820,local_10,(byte *)((int *)*DAT_004a2824 + 2),(int *)*DAT_004a2824);
    param_1 = param_1 + 2;
  }
                    /* WARNING: Subroutine does not return */
  FUN_00458ec4("list<T> too long");
}


