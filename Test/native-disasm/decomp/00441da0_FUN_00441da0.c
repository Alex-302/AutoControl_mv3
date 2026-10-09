// FUN_00441da0 @ 00441da0 size=111 callers=2

int * FUN_00441da0(int *param_1,undefined4 *param_2,void *param_3)

{
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = (undefined4 *)*DAT_004a28e4;
  iVar2 = FUN_0044f2d0(puVar1,(undefined4 *)puVar1[1],param_2,param_3);
  if (DAT_004a28e8 != 0x6666665) {
    DAT_004a28e8 = DAT_004a28e8 + 1;
    puVar1[1] = iVar2;
    **(int **)(iVar2 + 4) = iVar2;
    FUN_00446ee0(&DAT_004a28e0,param_1,(byte *)((int *)*DAT_004a28e4 + 2),(int *)*DAT_004a28e4);
    return param_1;
  }
                    /* WARNING: Subroutine does not return */
  FUN_00458ec4("list<T> too long");
}


