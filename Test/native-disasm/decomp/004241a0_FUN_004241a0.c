// FUN_004241a0 @ 004241a0 size=75 callers=1

undefined4 __cdecl FUN_004241a0(undefined1 *param_1,void *param_2)

{
  char *pcVar1;
  int iVar2;
  undefined4 extraout_ECX;
  HWND local_10;
  undefined4 local_c;
  
  local_c = 0;
  pcVar1 = (char *)FUN_00440e70(param_2,(uint *)&DAT_0048d814);
  FUN_004536b0(pcVar1,(uint *)&local_10);
  iVar2 = FUN_0040ee50(local_10);
  *param_1 = 0;
  *(undefined8 *)(param_1 + 8) = 0;
  FUN_00450f50(param_1,iVar2);
  return extraout_ECX;
}


