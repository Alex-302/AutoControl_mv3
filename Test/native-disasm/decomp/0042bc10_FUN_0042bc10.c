// FUN_0042bc10 @ 0042bc10 size=524 callers=1

undefined1 * __cdecl FUN_0042bc10(undefined1 *param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  char *this;
  undefined **local_44;
  undefined1 local_40;
  void *local_34 [4];
  undefined4 local_24;
  undefined ***local_20;
  int *local_1c;
  int *local_18;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0047cc76;
  local_10 = ExceptionList;
  local_20 = &local_44;
  local_14 = 0;
  local_44 = &PTR_LAB_0048eb24;
  local_8 = 0;
  ExceptionList = &local_10;
  FUN_0040f7a0(DAT_004a2458,(int *)local_20);
  if (local_20 != (undefined ***)0x0) {
    (*(code *)(*local_20)[4])(local_20 != &local_44);
  }
  local_40 = DAT_0049fc44;
  local_20 = &local_44;
  local_44 = &PTR_LAB_0048ed80;
  local_8 = 1;
  FUN_0040f6b0(DAT_004a23dc,(int *)local_20,0);
  local_8 = 0xffffffff;
  if (local_20 != (undefined ***)0x0) {
    (*(code *)(*local_20)[4])(local_20 != &local_44);
  }
  this = param_2;
  DAT_0049fc44 = 0;
  cVar1 = *param_2;
  pcVar3 = param_2;
  if (cVar1 == '\x04') {
LAB_0042bd48:
    FUN_00453610(pcVar3,(char *)((int)&param_2 + 3));
    DAT_004a26c6 = param_2._3_1_;
    FUN_004073f0(param_2._3_1_);
  }
  else {
    local_20 = (undefined ***)&DAT_0000000f;
    local_24 = 0;
    local_34[0] = (void *)((uint)local_34[0] & 0xffffff00);
    FUN_0043ace0(local_34,(uint *)"regular",7);
    if (*this == '\x01') {
      FUN_004437f0(*(void **)(this + 8),(int *)&local_1c,(byte *)local_34);
      iVar2 = FUN_00447a70(local_1c,local_18);
    }
    else {
      iVar2 = 0;
    }
    if (&DAT_0000000f < local_20) {
      FUN_00402430(local_34[0],(uint)((int)local_20 + 1),1);
    }
    if (iVar2 != 0) {
      pcVar3 = (char *)FUN_00440e70(this,(uint *)"regular");
      goto LAB_0042bd48;
    }
  }
  if (cVar1 != '\x04') {
    local_20 = (undefined ***)&DAT_0000000f;
    local_24 = 0;
    local_34[0] = (void *)((uint)local_34[0] & 0xffffff00);
    FUN_0043ace0(local_34,(uint *)"mouseGest",9);
    if (*this == '\x01') {
      FUN_004437f0(*(void **)(this + 8),(int *)&local_1c,(byte *)local_34);
      iVar2 = FUN_00447a70(local_1c,local_18);
    }
    else {
      iVar2 = 0;
    }
    if (&DAT_0000000f < local_20) {
      FUN_00402430(local_34[0],(uint)((int)local_20 + 1),1);
    }
    if (iVar2 == 0) goto LAB_0042bdf2;
    if (cVar1 != '\x04') {
      this = (char *)FUN_00440e70(this,(uint *)"mouseGest");
    }
  }
  FUN_004536b0(this,(uint *)&param_2);
  DAT_004a264c = param_2._0_1_;
LAB_0042bdf2:
  local_8 = 2;
  *param_1 = 0;
  FUN_004381d0(param_1 + 8,'\0');
  ExceptionList = local_10;
  return param_1;
}


