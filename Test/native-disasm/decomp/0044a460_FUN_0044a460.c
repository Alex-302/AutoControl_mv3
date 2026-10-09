// FUN_0044a460 @ 0044a460 size=103 callers=1

int * __thiscall FUN_0044a460(void *this,int *param_1,undefined4 param_2,undefined4 *param_3)

{
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = (undefined4 *)*DAT_004a3324;
  iVar2 = FUN_00454f80(puVar1,(undefined4 *)puVar1[1],this,param_3);
  if (DAT_004a3328 != 0x5d1745c) {
    DAT_004a3328 = DAT_004a3328 + 1;
    puVar1[1] = iVar2;
    **(int **)(iVar2 + 4) = iVar2;
    FUN_0044aad0(&DAT_004a3320,param_1,(byte *)((int *)*DAT_004a3324 + 2),(int *)*DAT_004a3324);
    return param_1;
  }
                    /* WARNING: Subroutine does not return */
  FUN_00458ec4("list<T> too long");
}


