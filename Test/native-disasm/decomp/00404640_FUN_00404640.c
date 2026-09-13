// FUN_00404640 @ 00404640 size=46 callers=17

LPWSTR __fastcall FUN_00404640(LPWSTR param_1,LPCSTR param_2)

{
  int *piVar1;
  
  piVar1 = (int *)(param_2 + 0x10);
  if (0xf < *(uint *)(param_2 + 0x14)) {
    param_2 = *(LPCSTR *)param_2;
  }
  FUN_004045c0(param_1,param_2,*piVar1 + 1);
  return param_1;
}


