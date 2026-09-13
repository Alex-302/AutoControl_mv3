// FUN_004445e0 @ 004445e0 size=103 callers=1

void __thiscall FUN_004445e0(void *this,int *param_1,int *param_2)

{
  int iVar1;
  void *pvVar2;
  
  iVar1 = *param_2;
  *(int *)param_2[1] = *param_2;
  *(int *)(*param_2 + 4) = param_2[1];
  *(int *)((int)this + 4) = *(int *)((int)this + 4) + -1;
  pvVar2 = (void *)param_2[3];
  if (pvVar2 != (void *)0x0) {
    FUN_00402430(pvVar2,param_2[5] - (int)pvVar2 >> 1,2);
    param_2[3] = 0;
    param_2[4] = 0;
    param_2[5] = 0;
  }
  FID_conflict__free(param_2);
  *param_1 = iVar1;
  return;
}


