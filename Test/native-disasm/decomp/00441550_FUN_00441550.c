// FUN_00441550 @ 00441550 size=197 callers=1

int __fastcall FUN_00441550(void *param_1)

{
  undefined4 uVar1;
  int iVar2;
  void *this;
  undefined4 local_28;
  char *local_24;
  undefined8 local_20;
  int local_18;
  char *local_14;
  undefined8 local_10;
  int local_8;
  
  FUN_004340a0(param_1,&local_24);
  FUN_00434120(this,&local_14);
  FUN_0044f160(&local_14,local_28,local_14,(int)local_10,(int)((ulonglong)local_10 >> 0x20),local_8)
  ;
  local_24 = local_14;
  local_18 = local_8;
  local_20 = local_10;
  FUN_004340a0(param_1,&local_14);
  uVar1 = FUN_004383a0(&local_24,(int *)&local_14);
  if ((char)uVar1 != '\0') {
    return -1;
  }
  FUN_00434120(param_1,&local_14);
  iVar2 = FUN_00444160(&local_24,(int)&local_14);
  return iVar2;
}


