// FUN_00428470 @ 00428470 size=181 callers=1

undefined1 * __cdecl FUN_00428470(undefined1 *param_1,void *param_2)

{
  char *pcVar1;
  undefined4 *puVar2;
  int iVar3;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004791a6;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  pcVar1 = (char *)FUN_00440e70(param_2,(uint *)"iTime");
  FUN_00453810(pcVar1,&local_14);
  DAT_004a23d8 = local_14;
  pcVar1 = (char *)FUN_00440e70(param_2,(uint *)"crVer");
  FUN_00453810(pcVar1,&local_14);
  DAT_004a23a4 = local_14;
  puVar2 = FUN_00440e70(param_2,(uint *)"variant");
  iVar3 = FUN_00441550(puVar2);
  if (-1 < iVar3) {
    PTR_s_Chrome__0049da10 = s_YandexBrowser__0048d1cc;
    PTR_s_Chrome_WidgetWin__0049d9f8 = s_YandexBrowser_WidgetWin__0048d1dc;
  }
  local_8 = 0;
  *param_1 = 0;
  FUN_004381d0(param_1 + 8,'\0');
  ExceptionList = local_10;
  return param_1;
}


