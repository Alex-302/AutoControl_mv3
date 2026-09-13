// FUN_004045c0 @ 004045c0 size=116 callers=1

LPWSTR __fastcall FUN_004045c0(LPWSTR param_1,LPCSTR param_2,int param_3)

{
  int iVar1;
  LPWSTR lpWideCharStr;
  
  iVar1 = MultiByteToWideChar(0xfde9,0,param_2,param_3,(LPWSTR)0x0,0);
  param_1[10] = L'\a';
  param_1[0xb] = L'\0';
  param_1[8] = L'\0';
  param_1[9] = L'\0';
  *param_1 = L'\0';
  FUN_0043a5b0(param_1,iVar1 - 1,0);
  lpWideCharStr = param_1;
  if (7 < *(uint *)(param_1 + 10)) {
    lpWideCharStr = *(LPWSTR *)param_1;
  }
  MultiByteToWideChar(0xfde9,0,param_2,param_3,lpWideCharStr,*(int *)(param_1 + 8) + 1);
  return param_1;
}


