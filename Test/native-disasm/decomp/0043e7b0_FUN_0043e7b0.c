// FUN_0043e7b0 @ 0043e7b0 size=122 callers=2

void __thiscall FUN_0043e7b0(void *this,int *param_1,int *param_2)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = *param_2;
  *(int *)param_2[1] = *param_2;
  *(int *)(*param_2 + 4) = param_2[1];
  *(int *)((int)this + 4) = *(int *)((int)this + 4) + -1;
  piVar2 = param_2 + 2;
  if ((HANDLE)param_2[8] != (HANDLE)0x0) {
    CloseHandle((HANDLE)param_2[8]);
  }
  if (7 < (uint)param_2[7]) {
    FUN_00402430((void *)*piVar2,param_2[7] + 1,2);
  }
  param_2[7] = 7;
  param_2[6] = 0;
  if (7 < (uint)param_2[7]) {
    piVar2 = (int *)*piVar2;
  }
  *(undefined2 *)piVar2 = 0;
  FID_conflict__free(param_2);
  *param_1 = iVar1;
  return;
}


