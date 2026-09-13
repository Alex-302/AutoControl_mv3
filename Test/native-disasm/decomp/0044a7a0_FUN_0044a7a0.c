// FUN_0044a7a0 @ 0044a7a0 size=103 callers=1

int * __thiscall FUN_0044a7a0(void *this,int *param_1,undefined4 param_2,undefined4 *param_3)

{
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = (undefined4 *)*DAT_004a27b4;
  iVar2 = FUN_00455190(puVar1,(undefined4 *)puVar1[1],this,param_3);
  if (DAT_004a27b8 != 0x3c3c3c2) {
    DAT_004a27b8 = DAT_004a27b8 + 1;
    puVar1[1] = iVar2;
    **(int **)(iVar2 + 4) = iVar2;
    FUN_0044aad0(&DAT_004a27b0,param_1,(byte *)((int *)*DAT_004a27b4 + 2),(int *)*DAT_004a27b4);
    return param_1;
  }
                    /* WARNING: Subroutine does not return */
  FUN_00458ec4("list<T> too long");
}


