// FUN_00448720 @ 00448720 size=139 callers=1

int * __thiscall FUN_00448720(void *this,int *param_1,int *param_2)

{
  int *piVar1;
  uint uVar2;
  
  uVar2 = *(uint *)((int)this + 0x18) &
          ((((*(byte *)(param_2 + 2) ^ 0x811c9dc5) * 0x1000193 ^ (uint)*(byte *)((int)param_2 + 9))
            * 0x1000193 ^ (uint)*(byte *)((int)param_2 + 10)) * 0x1000193 ^
          (uint)*(byte *)((int)param_2 + 0xb)) * 0x1000193;
  piVar1 = (int *)(*(int *)((int)this + 0xc) + uVar2 * 8);
  if (*(int **)(*(int *)((int)this + 0xc) + 4 + uVar2 * 8) == param_2) {
    if ((int *)*piVar1 == param_2) {
      *piVar1 = *(int *)((int)this + 4);
      *(undefined4 *)(*(int *)((int)this + 0xc) + 4 + uVar2 * 8) = *(undefined4 *)((int)this + 4);
    }
    else {
      piVar1[1] = param_2[1];
    }
  }
  else if ((int *)*piVar1 == param_2) {
    *piVar1 = *param_2;
  }
  FUN_00448c60((void *)((int)this + 4),param_1,param_2);
  return param_1;
}


