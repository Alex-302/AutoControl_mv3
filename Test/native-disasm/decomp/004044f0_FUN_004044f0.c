// FUN_004044f0 @ 004044f0 size=132 callers=9

LPSTR __fastcall FUN_004044f0(LPSTR param_1,LPCWSTR param_2,int param_3,uint param_4)

{
  int iVar1;
  LPSTR lpMultiByteStr;
  
  iVar1 = WideCharToMultiByte(0xfde9,0,param_2,param_3,(LPSTR)0x0,0,(LPCSTR)0x0,(LPBOOL)0x0);
  param_1[0x14] = '\x0f';
  param_1[0x15] = '\0';
  param_1[0x16] = '\0';
  param_1[0x17] = '\0';
  if (iVar1 - 1U < param_4) {
    param_4 = iVar1 - 1U;
  }
  param_1[0x10] = '\0';
  param_1[0x11] = '\0';
  param_1[0x12] = '\0';
  param_1[0x13] = '\0';
  *param_1 = '\0';
  FUN_0043ac10(param_1,param_4,'\0');
  lpMultiByteStr = param_1;
  if (0xf < *(uint *)(param_1 + 0x14)) {
    lpMultiByteStr = *(LPSTR *)param_1;
  }
  WideCharToMultiByte(0xfde9,0,param_2,param_3,lpMultiByteStr,*(int *)(param_1 + 0x10) + 1,
                      (LPCSTR)0x0,(LPBOOL)0x0);
  return param_1;
}


