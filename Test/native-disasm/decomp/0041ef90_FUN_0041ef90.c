// FUN_0041ef90 @ 0041ef90 size=1009 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __fastcall FUN_0041ef90(ushort param_1,HMENU param_2)

{
  char cVar1;
  uint *puVar2;
  HRESULT HVar3;
  LPDATAOBJECT pDataObj;
  undefined1 auStack_144 [8];
  undefined4 uStack_13c;
  char local_11c [16];
  undefined1 local_10c [16];
  undefined1 local_fc [16];
  undefined1 local_ec [16];
  char local_dc [28];
  undefined1 *local_c0;
  char local_bc [8];
  undefined8 local_b4;
  undefined1 local_ac [8];
  undefined8 local_a4;
  char local_9c [8];
  undefined8 local_94;
  undefined1 local_8c [8];
  undefined8 local_84;
  char local_7c [8];
  undefined8 local_74;
  undefined1 local_6c [8];
  undefined8 local_64;
  char local_5c [8];
  undefined8 local_54;
  undefined1 local_4c [8];
  undefined8 local_44;
  LPDROPSOURCE local_3c;
  byte local_38 [4];
  char local_34 [16];
  undefined4 local_24;
  LPDATAOBJECT local_18;
  char local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047b9e7;
  local_10 = ExceptionList;
  _DAT_0049da5c = DAT_0048e600;
  ExceptionList = &local_10;
  puVar2 = FUN_0041d6a0((void *)((int)&local_54 + 4),param_2,param_1);
  DAT_004a2520 = *puVar2;
  uRam004a2524 = puVar2[1];
  DAT_004a2528 = puVar2[2];
  DAT_004a252c = puVar2[3];
  _DAT_004a2530 = puVar2[4];
  if ((((DAT_004a2520 != 0) && (cVar1 = (char)(DAT_004a252c >> 0x10), cVar1 != '\x01')) &&
      (cVar1 != '\x02')) && (cVar1 != '\x03')) {
    HVar3 = OleInitialize((LPVOID)0x0);
    if (-1 < HVar3) {
      FUN_0041e810();
      FUN_00419e40((undefined4 *)local_dc,DAT_004a2520);
      local_8 = 0;
      local_34[0xc] = '\0';
      local_34[0xd] = '\0';
      local_34[0xe] = '\0';
      local_34[0xf] = '\0';
      local_34[0] = '\0';
      local_34[1] = '\0';
      local_34[2] = '\0';
      local_34[3] = '\0';
      local_34[4] = '\0';
      local_34[5] = '\0';
      local_34[6] = '\0';
      local_34[7] = '\0';
      local_34[8] = '\0';
      local_34[9] = '\0';
      local_34[10] = '\0';
      local_34[0xb] = '\0';
      local_24 = (uint)local_24._2_2_ << 0x10;
      DAT_004a29d4 = 0;
      DAT_004a29d8 = 0;
      DAT_004a29dc = 0;
      DAT_004a29e0 = 0;
      _DAT_004a29e4 = local_24;
      local_18 = operator_new(0x20);
      local_8._0_1_ = 1;
      pDataObj = FUN_0041d790(local_18,(undefined4 *)local_dc);
      local_8._0_1_ = 2;
      local_18 = pDataObj;
      local_3c = operator_new(8);
      local_3c[1].lpVtbl = (IDropSourceVtbl *)0x1;
      local_3c->lpVtbl = (IDropSourceVtbl *)&PTR_FUN_0048e38c;
      local_8._0_1_ = 3;
      DAT_004a2444 = 1;
      HVar3 = DoDragDrop(pDataObj,local_3c,3,(LPDWORD)local_38);
      DAT_004a2444 = 0;
      OleUninitialize();
      if (((HVar3 == 0) || (HVar3 == 0x40100)) &&
         ((DAT_004a29e5 != '\0' && ((local_38[0] & 2) != 0)))) {
        local_5c[0] = '\0';
        local_54 = 0;
        FUN_00451110(local_5c,(uint *)"srcItmId");
        local_4c[0] = 0;
        local_44 = 0;
        FUN_00451040(local_4c,DAT_004a2520);
        local_8._0_1_ = 4;
        FUN_00434b50(local_11c,local_5c,(char *)&local_3c,'\x01','\x02');
        local_8._0_1_ = 6;
        _eh_vector_destructor_iterator_(local_5c,0x10,2,FUN_00434820);
        local_7c[0] = '\0';
        local_74 = 0;
        FUN_00451110(local_7c,(uint *)"tgtItmId");
        local_6c[0] = 0;
        local_64 = 0;
        FUN_00451040(local_6c,DAT_004a29d4);
        local_8._0_1_ = 7;
        FUN_00434b50(local_10c,local_7c,local_5c,'\x01','\x02');
        local_8._0_1_ = 9;
        _eh_vector_destructor_iterator_(local_7c,0x10,2,FUN_00434820);
        local_9c[0] = '\0';
        local_94 = 0;
        FUN_00451110(local_9c,(uint *)"tgtParentId");
        local_8c[0] = 0;
        local_84 = 0;
        FUN_00451040(local_8c,DAT_004a29d8);
        local_8._0_1_ = 10;
        FUN_00434b50(local_fc,local_9c,local_7c,'\x01','\x02');
        local_8._0_1_ = 0xc;
        _eh_vector_destructor_iterator_(local_9c,0x10,2,FUN_00434820);
        local_bc[0] = '\0';
        local_b4 = 0;
        FUN_00451110(local_bc,(uint *)"insertPos");
        local_ac[0] = 0;
        local_a4 = 0;
        FUN_004511e0(local_ac,DAT_004a29e4);
        local_8._0_1_ = 0xd;
        FUN_00434b50(local_ec,local_bc,local_9c,'\x01','\x02');
        local_8._0_1_ = 0xf;
        _eh_vector_destructor_iterator_(local_bc,0x10,2,FUN_00434820);
        local_c0 = &stack0xfffffecc;
        local_8._0_1_ = 0x11;
        uStack_13c = 0x41f2cc;
        FUN_004381d0(&stack0xfffffed4,'\0');
        local_8._0_1_ = 0x12;
        FUN_00434b50(auStack_144,local_11c,local_dc,'\x01','\x02');
        local_8._0_1_ = 0x10;
        FUN_00408a00(local_34,0x30e);
        local_8._0_1_ = 0x14;
        _eh_vector_destructor_iterator_(local_11c,0x10,4,FUN_00434820);
        if (local_34[0] == '\x04') {
          FUN_00453610(local_34,&local_11);
          if (local_11 != '\0') {
            FUN_0041ebf0();
          }
        }
        FUN_00434820(local_34);
      }
      FUN_00431de0(&local_3c);
      FUN_00431e40(&local_18);
      FUN_004061c0((undefined4 *)local_dc);
      ExceptionList = local_10;
      return 0;
    }
  }
  DAT_004a2437 = 1;
  ExceptionList = local_10;
  return 0;
}


