// FUN_0042ed90 @ 0042ed90 size=167 callers=1

undefined4 __cdecl FUN_0042ed90(undefined1 *param_1,char *param_2)

{
  uint uVar1;
  LRESULT LVar2;
  WPARAM wParam;
  undefined4 extraout_ECX;
  char local_24 [8];
  undefined8 local_1c;
  char *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_004791a6;
  local_10 = ExceptionList;
  local_14 = "monOff";
  local_8 = 0;
  local_24[0] = '\0';
  local_1c = 0;
  ExceptionList = &local_10;
  FUN_00451340(local_24,&local_14);
  uVar1 = FUN_004441e0(param_2,local_24);
  FUN_00434820(local_24);
  wParam = 0xf140;
  if ((char)uVar1 != '\0') {
    wParam = 0xf170;
  }
  LVar2 = SendMessageA(*(HWND *)(&DAT_004a2470 + DAT_004a23dc * 4),0x112,wParam,2);
  *param_1 = 0;
  *(undefined8 *)(param_1 + 8) = 0;
  FUN_00450f50(param_1,LVar2);
  ExceptionList = local_10;
  return extraout_ECX;
}


