// FUN_00429380 @ 00429380 size=352 callers=1

undefined1 * __cdecl FUN_00429380(undefined1 *param_1,char *param_2)

{
  char cVar1;
  void **ppvVar2;
  uint *puVar3;
  uint uVar4;
  undefined1 local_cc [96];
  void *local_6c [5];
  uint local_58;
  undefined **local_54 [9];
  undefined ***local_30;
  void *local_2c [4];
  undefined4 local_1c;
  uint local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047c8e6;
  local_10 = ExceptionList;
  local_14 = 0;
  cVar1 = *param_2;
  if (cVar1 != '\x03') {
    local_18 = 0xf;
    local_1c = 0;
    local_2c[0] = (void *)((uint)local_2c[0] & 0xffffff00);
    ExceptionList = &local_10;
    FUN_0043ace0(local_2c,(uint *)&DAT_0048e75c,0);
    ppvVar2 = local_2c;
    uVar4 = 2;
  }
  else {
    ExceptionList = &local_10;
    ppvVar2 = (void **)FUN_00440bb0(param_2,local_6c);
    uVar4 = 1;
  }
  local_8 = (uint)(cVar1 != '\x03');
  local_14 = uVar4;
  puVar3 = FUN_00404130(local_cc,(uint *)ppvVar2);
  FUN_004294e0(&DAT_004a2650,puVar3);
  local_8 = 2;
  _eh_vector_destructor_iterator_(local_cc,0x18,4,FUN_004061c0);
  if ((uVar4 & 2) != 0) {
    uVar4 = uVar4 & 0xfffffffd;
    if (0xf < local_18) {
      FUN_00402430(local_2c[0],local_18 + 1,1);
    }
    local_18 = 0xf;
    local_1c = 0;
    local_2c[0] = (void *)((uint)local_2c[0] & 0xffffff00);
  }
  if (((uVar4 & 1) != 0) && (0xf < local_58)) {
    FUN_00402430(local_6c[0],local_58 + 1,1);
  }
  local_30 = local_54;
  local_54[0] = &PTR_LAB_0048e7a0;
  local_8 = 3;
  FUN_0040f6b0(DAT_004a2458,(int *)local_30,0);
  if (local_30 != (undefined ***)0x0) {
    (*(code *)(*local_30)[4])(local_30 != local_54);
  }
  local_8 = 4;
  *param_1 = 0;
  FUN_004381d0(param_1 + 8,'\0');
  ExceptionList = local_10;
  return param_1;
}


