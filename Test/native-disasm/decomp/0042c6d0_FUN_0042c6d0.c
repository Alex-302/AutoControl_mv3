// FUN_0042c6d0 @ 0042c6d0 size=373 callers=1

undefined1 * __cdecl FUN_0042c6d0(undefined1 *param_1,void *param_2)

{
  char *pcVar1;
  uint uVar2;
  int iVar3;
  undefined **local_44;
  uint local_40;
  void *local_34 [2];
  char local_2c [8];
  undefined4 local_24;
  undefined ***local_20;
  undefined4 local_1c;
  uint local_18;
  char local_14 [4];
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047cd64;
  local_10 = ExceptionList;
  local_1c = 0;
  ExceptionList = &local_10;
  pcVar1 = (char *)FUN_00440e70(param_2,(uint *)&DAT_0048d830);
  FUN_004536b0(pcVar1,(uint *)local_14);
  local_20 = (undefined ***)&DAT_0000000f;
  local_24 = 0;
  local_34[0] = (void *)((uint)local_34[0] & 0xffffff00);
  FUN_0043ace0(local_34,(uint *)"callback",8);
  local_8 = 0;
  uVar2 = FUN_004409d0(param_2,local_34,0);
  local_8 = 0xffffffff;
  local_18 = uVar2;
  if (&DAT_0000000f < local_20) {
    FUN_00402430(local_34[0],(uint)((int)local_20 + 1),1);
  }
  if ((local_14[0] != '\x02') && (uVar2 != 0)) {
    iVar3 = 0;
    do {
      if (DAT_004a24f4 == 0) break;
      Sleep(100);
      iVar3 = iVar3 + 1;
    } while (iVar3 < 5);
    uVar2 = local_18;
    local_20 = &local_44;
    local_44 = &PTR_LAB_0048ea38;
    local_40 = local_18;
    local_8 = 1;
    FUN_0040f7a0(DAT_004a23dc,(int *)local_20);
    local_8 = 0xffffffff;
    if (local_20 != (undefined ***)0x0) {
      (*(code *)(*local_20)[4])(local_20 != &local_44);
    }
  }
  FUN_00418490(local_14[0]);
  if ((local_14[0] == '\x02') && (uVar2 != 0)) {
    local_8 = 2;
    local_2c[0] = '\0';
    FUN_004381d0(&local_24,'\0');
    local_8 = 3;
    FUN_00408760(uVar2,local_2c);
    FUN_00434820(local_2c);
  }
  local_8 = 4;
  *param_1 = 0;
  FUN_004381d0(param_1 + 8,'\0');
  ExceptionList = local_10;
  return param_1;
}


