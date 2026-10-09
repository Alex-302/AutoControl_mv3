// FUN_00433d40 @ 00433d40 size=192 callers=2

void __thiscall FUN_00433d40(void *this,char *param_1,char *param_2)

{
  byte *pbVar1;
  char *pcVar2;
  undefined4 local_64 [10];
  undefined4 local_3c [6];
  char local_24 [20];
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047da18;
  local_10 = ExceptionList;
  if (((*(char *)this == '\x01') && ((int)param_2 - (int)param_1 >> 4 == 2)) && (*param_1 == '\x03')
     ) {
    ExceptionList = &local_10;
    FUN_00440d90(param_1,local_3c);
    local_8 = 0;
    pbVar1 = FUN_00440d10(local_64,local_3c,param_1 + 0x10);
    local_8 = CONCAT31(local_8._1_3_,1);
    FUN_00439b80(this,pbVar1);
    FUN_004357f0(local_64);
    FUN_004061c0(local_3c);
    ExceptionList = local_10;
    return;
  }
  ExceptionList = &local_10;
  pcVar2 = FUN_00434b50(local_24,param_1,param_2,'\x01','\x02');
  local_8 = 2;
  FUN_00433e10(this,pcVar2);
  FUN_00434820(local_24);
  ExceptionList = local_10;
  return;
}


