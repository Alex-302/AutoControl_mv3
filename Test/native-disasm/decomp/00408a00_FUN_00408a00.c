// FUN_00408a00 @ 00408a00 size=566 callers=5

char * __fastcall FUN_00408a00(undefined4 param_1,int param_2)

{
  undefined1 uVar1;
  LONG LVar2;
  undefined ***_Memory;
  char *pcVar3;
  uint uVar4;
  undefined4 *puVar5;
  DWORD DVar6;
  BOOL BVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  char in_stack_00000014;
  undefined4 in_stack_0000001c;
  undefined4 in_stack_00000020;
  undefined **local_94;
  undefined1 *local_90;
  HANDLE *local_8c;
  undefined ***local_70;
  uint local_6c;
  char local_64 [8];
  undefined8 local_5c;
  undefined1 local_54 [8];
  undefined8 local_4c;
  tagMSG local_44;
  undefined4 local_20;
  undefined8 local_1c;
  HANDLE local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_004799e6;
  local_10 = ExceptionList;
  local_1c = CONCAT44(param_1,(undefined4)local_1c);
  local_20 = 0;
  local_8 = 0;
  ExceptionList = &local_10;
  local_14 = CreateEventA((LPSECURITY_ATTRIBUTES)0x0,0,0,(LPCSTR)0x0);
  local_8c = &local_14;
  local_90 = &stack0x00000014;
  local_94 = &PTR_LAB_0048e4d8;
  local_70 = &local_94;
  uVar4 = FUN_00463ef1();
  uVar8 = 0;
  uVar9 = 0;
  local_64[0] = '\0';
  local_5c = 0;
  local_6c = uVar4;
  FUN_00450f50(local_64,(int)&local_94);
  local_54[0] = 0;
  local_4c = CONCAT44(uVar9,uVar8);
  FUN_00450f50(local_54,uVar4);
  local_8._0_1_ = 3;
  FUN_00434b50(&local_44.wParam,local_64,(char *)&local_44,'\x01','\x02');
  local_8._0_1_ = 4;
  puVar5 = FUN_00440e70(&stack0x00000004,(uint *)"callback");
  uVar1 = *(undefined1 *)puVar5;
  *(undefined1 *)puVar5 = (undefined1)local_44.wParam;
  DVar6 = puVar5[2];
  LVar2 = puVar5[3];
  puVar5[2] = local_44.time;
  puVar5[3] = local_44.pt.x;
  local_44.wParam._0_1_ = uVar1;
  local_44.time = DVar6;
  local_44.pt.x = LVar2;
  FUN_00434820((char *)&local_44.wParam);
  local_8 = CONCAT31(local_8._1_3_,2);
  _eh_vector_destructor_iterator_(local_64,0x10,2,FUN_00434820);
  FUN_00408600(param_2,&stack0x00000004);
  DAT_004a23d6 = 1;
  DVar6 = MsgWaitForMultipleObjects(1,&local_14,0,8000,0x40);
  while (DVar6 == 1) {
    BVar7 = PeekMessageA(&local_44,(HWND)0x0,0x84,0x84,1);
    if (BVar7 != 0) {
      DispatchMessageA(&local_44);
    }
    DVar6 = MsgWaitForMultipleObjects(1,&local_14,0,8000,0x40);
  }
  local_6c = 0xffffffff;
  DAT_004a23d6 = 0;
  CloseHandle(local_14);
  _Memory = local_70;
  pcVar3 = local_1c._4_4_;
  local_1c = 0;
  *pcVar3 = in_stack_00000014;
  *(undefined4 *)(pcVar3 + 8) = in_stack_0000001c;
  *(undefined4 *)(pcVar3 + 0xc) = in_stack_00000020;
  in_stack_0000001c = 0;
  in_stack_00000014 = '\0';
  in_stack_00000020 = 0;
  if (local_70 != (undefined ***)0x0) {
    local_1c = (ulonglong)(local_70 != &local_94) << 0x20;
    if (*local_70 == &PTR_LAB_0048e4d8) {
      *local_70 = &PTR_LAB_0048e4d8;
      *_Memory = &PTR_FUN_0048ed18;
      if (_Memory != &local_94) {
        FID_conflict__free(_Memory);
      }
    }
    else {
      (*(code *)(*local_70)[4])(local_70 != &local_94);
    }
    local_70 = (undefined ***)0x0;
  }
  FUN_00434820(&stack0x00000004);
  FUN_00434820(&stack0x00000014);
  ExceptionList = local_10;
  return pcVar3;
}


