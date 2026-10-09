// FUN_00432710 @ 00432710 size=175 callers=2

void __thiscall FUN_00432710(void *this,int *param_1,int *param_2)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = (*(uint *)((int)this + 0x18) &
          ((((*(byte *)(param_2 + 2) ^ 0x811c9dc5) * 0x1000193 ^ (uint)*(byte *)((int)param_2 + 9))
            * 0x1000193 ^ (uint)*(byte *)((int)param_2 + 10)) * 0x1000193 ^
          (uint)*(byte *)((int)param_2 + 0xb)) * 0x1000193) * 8;
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
  iVar1 = *param_2;
  *(int *)param_2[1] = iVar1;
  *(int *)(*param_2 + 4) = param_2[1];
  *(int *)((int)this + 8) = *(int *)((int)this + 8) + -1;
  if ((undefined4 *)param_2[4] != (undefined4 *)0x0) {
    (*(code *)**(undefined4 **)param_2[4])(1);
  }
  FID_conflict__free(param_2);
  *param_1 = iVar1;
  return;
}


