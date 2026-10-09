// FUN_00413cd0 @ 00413cd0 size=1266 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_00413cd0(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  uint uVar4;
  byte *pbVar5;
  UINT UVar6;
  uint uVar7;
  void *this;
  uint *puVar8;
  undefined4 extraout_ECX;
  undefined4 uVar9;
  undefined4 extraout_ECX_00;
  uint *puVar10;
  byte *pbVar11;
  byte *extraout_EDX;
  byte bVar12;
  int *piVar13;
  uint uVar14;
  bool bVar15;
  void *in_stack_ffffff7c;
  char local_60 [8];
  undefined8 local_58;
  undefined1 local_50 [8];
  undefined8 local_48;
  char local_40 [16];
  char local_30 [16];
  byte *local_20;
  byte *local_1c;
  uint local_18;
  byte *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047ac5a;
  local_10 = ExceptionList;
  if (param_1 != -1) {
    if (DAT_004a3390 == 2) {
      ExceptionList = &local_10;
      if ((*(int *)(*(int *)ThreadLocalStoragePointer + 8) < DAT_004a2e90) &&
         (ExceptionList = &local_10, FUN_0045a219(&DAT_004a2e90), DAT_004a2e90 == -1)) {
        local_8 = 0;
        local_14 = (byte *)0x0;
        FUN_00435db0(&local_14);
        _atexit(thunk_FUN_004324a0);
        local_8 = 0xffffffff;
        FUN_0045a1da(&DAT_004a2e90);
      }
      FUN_00448b50(&local_14,(byte *)&DAT_004a3398);
      pbVar11 = local_14;
      if (local_14 == DAT_004a3324) {
        local_14 = (byte *)&DAT_004a3398;
        FUN_0044a460(this,(int *)&local_1c,this,&local_14);
        pbVar11 = local_1c;
      }
      if (_DAT_004a33a0 < 0x21) {
        puVar10 = &DAT_004a33a8;
        puVar8 = (uint *)(pbVar11 + 0xc);
        uVar4 = _DAT_004a33a0;
        while (uVar14 = uVar4 - 4, 3 < uVar4) {
          if (*puVar8 != *puVar10) goto LAB_00413dda;
          puVar8 = puVar8 + 1;
          puVar10 = puVar10 + 1;
          uVar4 = uVar14;
        }
        if (uVar14 != 0xfffffffc) {
LAB_00413dda:
          if (((char)*puVar8 != (char)*puVar10) ||
             ((uVar14 != 0xfffffffd &&
              ((*(char *)((int)puVar8 + 1) != *(char *)((int)puVar10 + 1) ||
               ((uVar14 != 0xfffffffe &&
                ((*(char *)((int)puVar8 + 2) != *(char *)((int)puVar10 + 2) ||
                 ((uVar14 != 0xffffffff &&
                  (*(char *)((int)puVar8 + 3) != *(char *)((int)puVar10 + 3))))))))))))) {
            FUN_0045c870((uint *)(pbVar11 + 0xc),&DAT_004a33a8,_DAT_004a33a0);
            uVar4 = FUN_00407480(DAT_004a3398,&DAT_004a33a0);
            if ((char)uVar4 != '\0') {
              pbVar5 = FUN_00432f70((byte *)&DAT_004a3398);
              piVar13 = &DAT_004a2e50;
              uVar4 = 0x32;
              pbVar11 = pbVar5;
              do {
                if (*(int *)pbVar11 != *piVar13) goto LAB_00413e7d;
                pbVar11 = pbVar11 + 4;
                piVar13 = piVar13 + 1;
                bVar15 = 3 < uVar4;
                uVar4 = uVar4 - 4;
              } while (bVar15);
              if (*(short *)pbVar11 != (short)*piVar13) {
LAB_00413e7d:
                local_14 = pbVar5;
                DAT_004a26b4 = GetMessageTime();
                FUN_004082c0((uint *)&local_20,DAT_004a3398,extraout_ECX,(short *)pbVar5);
                local_8 = 1;
                uVar9 = 0;
                uVar14 = 0;
                uVar4 = (uint)(local_1c + (1 - (int)local_20)) >> 1;
                if (local_1c < local_20) {
                  uVar4 = 0;
                }
                pbVar11 = local_20;
                if (uVar4 != 0) {
                  do {
                    FUN_00413390(CONCAT22((short)((uint)uVar9 >> 0x10),*(undefined2 *)pbVar11),'\0')
                    ;
                    uVar14 = uVar14 + 1;
                    uVar9 = extraout_ECX_00;
                    pbVar11 = pbVar11 + 2;
                  } while (uVar14 != uVar4);
                }
                FUN_004335b0(&local_20);
                uVar3 = uRam004a2e5c;
                uVar2 = _DAT_004a2e58;
                uVar9 = DAT_004a2e54;
                *(undefined4 *)local_14 = DAT_004a2e50;
                *(undefined4 *)(local_14 + 4) = uVar9;
                *(undefined4 *)(local_14 + 8) = uVar2;
                *(undefined4 *)(local_14 + 0xc) = uVar3;
                uVar3 = uRam004a2e6c;
                uVar2 = uRam004a2e68;
                uVar9 = _DAT_004a2e64;
                *(undefined4 *)(local_14 + 0x10) = _DAT_004a2e60;
                *(undefined4 *)(local_14 + 0x14) = uVar9;
                *(undefined4 *)(local_14 + 0x18) = uVar2;
                *(undefined4 *)(local_14 + 0x1c) = uVar3;
                uVar3 = uRam004a2e7c;
                uVar2 = uRam004a2e78;
                uVar9 = uRam004a2e74;
                *(undefined4 *)(local_14 + 0x20) = _DAT_004a2e70;
                *(undefined4 *)(local_14 + 0x24) = uVar9;
                *(undefined4 *)(local_14 + 0x28) = uVar2;
                *(undefined4 *)(local_14 + 0x2c) = uVar3;
                *(undefined4 *)(local_14 + 0x30) = DAT_004a2e80;
                *(undefined2 *)(local_14 + 0x34) = DAT_004a2e84;
                ExceptionList = local_10;
                return;
              }
            }
          }
        }
      }
      else if (DAT_0049d9c4 != '\0') {
        DAT_0049d9c4 = 0;
        local_60[0] = '\0';
        local_58 = 0;
        FUN_00450f70(local_60,(uint *)"neededBufferSize");
        local_50[0] = 0;
        local_48 = 0;
        FUN_00451040(local_50,_DAT_004a33a0);
        local_8 = 2;
        FUN_00434b50(local_30,local_60,local_40,'\x01','\x02');
        local_8 = CONCAT31(local_8._1_3_,4);
        _eh_vector_destructor_iterator_(local_60,0x10,2,FUN_00434820);
        local_8 = 5;
        FUN_00434b50(local_40,local_30,(char *)&local_20,'\x01','\x02');
        local_8 = CONCAT31(local_8._1_3_,6);
        FUN_004355e0(&stack0xffffff7c,(uint *)"joyRawBufferTooSmall");
        FUN_00408c90(local_40,in_stack_ffffff7c);
        FUN_00434820(local_40);
        local_8 = 0xffffffff;
        _eh_vector_destructor_iterator_(local_30,0x10,1,FUN_00434820);
        ExceptionList = local_10;
        return;
      }
    }
    else if (DAT_004a3390 == 1) {
      if (DAT_004a33a6 == 0x10) {
        ExceptionList = &local_10;
        UVar6 = MapVirtualKeyA(_DAT_004a33a0 & 0xffff,3);
        pbVar11 = (byte *)(UVar6 & 0xffff);
        pbVar5 = pbVar11;
        local_14 = pbVar11;
      }
      else if ((DAT_004a33a6 == 0x11) || (DAT_004a33a6 == 0x12)) {
        pbVar11 = (byte *)(uint)(ushort)((DAT_004a33a6 + 0x40) * 2 + (DAT_004a33a2 >> 1 & 1));
        pbVar5 = pbVar11;
        ExceptionList = &local_10;
        local_14 = pbVar11;
      }
      else {
        pbVar11 = (byte *)0x0;
        pbVar5 = (byte *)(uint)DAT_004a33a6;
        ExceptionList = &local_10;
      }
      if (DAT_004a3398 == (HANDLE)0x0) {
        local_14 = (byte *)(CONCAT31((int3)((uint)pbVar11 >> 8),DAT_004a33ac != -0x293e76cb) * 2 - 1
                           );
      }
      else {
        local_14 = (byte *)((uint)local_14 & 0xffffff00);
      }
      bVar12 = (byte)DAT_004a33a2;
      if (((DAT_004a33a2 & 6) == 0) ||
         (uVar9 = FUN_0040bfd0((byte)pbVar5), pbVar5 = extraout_EDX, (char)uVar9 == '\0')) {
        uVar4 = 0;
      }
      else {
        uVar4 = 0x100;
      }
      uVar14 = (uint)pbVar5 & 0xffff;
      uVar4 = uVar14 | uVar4;
      bVar12 = ~bVar12 & 1;
      local_18 = 0x400;
      if (bVar12 != 0) {
        local_18 = 0;
      }
      local_18 = local_18 | uVar4;
      if ((-1 < (char)local_14) &&
         ((((char)local_14 < '\x01' || (DAT_004a2425 == '\0')) &&
          (uVar7 = FUN_00412a80(uVar14), (char)uVar7 != '\0')))) {
        _DAT_004a2428 = (byte *)GetTickCount();
        local_14 = _DAT_004a2428;
        if (DAT_0049d9f5 != '\0') {
          FUN_00413a50('\0');
        }
        if ((bVar12 == 0) &&
           ((*(uint *)(DAT_004a28b0 + (uVar4 >> 5) * 4) & 1 << ((byte)uVar14 & 0x1f)) != 0)) {
          FUN_00412d40(uVar4,'\0',local_14);
          FUN_00413390(local_18,'\0');
          ExceptionList = local_10;
          return;
        }
      }
    }
    else if ((((DAT_004a3390 == 0) && (DAT_004a33a4 != 0)) &&
             ((DAT_004a3398 != (HANDLE)0x0 ||
              ((cVar1 = (DAT_004a33b4 != -0x293e76cb) * '\x02' + -1, -1 < cVar1 &&
               ((cVar1 < '\x01' || (DAT_004a2424 == '\0')))))))) &&
            (ExceptionList = &local_10, _DAT_004a242c = GetTickCount(), DAT_0049d9f5 != '\0')) {
      FUN_00413a50('\x01');
    }
  }
  ExceptionList = local_10;
  return;
}


