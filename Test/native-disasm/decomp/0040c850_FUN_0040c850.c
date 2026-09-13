// FUN_0040c850 @ 0040c850 size=198 callers=2

UINT __fastcall FUN_0040c850(undefined4 *param_1,char param_2)

{
  char *pcVar1;
  int *piVar2;
  UINT UVar3;
  char local_2c [16];
  void *local_1c;
  undefined4 local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047a018;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  pcVar1 = FUN_0040c790(local_2c,param_1,param_2);
  local_8 = 0;
  piVar2 = FUN_0040c190((int *)&local_1c,pcVar1,0xd6c18935,'\0');
  UVar3 = SendInput((piVar2[1] - *piVar2) / 0x1c,(LPINPUT)*piVar2,0x1c);
  if (local_1c != (void *)0x0) {
    FUN_00402430(local_1c,(local_14 - (int)local_1c) / 0x1c,0x1c);
    local_1c = (void *)0x0;
    local_18 = 0;
    local_14 = 0;
  }
  FUN_00434820(local_2c);
  ExceptionList = local_10;
  return UVar3;
}


