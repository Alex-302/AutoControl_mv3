// FUN_00423ec0 @ 00423ec0 size=263 callers=1

void __fastcall FUN_00423ec0(undefined4 *param_1)

{
  char cVar1;
  ushort uVar2;
  char *pcVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  uint uVar7;
  char local_24 [8];
  undefined4 local_1c;
  undefined4 uStack_18;
  undefined4 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004791a6;
  local_10 = ExceptionList;
  pcVar3 = (char *)*param_1;
  cVar1 = *pcVar3;
  uVar4 = *(undefined4 *)(pcVar3 + 8);
  uVar5 = *(undefined4 *)(pcVar3 + 0xc);
  ExceptionList = &local_10;
  *pcVar3 = '\0';
  pcVar3[8] = '\0';
  pcVar3[9] = '\0';
  pcVar3[10] = '\0';
  pcVar3[0xb] = '\0';
  pcVar3[0xc] = '\0';
  pcVar3[0xd] = '\0';
  pcVar3[0xe] = '\0';
  pcVar3[0xf] = '\0';
  local_24[0] = DAT_004a26c8;
  local_1c = DAT_004a26d0;
  uStack_18 = DAT_004a26d4;
  DAT_004a26c8 = cVar1;
  DAT_004a26d0 = uVar4;
  DAT_004a26d4 = uVar5;
  local_14 = param_1;
  FUN_00434820(local_24);
  puVar6 = local_14;
  uVar2 = *(ushort *)local_14[2];
  DAT_004a26c4 = 0;
  DAT_004a26b4 = GetTickCount();
  uVar7 = FUN_00413390((uint)uVar2,'\x01');
  *(bool *)puVar6[1] = uVar7 != 0;
  local_8 = 0;
  local_24[0] = '\0';
  FUN_004381d0(&local_1c,'\0');
  uVar5 = DAT_004a26d4;
  uVar4 = DAT_004a26d0;
  cVar1 = DAT_004a26c8;
  DAT_004a26c8 = local_24[0];
  local_24[0] = cVar1;
  DAT_004a26d0 = local_1c;
  DAT_004a26d4 = uStack_18;
  _local_1c = CONCAT44(uVar5,uVar4);
  FUN_00434820(local_24);
  ExceptionList = local_10;
  return;
}


