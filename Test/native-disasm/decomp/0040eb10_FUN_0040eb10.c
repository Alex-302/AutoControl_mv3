// FUN_0040eb10 @ 0040eb10 size=613 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

HWND __fastcall FUN_0040eb10(HWND param_1,HWND param_2)

{
  HRESULT HVar1;
  HWND pHVar2;
  int iVar3;
  int *piVar4;
  uint *puVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  void *pvVar8;
  uint uVar9;
  char local_80 [8];
  undefined8 local_78;
  undefined1 local_70 [8];
  undefined8 local_68;
  void *local_60 [2];
  char local_58 [12];
  uint local_4c;
  undefined4 local_48;
  int iStack_44;
  uint uStack_40;
  undefined4 uStack_3c;
  HRESULT local_34;
  HWND local_30;
  HWND local_2c;
  undefined4 local_28;
  int *local_24;
  undefined1 *puStack_20;
  void *local_1c;
  undefined1 *puStack_18;
  undefined4 local_14;
  
  puStack_20 = &stack0xfffffffc;
  local_14 = 0xffffffff;
  puStack_18 = &LAB_0047a3f0;
  local_1c = ExceptionList;
  local_28 = 0;
  pvVar8 = (void *)0x40eb5a;
  ExceptionList = &local_1c;
  local_30 = param_1;
  local_2c = param_2;
  HVar1 = CoInitializeEx((LPVOID)0x0,2);
  local_14 = 1;
  param_1[4].unused = 0;
  param_1[5].unused = 0;
  param_1[5].unused = 7;
  param_1[4].unused = 0;
  pHVar2 = param_1;
  if (7 < (uint)param_1[5].unused) {
    pHVar2 = (HWND)param_1->unused;
  }
  *(undefined2 *)&pHVar2->unused = 0;
  local_28 = 1;
  local_34 = HVar1;
  FUN_0040e150(&local_24,local_2c);
  local_14._0_1_ = 2;
  if (local_24 != (int *)0x0) {
    uVar9 = 0x40ebc0;
    local_2c = (HWND)FUN_0040bee0(local_60,(int *)&local_24);
    if (param_1 != local_2c) {
      if (7 < (uint)param_1[5].unused) {
        pvVar8 = (void *)param_1->unused;
        FUN_00402430(pvVar8,param_1[5].unused + 1,2);
      }
      param_1[5].unused = 7;
      param_1[4].unused = 0;
      pHVar2 = param_1;
      if (7 < (uint)param_1[5].unused) {
        pHVar2 = (HWND)param_1->unused;
      }
      *(undefined2 *)&pHVar2->unused = 0;
      uVar9 = 0x40ec0d;
      FUN_0043a920(param_1,(uint *)local_2c);
    }
    local_14._0_1_ = 2;
    if (7 < local_4c) {
      uVar9 = local_4c + 1;
      FUN_00402430(local_60[0],uVar9,2);
      pvVar8 = local_60[0];
    }
    iVar3 = FUN_0043a250(param_1,pvVar8,uVar9,4);
    if (iVar3 != -1) {
      local_48 = 0;
      iStack_44 = 0;
      uStack_40 = 0;
      uStack_3c = 0;
      if (local_24 != (int *)0x0) {
        (**(code **)(*local_24 + 0x38))
                  (local_24,_DAT_0048e618,_UNK_0048e61c,_UNK_0048e620,_UNK_0048e624,&local_48);
      }
      if ((uStack_40 & 4) != 0) {
        uVar6 = 0;
        uVar7 = 0;
        local_80[0] = '\0';
        local_78 = 0;
        FUN_00450f50(local_80,0x123);
        local_70[0] = 0;
        local_68 = CONCAT44(uVar7,uVar6);
        FUN_00450f50(local_70,0x523);
        local_14._0_1_ = 4;
        FUN_00434b50(local_58,local_80,(char *)local_60,'\x01','\x02');
        local_14._0_1_ = 5;
        piVar4 = FUN_0040c190(&iStack_44,local_58,0xd6c18935,'\0');
        SendInput((piVar4[1] - *piVar4) / 0x1c,(LPINPUT)*piVar4,0x1c);
        FUN_00432b50(&iStack_44);
        FUN_00434820(local_58);
        local_14._0_1_ = 2;
        _eh_vector_destructor_iterator_(local_80,0x10,2,FUN_00434820);
        Sleep(0x14);
        puVar5 = FUN_0040bee0(local_60,(int *)&local_24);
        param_1 = local_30;
        FUN_004351b0(local_30,puVar5);
        FUN_00435170(local_60);
      }
    }
  }
  local_14 = CONCAT31(local_14._1_3_,6);
  if (local_24 != (int *)0x0) {
    (**(code **)(*local_24 + 8))(local_24);
  }
  if (-1 < HVar1) {
    CoUninitialize();
  }
  ExceptionList = local_1c;
  return param_1;
}


