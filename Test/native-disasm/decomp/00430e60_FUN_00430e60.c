// FUN_00430e60 @ 00430e60 size=609 callers=1

void __fastcall FUN_00430e60(ushort *param_1)

{
  ushort uVar1;
  int *piVar2;
  char *pcVar3;
  char *extraout_ECX;
  char *extraout_ECX_00;
  undefined4 uVar4;
  undefined4 uVar5;
  uint uVar6;
  char local_78 [8];
  undefined8 local_70;
  undefined1 local_68 [8];
  undefined8 local_60;
  char local_58 [16];
  char local_48 [16];
  char local_38 [8];
  undefined8 local_30;
  int local_28 [3];
  void *local_1c;
  undefined4 local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047d771;
  local_10 = ExceptionList;
  if ((DAT_004a23c6 == '\0') || (*param_1 != 2)) {
    uVar1 = *param_1;
    uVar4 = 0;
    uVar5 = 0;
    local_78[0] = '\0';
    local_70 = 0;
    ExceptionList = &local_10;
    FUN_004512e0(local_78,(uint)uVar1);
    local_68[0] = 0;
    local_60 = CONCAT44(uVar5,uVar4);
    FUN_00450f50(local_68,uVar1 | 0x400);
    local_8 = 4;
    FUN_00434b50(local_58,local_78,local_58,'\x01','\x02');
    local_8 = CONCAT31(local_8._1_3_,5);
    piVar2 = FUN_0040c190((int *)&local_1c,local_58,0xd6c18935,'\0');
    SendInput((piVar2[1] - *piVar2) / 0x1c,(LPINPUT)*piVar2,0x1c);
    if (local_1c != (void *)0x0) {
      FUN_00402430(local_1c,(local_14 - (int)local_1c) / 0x1c,0x1c);
      local_1c = (void *)0x0;
      local_18 = 0;
      local_14 = 0;
    }
    FUN_00434820(local_58);
    uVar6 = 2;
    pcVar3 = local_78;
  }
  else {
    local_38[0] = '\0';
    local_30 = 0;
    ExceptionList = &local_10;
    FUN_004512e0(local_38,2);
    local_8 = 0;
    FUN_00434b50(local_48,extraout_ECX,(char *)local_28,'\x01','\x02');
    local_8 = CONCAT31(local_8._1_3_,1);
    piVar2 = FUN_0040c190(local_28,local_48,0xd6c18935,'\0');
    SendInput((piVar2[1] - *piVar2) / 0x1c,(LPINPUT)*piVar2,0x1c);
    FUN_00432b50(local_28);
    FUN_00434820(local_48);
    local_8 = 0xffffffff;
    _eh_vector_destructor_iterator_(local_38,0x10,1,FUN_00434820);
    Sleep(100);
    local_38[0] = '\0';
    local_30 = 0;
    FUN_00450f50(local_38,*param_1 | 0x400);
    local_8 = 2;
    FUN_00434b50(local_48,extraout_ECX_00,(char *)local_28,'\x01','\x02');
    local_8 = CONCAT31(local_8._1_3_,3);
    piVar2 = FUN_0040c190(local_28,local_48,0xd6c18935,'\0');
    SendInput((piVar2[1] - *piVar2) / 0x1c,(LPINPUT)*piVar2,0x1c);
    FUN_00432b50(local_28);
    FUN_00434820(local_48);
    uVar6 = 1;
    pcVar3 = local_38;
  }
  local_8 = 0xffffffff;
  _eh_vector_destructor_iterator_(pcVar3,0x10,uVar6,FUN_00434820);
  ExceptionList = local_10;
  return;
}


