// FUN_0040c920 @ 0040c920 size=400 callers=4

int * __fastcall FUN_0040c920(int *param_1)

{
  char cVar1;
  int *piVar2;
  undefined4 extraout_EDX;
  undefined4 uVar3;
  undefined4 uVar4;
  char local_64 [8];
  undefined8 local_5c;
  undefined1 local_54 [8];
  undefined8 local_4c;
  char local_44 [20];
  void *local_30;
  undefined4 local_2c;
  int local_28;
  undefined2 *local_24;
  int local_20;
  int local_1c;
  undefined4 local_18;
  int *local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047a053;
  local_10 = ExceptionList;
  local_18 = 0;
  ExceptionList = &local_10;
  local_14 = param_1;
  FUN_0040c5e0((uint *)&local_24);
  local_8 = 0;
  if ((local_20 - (int)local_24 >> 1 == 1) &&
     ((((cVar1 = (char)*local_24, cVar1 == '[' || (cVar1 == '\\')) || (cVar1 == -0x5c)) ||
      (cVar1 == -0x5b)))) {
    uVar3 = 0;
    uVar4 = 0;
    local_64[0] = '\0';
    local_5c = 0;
    FUN_00450f50(local_64,0xa0);
    local_54[0] = 0;
    local_4c = CONCAT44(uVar4,uVar3);
    FUN_00450f50(local_54,0x4a0);
    local_8._0_1_ = 1;
    FUN_00434b50(local_44,local_64,local_44,'\x01','\x02');
    local_8 = CONCAT31(local_8._1_3_,2);
    piVar2 = FUN_0040c190((int *)&local_30,local_44,0xd6c18935,'\0');
    SendInput((piVar2[1] - *piVar2) / 0x1c,(LPINPUT)*piVar2,0x1c);
    if (local_30 != (void *)0x0) {
      FUN_00402430(local_30,(local_28 - (int)local_30) / 0x1c,0x1c);
      local_30 = (void *)0x0;
      local_2c = 0;
      local_28 = 0;
    }
    FUN_00434820(local_44);
    local_8 = local_8 & 0xffffff00;
    _eh_vector_destructor_iterator_(local_64,0x10,2,FUN_00434820);
  }
  FUN_0040c850(&local_24,'\0');
  FUN_004335f0(param_1,extraout_EDX,(int *)&local_24);
  if (local_24 != (undefined2 *)0x0) {
    FUN_00402430(local_24,local_1c - (int)local_24 >> 1,2);
  }
  ExceptionList = local_10;
  return param_1;
}


