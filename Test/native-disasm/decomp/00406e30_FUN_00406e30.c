// FUN_00406e30 @ 00406e30 size=131 callers=1

undefined4 __fastcall FUN_00406e30(undefined4 param_1,int param_2,undefined4 *param_3)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 local_130;
  undefined1 local_12c [296];
  
  local_130 = 0x128;
  _memset(local_12c,0,0x124);
  puVar2 = &local_130;
  puVar3 = param_3;
  for (iVar1 = 0x4a; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  iVar1 = Process32First(param_1,param_3);
  while( true ) {
    if (iVar1 == 0) {
      return 0;
    }
    if (param_3[2] == param_2) break;
    iVar1 = Process32Next(param_1,param_3);
  }
  return CONCAT31((int3)((uint)param_2 >> 8),1);
}


