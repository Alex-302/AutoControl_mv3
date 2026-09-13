// FUN_00443d50 @ 00443d50 size=120 callers=1

int * __thiscall FUN_00443d50(void *this,int *param_1,int *param_2)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = (*(uint *)((int)this + 0x18) &
          ((*(byte *)(param_2 + 2) ^ 0x811c9dc5) * 0x1000193 ^ (uint)*(byte *)((int)param_2 + 9)) *
          0x1000193) * 8;
  piVar2 = (int *)(*(int *)((int)this + 0xc) + iVar1);
  if ((int *)piVar2[1] == param_2) {
    if ((int *)*piVar2 == param_2) {
      *piVar2 = *(int *)((int)this + 4);
      *(undefined4 *)(iVar1 + 4 + *(int *)((int)this + 0xc)) = *(undefined4 *)((int)this + 4);
    }
    else {
      piVar2[1] = param_2[1];
    }
  }
  else if ((int *)*piVar2 == param_2) {
    *piVar2 = *param_2;
  }
  FUN_004445e0((void *)((int)this + 4),param_1,param_2);
  return param_1;
}


