// FUN_0040d260 @ 0040d260 size=403 callers=1

undefined1 * __fastcall FUN_0040d260(undefined1 *param_1,byte *param_2)

{
  byte *pbVar1;
  uint uVar2;
  byte *pbVar3;
  char cVar4;
  undefined4 *this;
  byte *pbVar5;
  void *pvVar6;
  undefined4 local_50;
  undefined1 local_4c;
  void *local_48;
  int iStack_44;
  int iStack_40;
  undefined4 uStack_3c;
  undefined4 local_38;
  undefined1 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined1 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined1 local_1c;
  undefined4 local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047a1a4;
  local_10 = ExceptionList;
  local_18 = 0;
  ExceptionList = &local_10;
  local_14 = param_1;
  if ((*(int *)(*(int *)ThreadLocalStoragePointer + 8) < DAT_004a3300) &&
     (ExceptionList = &local_10, FUN_0045a219(&DAT_004a3300), DAT_004a3300 == -1)) {
    local_8 = 0;
    FUN_00433840(&DAT_004a33b8,"^\\w+\\..+\\.(\\w+)$",0x500);
    _atexit(FUN_0047f250);
    FUN_0045a1da(&DAT_004a3300);
  }
  local_50 = 0;
  local_4c = 0;
  local_48 = (void *)0x0;
  iStack_44 = 0;
  iStack_40 = 0;
  uStack_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_8 = 1;
  uVar2 = *(uint *)(param_2 + 0x14);
  pbVar5 = param_2;
  pbVar3 = param_2;
  if (0xf < uVar2) {
    pbVar5 = *(byte **)param_2;
    pbVar3 = *(byte **)param_2;
  }
  pbVar1 = param_2 + 0x10;
  if (0xf < uVar2) {
    param_2 = *(byte **)param_2;
  }
  cVar4 = FUN_004466f0(&local_50,&DAT_004a33b8,param_2,pbVar5 + *(int *)pbVar1,uVar2,pbVar3);
  pvVar6 = local_48;
  if (cVar4 == '\0') {
    *(undefined4 *)(param_1 + 0x14) = 0xf;
    *(undefined4 *)(param_1 + 0x10) = 0;
    *param_1 = 0;
    FUN_0043ace0(param_1,(uint *)&DAT_0048d20c,4);
    pvVar6 = local_48;
  }
  else {
    this = &local_24;
    if (1 < (uint)((iStack_44 - (int)local_48) / 0xc)) {
      this = (undefined4 *)((int)local_48 + 0xc);
    }
    FUN_00433a80(this,param_1);
  }
  if (pvVar6 != (void *)0x0) {
    FUN_00402430(pvVar6,(iStack_40 - (int)pvVar6) / 0xc,0xc);
  }
  ExceptionList = local_10;
  return param_1;
}


