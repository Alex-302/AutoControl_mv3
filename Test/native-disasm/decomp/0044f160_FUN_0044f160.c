// FUN_0044f160 @ 0044f160 size=240 callers=1

void * __thiscall
FUN_0044f160(void *this,undefined4 param_1,char *param_2,int param_3,int param_4,int param_5)

{
  undefined4 uVar1;
  char *pcVar2;
  uint uVar3;
  char local_30 [8];
  undefined8 local_28;
  uint local_1c;
  char *local_18 [2];
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004791a6;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  uVar1 = FUN_004383a0(&param_2,(int *)&stack0x00000018);
  if ((char)uVar1 == '\0') {
    local_18[0] = "YaBrowser";
    do {
      pcVar2 = FUN_00433bc0(&param_2);
      local_8 = 0;
      local_30[0] = '\0';
      local_28 = 0;
      FUN_00451340(local_30,local_18);
      uVar3 = FUN_004441e0(pcVar2,local_30);
      FUN_00434820(local_30);
      local_8 = 0xffffffff;
      if ((char)uVar3 != '\0') break;
      if (*param_2 == '\x01') {
        local_1c = local_1c & 0xffffff00;
        FUN_00447660(&param_3);
      }
      else if (*param_2 == '\x02') {
        param_4 = param_4 + 0x10;
      }
      else {
        param_5 = param_5 + 1;
      }
      uVar1 = FUN_004383a0(&param_2,(int *)&stack0x00000018);
    } while ((char)uVar1 == '\0');
  }
  *(char **)this = param_2;
  *(ulonglong *)((int)this + 4) = CONCAT44(param_4,param_3);
  *(int *)((int)this + 0xc) = param_5;
  ExceptionList = local_10;
  return this;
}


