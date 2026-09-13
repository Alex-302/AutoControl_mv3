// FUN_00404220 @ 00404220 size=438 callers=5

uint * __fastcall FUN_00404220(uint *param_1,char *param_2)

{
  char *pcVar1;
  char cVar2;
  char cVar3;
  byte bVar4;
  byte ****ppppbVar5;
  byte ****ppppbVar6;
  uint uVar7;
  char *pcVar8;
  byte ***local_38 [4];
  uint local_28;
  uint local_24;
  undefined4 local_20;
  uint *local_1c;
  char *local_18;
  char local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004792a8;
  local_10 = ExceptionList;
  local_20 = 0;
  local_1c = param_1;
  if (*(int *)(param_2 + 0x10) == 0) {
    ExceptionList = &local_10;
    param_1[5] = 0xf;
    param_1[4] = 0;
    *(undefined1 *)param_1 = 0;
    FUN_0043ade0(param_1,(undefined4 *)param_2,0,0xffffffff);
    ExceptionList = local_10;
    return param_1;
  }
  local_24 = 0xf;
  local_28 = 0;
  local_38[0] = (byte ***)((uint)local_38[0] & 0xffffff00);
  ExceptionList = &local_10;
  FUN_0043ac10(local_38,((uint)(*(int *)(param_2 + 0x10) * 3) >> 2) + 4,'\0');
  local_8 = 0;
  pcVar8 = param_2;
  if (0xf < *(uint *)(param_2 + 0x14)) {
    pcVar8 = *(char **)param_2;
  }
  pcVar8 = pcVar8 + *(int *)(param_2 + 0x10) + -1;
  ppppbVar6 = local_38;
  if (0xf < local_24) {
    ppppbVar6 = (byte ****)local_38[0];
  }
  local_18 = pcVar8;
  if (0xf < *(uint *)(param_2 + 0x14)) {
    param_2 = *(char **)param_2;
  }
  while (ppppbVar5 = ppppbVar6, param_2 <= pcVar8) {
    cVar2 = *param_2;
    local_11 = PTR_s_>____456789__<_________0048e5f8[param_2[1] + -0x2b];
    cVar3 = PTR_s_>____456789__<_________0048e5f8[param_2[2] + -0x2b];
    pcVar1 = param_2 + 3;
    param_2 = param_2 + 4;
    bVar4 = PTR_s_>____456789__<_________0048e5f8[*pcVar1 + -0x2b];
    uVar7 = CONCAT11(local_11,local_11 >> 4) & 0xffffff03;
    *(byte *)ppppbVar6 = (byte)uVar7 | PTR_s_>____456789__<_________0048e5f8[cVar2 + -0x2b] << 2;
    ppppbVar5 = (byte ****)((int)ppppbVar6 + 1);
    param_1 = local_1c;
    if (cVar3 == '@') break;
    uVar7 = CONCAT11((char)(uVar7 >> 8) << 4,cVar3 >> 2) & 0xffffff0f;
    *(byte *)ppppbVar5 = (byte)uVar7 | (byte)(uVar7 >> 8);
    ppppbVar5 = (byte ****)((int)ppppbVar6 + 2);
    param_1 = local_1c;
    if (bVar4 == 0x40) break;
    *(byte *)ppppbVar5 = bVar4 & 0x3f | cVar3 << 6;
    ppppbVar6 = (byte ****)((int)ppppbVar6 + 3);
    param_1 = local_1c;
  }
  ppppbVar6 = local_38;
  if (0xf < local_24) {
    ppppbVar6 = (byte ****)local_38[0];
  }
  uVar7 = (int)ppppbVar5 - (int)ppppbVar6;
  if (local_28 < uVar7) {
    FUN_0043aef0(local_38,uVar7 - local_28,'\0');
  }
  else {
    ppppbVar6 = local_38;
    if (0xf < local_24) {
      ppppbVar6 = (byte ****)local_38[0];
    }
    local_28 = uVar7;
    *(byte *)((int)ppppbVar6 + uVar7) = 0;
  }
  param_1[5] = 0xf;
  param_1[4] = 0;
  *(undefined1 *)param_1 = 0;
  if (local_24 < 0x10) {
    if (local_28 + 1 != 0) {
      FUN_0045b0e0(param_1,(uint *)local_38,local_28 + 1);
    }
  }
  else {
    *param_1 = (uint)local_38[0];
  }
  param_1[4] = local_28;
  param_1[5] = local_24;
  ExceptionList = local_10;
  return param_1;
}


