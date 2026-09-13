// FUN_0044b780 @ 0044b780 size=94 callers=1

void __fastcall FUN_0044b780(int param_1)

{
  char local_20 [8];
  undefined1 local_18 [8];
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0047e6ae;
  local_10 = ExceptionList;
  local_8 = 0;
  local_20[0] = '\0';
  ExceptionList = &local_10;
  FUN_004381d0(local_18,'\0');
  local_8 = 1;
  FUN_00408760(*(int *)(param_1 + 4),local_20);
  FUN_00434820(local_20);
  ExceptionList = local_10;
  return;
}


