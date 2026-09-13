// FUN_004268a0 @ 004268a0 size=138 callers=1

void __cdecl FUN_004268a0(undefined1 *param_1,char *param_2)

{
  bool bVar1;
  byte local_11 [5];
  UINT local_c;
  uint local_8;
  
  local_11[1] = 0;
  local_11[2] = 0;
  local_11[3] = 0;
  local_11[4] = 0;
  FUN_00453610(param_2,(char *)local_11);
  local_c = 8;
  local_8 = 0;
  SystemParametersInfoA(0x48,8,&local_c,0);
  bVar1 = local_8 != 0;
  if ((bool)local_11[0] != bVar1) {
    local_8 = (uint)local_11[0];
    SystemParametersInfoA(0x49,local_c,&local_c,0);
  }
  local_c = CONCAT31(local_c._1_3_,bVar1);
  *(undefined8 *)(param_1 + 8) = 0;
  *(UINT *)(param_1 + 8) = local_c;
  *param_1 = 4;
  *(uint *)(param_1 + 0xc) = local_8;
  return;
}


