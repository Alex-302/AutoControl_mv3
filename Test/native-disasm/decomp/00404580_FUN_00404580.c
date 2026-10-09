// FUN_00404580 @ 00404580 size=50 callers=16

LPSTR __fastcall FUN_00404580(LPSTR param_1,LPCWSTR param_2,uint param_3)

{
  LPCWSTR pWVar1;
  
  pWVar1 = param_2 + 8;
  if (7 < *(uint *)(param_2 + 10)) {
    param_2 = *(LPCWSTR *)param_2;
  }
  FUN_004044f0(param_1,param_2,*(int *)pWVar1 + 1,param_3);
  return param_1;
}


