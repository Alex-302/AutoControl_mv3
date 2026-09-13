// FUN_0042fc40 @ 0042fc40 size=213 callers=1

void __thiscall FUN_0042fc40(void *this,char *param_1)

{
  undefined1 *puVar1;
  uint uVar2;
  bool bVar3;
  char local_38 [16];
  char local_28 [16];
  uint local_18;
  char local_11;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047d512;
  local_10 = ExceptionList;
  local_18 = 0;
  ExceptionList = &local_10;
  FUN_00453610(param_1,&local_11);
  bVar3 = local_11 == '\0';
  if (bVar3) {
    puVar1 = FUN_00434a40(local_28,(char *)0x0,(char *)0x0);
    uVar2 = 2;
  }
  else {
    puVar1 = FUN_00416fe0(local_38,*(undefined4 **)((int)this + 4),0x7fffffff);
    uVar2 = 1;
  }
  local_8 = (uint)bVar3;
  local_18 = uVar2;
  FUN_00408760(*(int *)this,puVar1);
  if ((uVar2 & 2) != 0) {
    uVar2 = uVar2 & 0xfffffffd;
    FUN_00434820(local_28);
  }
  local_8 = 0xffffffff;
  if ((uVar2 & 1) != 0) {
    FUN_00434820(local_38);
  }
  FUN_00453610(param_1,&local_11);
  if (local_11 != '\0') {
    DAT_004a2504 = 1;
    FUN_00418360((undefined4 *)((int)this + 8));
  }
  ExceptionList = local_10;
  return;
}


