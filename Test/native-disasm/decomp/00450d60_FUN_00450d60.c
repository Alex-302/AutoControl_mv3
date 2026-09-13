// FUN_00450d60 @ 00450d60 size=106 callers=2

void __thiscall FUN_00450d60(void *this,int *param_1,int *param_2)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = *param_2;
  *(int *)param_2[1] = *param_2;
  *(int *)(*param_2 + 4) = param_2[1];
  *(int *)((int)this + 4) = *(int *)((int)this + 4) + -1;
  piVar2 = param_2 + 2;
  if (0xf < (uint)param_2[7]) {
    FUN_00402430((void *)*piVar2,param_2[7] + 1,1);
  }
  param_2[7] = 0xf;
  param_2[6] = 0;
  if (0xf < (uint)param_2[7]) {
    piVar2 = (int *)*piVar2;
  }
  *(undefined1 *)piVar2 = 0;
  FID_conflict__free(param_2);
  *param_1 = iVar1;
  return;
}


