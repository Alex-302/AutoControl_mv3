// FUN_0040ee50 @ 0040ee50 size=261 callers=5

void __fastcall FUN_0040ee50(HWND param_1)

{
  int *piVar1;
  char *extraout_ECX;
  char local_3c [16];
  undefined1 local_2c [8];
  undefined8 local_24;
  void *local_1c;
  undefined4 local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047a44b;
  local_10 = ExceptionList;
  local_2c[0] = 0;
  local_24 = 0;
  ExceptionList = &local_10;
  FUN_00450f50(local_2c,0x40c);
  local_8 = 0;
  FUN_00434b50(local_3c,extraout_ECX,(char *)&local_1c,'\x01','\x02');
  local_8 = CONCAT31(local_8._1_3_,1);
  piVar1 = FUN_0040c190((int *)&local_1c,local_3c,0xd6c18935,'\0');
  SendInput((piVar1[1] - *piVar1) / 0x1c,(LPINPUT)*piVar1,0x1c);
  if (local_1c != (void *)0x0) {
    FUN_00402430(local_1c,(local_14 - (int)local_1c) / 0x1c,0x1c);
    local_1c = (void *)0x0;
    local_18 = 0;
    local_14 = 0;
  }
  FUN_00434820(local_3c);
  local_8 = 0xffffffff;
  _eh_vector_destructor_iterator_(local_2c,0x10,1,FUN_00434820);
  SetForegroundWindow(param_1);
  ExceptionList = local_10;
  return;
}


