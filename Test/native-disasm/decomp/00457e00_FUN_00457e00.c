// FUN_00457e00 @ 00457e00 size=123 callers=1

void __thiscall FUN_00457e00(void *this,undefined4 *param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  int iVar2;
  int local_10 [3];
  
  while( true ) {
    if (param_1 == param_2) {
      return;
    }
    puVar1 = (undefined4 *)**(undefined4 **)((int)this + 4);
    iVar2 = FUN_00458430(puVar1,(undefined4 *)puVar1[1],param_1 + 2);
    if (*(int *)((int)this + 8) == 0x71c71c6) break;
    *(int *)((int)this + 8) = *(int *)((int)this + 8) + 1;
    puVar1[1] = iVar2;
    **(int **)(iVar2 + 4) = iVar2;
    FUN_0044f420(this,local_10,(byte *)((int *)**(undefined4 **)((int)this + 4) + 2),
                 (int *)**(undefined4 **)((int)this + 4));
    param_1 = (undefined4 *)*param_1;
  }
                    /* WARNING: Subroutine does not return */
  FUN_00458ec4("list<T> too long");
}


