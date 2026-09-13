// FUN_00441e80 @ 00441e80 size=94 callers=1

int * __thiscall FUN_00441e80(void *this,int *param_1,undefined4 *param_2,undefined4 *param_3)

{
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = (undefined4 *)**(undefined4 **)((int)this + 4);
  iVar2 = FUN_0044f360(puVar1,(undefined4 *)puVar1[1],param_2,param_3);
  if (*(int *)((int)this + 8) != 0xffffffe) {
    *(int *)((int)this + 8) = *(int *)((int)this + 8) + 1;
    puVar1[1] = iVar2;
    **(int **)(iVar2 + 4) = iVar2;
    FUN_00447060(this,param_1,(byte *)((int *)**(undefined4 **)((int)this + 4) + 2),
                 (int *)**(undefined4 **)((int)this + 4));
    return param_1;
  }
                    /* WARNING: Subroutine does not return */
  FUN_00458ec4("list<T> too long");
}


