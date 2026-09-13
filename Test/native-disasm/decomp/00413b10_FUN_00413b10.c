// FUN_00413b10 @ 00413b10 size=445 callers=1

void __fastcall FUN_00413b10(char *param_1)

{
  char cVar1;
  int *piVar2;
  char *pcVar3;
  char *extraout_ECX;
  char *extraout_ECX_00;
  undefined **local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined ***local_6c;
  char local_68 [16];
  char local_58 [16];
  char local_48 [8];
  undefined8 local_40;
  char local_38 [8];
  undefined8 local_30;
  int local_28 [3];
  int local_1c;
  undefined4 local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0047ac01;
  local_10 = ExceptionList;
  cVar1 = *param_1;
  if (1 < *(uint *)(&DAT_004a2468 + cVar1 * 4)) {
    local_88 = *(undefined4 *)(&DAT_004a23b0 + cVar1 * 4);
    local_18 = CONCAT31(local_18._1_3_,cVar1);
    local_8c = local_18;
    local_6c = &local_90;
    local_90 = &PTR_LAB_0048f0a0;
    local_8 = 0;
    ExceptionList = &local_10;
    FUN_0040fd50(500,(int *)local_6c);
    if (local_6c != (undefined ***)0x0) {
      (*(code *)(*local_6c)[4])(local_6c != &local_90);
    }
    if (*param_1 == '\x01') {
      local_38[0] = '\0';
      local_30 = 0;
      FUN_00450f50(local_38,0x401);
      local_8 = 1;
      FUN_00434b50(local_58,extraout_ECX,(char *)local_28,'\x01','\x02');
      local_8 = CONCAT31(local_8._1_3_,2);
      piVar2 = FUN_0040c190(&local_1c,local_58,0xd6c18936,'\0');
      SendInput((piVar2[1] - *piVar2) / 0x1c,(LPINPUT)*piVar2,0x1c);
      FUN_00432b50(&local_1c);
      FUN_00434820(local_58);
      pcVar3 = local_38;
    }
    else {
      local_48[0] = '\0';
      local_40 = 0;
      FUN_00450f50(local_48,0x4ff);
      local_8 = 3;
      FUN_00434b50(local_68,extraout_ECX_00,local_38,'\x01','\x02');
      local_8 = CONCAT31(local_8._1_3_,4);
      piVar2 = FUN_0040c190(local_28,local_68,0xd6c18935,'\0');
      SendInput((piVar2[1] - *piVar2) / 0x1c,(LPINPUT)*piVar2,0x1c);
      FUN_00432b50(local_28);
      FUN_00434820(local_68);
      pcVar3 = local_48;
    }
    local_8 = 0xffffffff;
    _eh_vector_destructor_iterator_(pcVar3,0x10,1,FUN_00434820);
  }
  ExceptionList = local_10;
  return;
}


