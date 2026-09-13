// FUN_0044a660 @ 0044a660 size=92 callers=1

int * __thiscall FUN_0044a660(void *this,int *param_1,undefined4 param_2,undefined4 *param_3)

{
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = (undefined4 *)**(undefined4 **)((int)this + 4);
  iVar2 = FUN_00455080(puVar1,(undefined4 *)puVar1[1],this,param_3);
  if (*(int *)((int)this + 8) != 0x4924923) {
    *(int *)((int)this + 8) = *(int *)((int)this + 8) + 1;
    puVar1[1] = iVar2;
    **(int **)(iVar2 + 4) = iVar2;
    FUN_0044f7e0(this,param_1,(byte *)((int *)**(undefined4 **)((int)this + 4) + 2),
                 (int *)**(undefined4 **)((int)this + 4));
    return param_1;
  }
                    /* WARNING: Subroutine does not return */
  FUN_00458ec4("list<T> too long");
}


