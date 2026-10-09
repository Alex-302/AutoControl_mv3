// FUN_0044a270 @ 0044a270 size=272 callers=1

void __thiscall FUN_0044a270(void *param_1,char *param_2,undefined8 param_3,int param_4)

{
  uint uVar1;
  void *pvVar2;
  ushort *puVar3;
  int iVar4;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047e630;
  local_10 = ExceptionList;
  iVar4 = (int)((ulonglong)param_3 >> 0x20);
  ExceptionList = &local_10;
  uVar1 = FUN_00452ea0(param_2,(int *)param_3,iVar4,param_4);
  *(undefined4 *)param_1 = 0;
  *(undefined4 *)((int)param_1 + 4) = 0;
  *(undefined4 *)((int)param_1 + 8) = 0;
  if (uVar1 != 0) {
    if (0x7fffffff < uVar1) {
                    /* WARNING: Subroutine does not return */
      FUN_00458ec4("vector<T> too long");
    }
    pvVar2 = FUN_0043ec70(uVar1);
    *(void **)param_1 = pvVar2;
    *(void **)((int)param_1 + 4) = pvVar2;
    local_8 = 0;
    *(uint *)((int)param_1 + 8) = *(int *)param_1 + uVar1 * 2;
    puVar3 = FUN_00455f70(*(void **)param_1,param_2,(int *)param_3,iVar4,param_4);
    *(ushort **)((int)param_1 + 4) = puVar3;
  }
  ExceptionList = local_10;
  return;
}


