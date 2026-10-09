// FUN_0040f7a0 @ 0040f7a0 size=422 callers=16

/* WARNING: Removing unreachable block (ram,0x0040f8a8) */

bool __fastcall FUN_0040f7a0(int param_1,int *param_2)

{
  int iVar1;
  HANDLE pvVar2;
  DWORD DVar3;
  int *piVar4;
  undefined1 uVar5;
  void *in_stack_ffffff80;
  char local_60 [8];
  undefined8 local_58;
  undefined1 local_50 [8];
  undefined8 local_48;
  char local_40 [16];
  char local_30 [16];
  char local_20 [8];
  int local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047a59e;
  local_10 = ExceptionList;
  iVar1 = *(int *)ThreadLocalStoragePointer;
  ExceptionList = &local_10;
  local_18 = param_1;
  if ((*(uint *)(iVar1 + 0x14) & 1) == 0) {
    ExceptionList = &local_10;
    *(uint *)(iVar1 + 0x14) = *(uint *)(iVar1 + 0x14) | 1;
    pvVar2 = CreateEventA((LPSECURITY_ATTRIBUTES)0x0,0,0,(LPCSTR)0x0);
    *(HANDLE *)(iVar1 + 0x10) = pvVar2;
  }
  DVar3 = WaitForSingleObject(*(HANDLE *)(iVar1 + 0x10),0);
  if (DVar3 == 0) {
    local_60[0] = '\0';
    local_58 = 0;
    FUN_00451110(local_60,(uint *)"evtVar");
    local_8 = 0;
    local_50[0] = 0;
    local_48 = 0;
    FUN_00451110(local_50,(uint *)"`event` in runInThreadSync");
    local_8 = 1;
    FUN_00434b50(local_30,local_60,local_40,'\x01','\x02');
    local_8 = CONCAT31(local_8._1_3_,3);
    _eh_vector_destructor_iterator_(local_60,0x10,2,FUN_00434820);
    local_8 = 4;
    FUN_00434b50(local_40,local_30,local_20,'\x01','\x02');
    local_8 = CONCAT31(local_8._1_3_,5);
                    /* WARNING: Ignoring partial resolution of indirect */
    uVar5 = 0;
    FUN_0043ace0(&stack0xffffff80,(uint *)"nonSignaledEvt",0xe);
    FUN_00408c90(local_40,in_stack_ffffff80);
    FUN_00434820(local_40);
    local_8 = 0xffffffff;
    _eh_vector_destructor_iterator_(local_30,0x10,1,FUN_00434820);
  }
  piVar4 = FUN_0040f6b0(local_18,param_2,*(WPARAM *)(iVar1 + 0x10));
  if (piVar4 != (int *)0x0) {
    DVar3 = WaitForSingleObject(*(HANDLE *)(iVar1 + 0x10),5000);
    if (DVar3 != 0) {
      *(undefined1 *)(piVar4 + 10) = 0;
    }
    ExceptionList = local_10;
    return DVar3 == 0;
  }
  ExceptionList = local_10;
  return false;
}


