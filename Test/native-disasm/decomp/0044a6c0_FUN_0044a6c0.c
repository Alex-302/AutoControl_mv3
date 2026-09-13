// FUN_0044a6c0 @ 0044a6c0 size=103 callers=2

int * __thiscall FUN_0044a6c0(void *this,int *param_1,undefined4 param_2,undefined4 *param_3)

{
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = (undefined4 *)*DAT_004a2f94;
  iVar2 = FUN_004550b0(puVar1,(undefined4 *)puVar1[1],this,param_3);
  if (DAT_004a2f98 != 0x6666665) {
    DAT_004a2f98 = DAT_004a2f98 + 1;
    puVar1[1] = iVar2;
    **(int **)(iVar2 + 4) = iVar2;
    FUN_0044f990(&DAT_004a2f90,param_1,(ushort *)((int *)*DAT_004a2f94 + 2),(int *)*DAT_004a2f94);
    return param_1;
  }
                    /* WARNING: Subroutine does not return */
  FUN_00458ec4("list<T> too long");
}


