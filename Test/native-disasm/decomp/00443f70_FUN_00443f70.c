// FUN_00443f70 @ 00443f70 size=268 callers=2

char * __thiscall FUN_00443f70(void *this,char *param_1)

{
  undefined4 uVar1;
  char *pcVar2;
  bool bVar3;
  char local_50 [8];
  undefined1 local_48 [8];
  char local_40 [8];
  undefined4 local_38;
  undefined4 local_34;
  char local_30 [8];
  undefined4 local_28;
  undefined4 local_24;
  undefined8 local_20;
  undefined4 local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047e26e;
  local_10 = ExceptionList;
  local_18 = 0;
  ExceptionList = &local_10;
  uVar1 = FUN_00445a10((void *)((int)this + 0x34));
  *(undefined4 *)((int)this + 0x30) = uVar1;
  FUN_00444920(this,local_30,1);
  local_8 = 0;
  FUN_004446b0(this,0xf);
  bVar3 = local_30[0] != '\b';
  if (bVar3) {
    local_38 = local_28;
    local_34 = local_24;
    local_28 = 0;
    local_40[0] = local_30[0];
    pcVar2 = local_40;
    local_30[0] = '\0';
    local_24 = 0;
  }
  else {
    local_8 = CONCAT31(local_8._1_3_,1);
    local_50[0] = '\0';
    FUN_004381d0(local_48,'\0');
    pcVar2 = local_50;
  }
  local_20 = 0;
  *param_1 = *pcVar2;
  *(undefined4 *)(param_1 + 8) = *(undefined4 *)(pcVar2 + 8);
  *(undefined4 *)(param_1 + 0xc) = *(undefined4 *)(pcVar2 + 0xc);
  *pcVar2 = '\0';
  pcVar2[8] = '\0';
  pcVar2[9] = '\0';
  pcVar2[10] = '\0';
  pcVar2[0xb] = '\0';
  pcVar2[0xc] = '\0';
  pcVar2[0xd] = '\0';
  pcVar2[0xe] = '\0';
  pcVar2[0xf] = '\0';
  if (bVar3) {
    FUN_00434820(local_40);
  }
  else {
    FUN_00434820(local_50);
  }
  FUN_00434820(local_30);
  ExceptionList = local_10;
  return param_1;
}


