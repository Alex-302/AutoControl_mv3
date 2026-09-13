// FUN_0044a810 @ 0044a810 size=103 callers=1

int * __thiscall FUN_0044a810(void *this,int *param_1,undefined4 param_2,undefined4 *param_3)

{
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = (undefined4 *)*DAT_004a2804;
  iVar2 = FUN_00454f20(puVar1,(undefined4 *)puVar1[1],this,param_3);
  if (DAT_004a2808 != 0xffffffe) {
    DAT_004a2808 = DAT_004a2808 + 1;
    puVar1[1] = iVar2;
    **(int **)(iVar2 + 4) = iVar2;
    FUN_0044aad0(&DAT_004a2800,param_1,(byte *)((int *)*DAT_004a2804 + 2),(int *)*DAT_004a2804);
    return param_1;
  }
                    /* WARNING: Subroutine does not return */
  FUN_00458ec4("list<T> too long");
}


