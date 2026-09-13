// FUN_0042dbf0 @ 0042dbf0 size=681 callers=1

undefined1 * __cdecl FUN_0042dbf0(undefined1 *param_1,char *param_2)

{
  char *this;
  char cVar1;
  LPCSTR pCVar2;
  int iVar3;
  char *pcVar4;
  undefined ***extraout_ECX;
  undefined ***pppuVar5;
  void *local_8c [4];
  undefined4 local_7c;
  uint local_78;
  void *local_74 [4];
  int local_64;
  uint local_60;
  undefined **local_5c;
  char **local_58;
  void *local_4c [4];
  undefined4 local_3c;
  undefined ***local_38;
  void *local_34 [4];
  undefined4 local_24;
  uint local_20;
  undefined4 local_1c;
  int *local_18;
  int *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047d189;
  local_10 = ExceptionList;
  local_1c = 0;
  local_20 = 0xf;
  local_24 = 0;
  local_34[0] = (void *)((uint)local_34[0] & 0xffffff00);
  ExceptionList = &local_10;
  FUN_0043ace0(local_34,(uint *)"exeName",7);
  this = param_2;
  local_8 = 0;
  pCVar2 = (LPCSTR)FUN_004342f0(param_2,local_8c,local_34,(uint *)&DAT_0048e75c);
  local_8 = CONCAT31(local_8._1_3_,1);
  FUN_00404640((LPWSTR)local_74,pCVar2);
  if (0xf < local_78) {
    FUN_00402430(local_8c[0],local_78 + 1,1);
  }
  local_78 = 0xf;
  local_7c = 0;
  local_8c[0] = (void *)((uint)local_8c[0] & 0xffffff00);
  local_8 = CONCAT31(local_8._1_3_,4);
  if (0xf < local_20) {
    FUN_00402430(local_34[0],local_20 + 1,1);
  }
  local_20 = 0xf;
  local_24 = 0;
  local_34[0] = (void *)((uint)local_34[0] & 0xffffff00);
  local_38 = (undefined ***)0xf;
  local_3c = 0;
  local_4c[0] = (void *)((uint)local_4c[0] & 0xffffff00);
  FUN_0043ace0(local_4c,(uint *)"volume",6);
  if (*this == '\x01') {
    FUN_004437f0(*(void **)(this + 8),(int *)&local_18,(byte *)local_4c);
    iVar3 = FUN_00447a70(local_18,local_14);
  }
  else {
    iVar3 = 0;
  }
  if (0xf < local_38) {
    FUN_00402430(local_4c[0],(int)local_38 + 1,1);
  }
  if (iVar3 == 0) {
    local_38 = (undefined ***)&DAT_0000000f;
    local_3c = 0;
    local_4c[0] = (void *)((uint)local_4c[0] & 0xffffff00);
    FUN_0043ace0(local_4c,(uint *)&DAT_0048db20,4);
    local_8._0_1_ = 6;
    cVar1 = FUN_00442460(this,local_4c);
    local_8._0_1_ = 4;
    if (&DAT_0000000f < local_38) {
      FUN_00402430(local_4c[0],(uint)((int)local_38 + 1),1);
    }
    if (local_64 == 0) {
      local_58 = &param_2;
      param_2 = (char *)CONCAT31(param_2._1_3_,cVar1);
      local_38 = &local_5c;
      local_5c = &PTR_LAB_0048e9f0;
      local_8._0_1_ = 7;
      FUN_00427e50((int)local_38);
      if (local_38 != (undefined ***)0x0) {
        (*(code *)(*local_38)[4])(local_38 != &local_5c);
      }
    }
    else {
      FUN_004283b0(local_74,cVar1);
    }
  }
  else {
    pcVar4 = (char *)FUN_00440e70(this,(uint *)"volume");
    FUN_004536b0(pcVar4,(uint *)&param_2);
    local_38 = (undefined ***)&DAT_0000000f;
    local_3c = 0;
    local_4c[0] = (void *)((uint)local_4c[0] & 0xffffff00);
    FUN_0043ace0(local_4c,(uint *)"relative",8);
    local_8._0_1_ = 5;
    cVar1 = FUN_00441100(this,local_4c);
    local_8._0_1_ = 4;
    local_14 = (int *)CONCAT31(local_14._1_3_,cVar1);
    pppuVar5 = local_38;
    if (&DAT_0000000f < local_38) {
      FUN_00402430(local_4c[0],(uint)((int)local_38 + 1),1);
      pppuVar5 = extraout_ECX;
    }
    if (local_64 == 0) {
      FUN_004282a0(CONCAT31((int3)((uint)pppuVar5 >> 8),param_2._0_1_),cVar1);
    }
    else {
      FUN_00428310(local_74,param_2._0_1_);
    }
  }
  local_8 = CONCAT31(local_8._1_3_,8);
  *param_1 = 0;
  FUN_004381d0(param_1 + 8,'\0');
  if (7 < local_60) {
    FUN_00402430(local_74[0],local_60 + 1,2);
  }
  ExceptionList = local_10;
  return param_1;
}


