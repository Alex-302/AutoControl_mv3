// FUN_00407480 @ 00407480 size=804 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint __fastcall FUN_00407480(HANDLE param_1,undefined4 param_2)

{
  UINT UVar1;
  uint uVar2;
  int iVar3;
  uint extraout_EAX;
  int iVar4;
  undefined2 uVar5;
  uint uVar6;
  ushort *puVar7;
  void *in_stack_ffffff78;
  char local_68 [8];
  undefined8 local_60;
  undefined1 local_58 [8];
  undefined8 local_50;
  char local_48 [16];
  char local_38 [16];
  uint local_28;
  int local_24;
  uint local_20;
  undefined4 local_1c;
  uint local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004796b6;
  local_10 = ExceptionList;
  local_28 = 10000;
  ExceptionList = &local_10;
  local_1c = param_2;
  UVar1 = GetRawInputDeviceInfoA(param_1,0x20000005,&DAT_0049fc78,&local_28);
  if (UVar1 == 0xffffffff) {
    uVar2 = 0xffffffff;
    if (DAT_0049d9e4 != '\0') {
      DAT_0049d9e4 = '\0';
      local_68[0] = '\0';
      local_60 = 0;
      FUN_00450f70(local_68,(uint *)"neededBufferSize");
      local_58[0] = 0;
      local_50 = 0;
      FUN_00451040(local_58,local_28);
      local_8 = 0;
      FUN_00434b50(local_38,local_68,local_48,'\x01','\x02');
      local_8 = CONCAT31(local_8._1_3_,2);
      _eh_vector_destructor_iterator_(local_68,0x10,2,FUN_00434820);
      local_8 = 3;
      FUN_00434b50(local_48,local_38,(char *)&local_28,'\x01','\x02');
      local_8 = CONCAT31(local_8._1_3_,4);
      FUN_004355e0(&stack0xffffff78,(uint *)"joyBufferTooSmall");
      FUN_00408c90(local_48,in_stack_ffffff78);
      FUN_00434820(local_48);
      local_8 = 0xffffffff;
      _eh_vector_destructor_iterator_(local_38,0x10,1,FUN_00434820);
      uVar2 = extraout_EAX;
    }
  }
  else {
    local_14 = 10;
    uVar2 = HidP_GetButtonCaps();
    if (uVar2 == 0x110000) {
      local_18 = 0x20;
      uVar2 = HidP_GetUsages(0,DAT_004a2b70);
      if (uVar2 == 0x110000) {
        uVar2 = 0;
        _DAT_004a2e66 = 0;
        uRam004a2e6a = 0;
        uRam004a2e6e = 0;
        uRam004a2e72 = 0;
        _DAT_004a2e76 = 0;
        uRam004a2e7a = 0;
        uRam004a2e7e = 0;
        ram0x004a2e82 = 0;
        if (local_18 != 0) {
          do {
            puVar7 = &DAT_004a2f50 + uVar2;
            uVar2 = uVar2 + 1;
            (&DAT_004a2e66)[(uint)*puVar7 - (uint)DAT_004a2ba8] = 1;
          } while (uVar2 < local_18);
        }
        local_14 = 0xb;
        uVar2 = HidP_GetValueCaps();
        if (uVar2 == 0x110000) {
          uVar2 = 0;
          local_20 = 0;
          if ((short)local_14 != 0) {
            puVar7 = &DAT_004a3008;
            do {
              if ((0x2f < *puVar7) && (*puVar7 < 0x3a)) {
                uVar2 = HidP_GetUsageValue(0,puVar7[-0x1c]);
                if (uVar2 != 0x110000) goto LAB_00407792;
                iVar3 = *(int *)(puVar7 + -8);
                local_24 = (*(int *)(puVar7 + -6) - iVar3) + 1;
                uVar2 = (DAT_004a2e8c - local_24 / 2) - iVar3;
                uVar6 = (int)uVar2 >> 0x1f;
                if (*puVar7 == 0x39) {
                  _DAT_004a2e62 = 0;
                  if ((iVar3 <= DAT_004a2e8c) && (DAT_004a2e8c <= *(int *)(puVar7 + -6))) {
                    if (0 < (int)uVar2) {
                      _DAT_004a2e62 = 0xffff;
                    }
                    if (((int)uVar2 < 0) && (iVar3 - local_24 / 2 < (int)uVar2)) {
                      _DAT_004a2e62 = 1;
                    }
                    iVar4 = (uVar2 ^ uVar6) - uVar6;
                    iVar3 = (int)(local_24 + (local_24 >> 0x1f & 3U)) >> 2;
                    if (iVar3 < iVar4) {
                      _DAT_004a2e62 = CONCAT22(0xffff,_DAT_004a2e62);
                    }
                    if (iVar4 < iVar3) {
                      _DAT_004a2e62 = CONCAT22(1,_DAT_004a2e62);
                    }
                  }
                }
                else {
                  uVar5 = 0;
                  if (1 < (int)((uVar2 ^ uVar6) - uVar6)) {
                    uVar5 = (undefined2)uVar2;
                  }
                  *(undefined2 *)(&DAT_004a2df0 + (uint)*puVar7 * 2) = uVar5;
                }
              }
              local_20 = local_20 + 1;
              puVar7 = puVar7 + 0x24;
              uVar2 = local_14 & 0xffff;
            } while (local_20 < uVar2);
          }
          ExceptionList = local_10;
          return CONCAT31((int3)(uVar2 >> 8),1);
        }
      }
    }
  }
LAB_00407792:
  ExceptionList = local_10;
  return uVar2 & 0xffffff00;
}


