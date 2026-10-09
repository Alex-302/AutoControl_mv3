// FUN_00438530 @ 00438530 size=3655 callers=20

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

char * __fastcall FUN_00438530(char *param_1,int *param_2,uint *param_3)

{
  byte *pbVar1;
  byte bVar2;
  int iVar3;
  ushort uVar4;
  undefined4 uVar5;
  char *pcVar6;
  byte *pbVar7;
  undefined1 *puVar8;
  int iVar9;
  uint *puVar10;
  uint *puVar11;
  undefined4 *puVar12;
  char *extraout_ECX;
  char *extraout_ECX_00;
  char *extraout_ECX_01;
  char *extraout_ECX_02;
  undefined4 extraout_EDX;
  uint uVar13;
  uint uVar14;
  float10 fVar15;
  undefined8 uVar16;
  uint in_stack_fffffef8;
  undefined4 in_stack_fffffefc;
  undefined4 uVar17;
  undefined1 local_f0 [24];
  undefined1 local_d8 [24];
  undefined1 local_c0 [24];
  undefined1 local_a8 [24];
  undefined1 local_90 [24];
  undefined4 local_78;
  int local_74;
  byte local_70 [24];
  byte local_58 [8];
  char local_50 [4];
  undefined **local_4c;
  undefined8 local_48;
  uint local_40;
  undefined4 local_38;
  byte *local_34;
  int *local_30;
  char local_2c [8];
  undefined1 local_24 [8];
  undefined8 local_1c;
  char *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puVar10 = param_3;
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047dd87;
  local_10 = ExceptionList;
  local_38 = *param_3;
  local_78 = 0;
  uVar13 = local_38 + 1;
  ExceptionList = &local_10;
  *param_3 = uVar13;
  local_74 = *param_2;
  local_40 = uVar13;
  local_30 = param_2;
  local_14 = param_1;
  if ((uint)(param_2[1] - *param_2) <= local_38) goto LAB_0043857d;
  local_34 = (byte *)(*param_2 + local_38);
  local_1c = (double)(ulonglong)CONCAT14(*local_34,(undefined4)local_1c);
  switch(*local_34) {
  case 0:
  case 1:
  case 2:
  case 3:
  case 4:
  case 5:
  case 6:
  case 7:
  case 8:
  case 9:
  case 10:
  case 0xb:
  case 0xc:
  case 0xd:
  case 0xe:
  case 0xf:
  case 0x10:
  case 0x11:
  case 0x12:
  case 0x13:
  case 0x14:
  case 0x15:
  case 0x16:
  case 0x17:
    FUN_00441d80(param_1,local_38,local_34);
    ExceptionList = local_10;
    return extraout_ECX;
  case 0x18:
    *param_3 = local_38 + 2;
    uVar5 = FUN_00442db0(param_2,local_38);
    pcVar6 = local_14;
    *local_14 = '\0';
    local_14[8] = '\0';
    local_14[9] = '\0';
    local_14[10] = '\0';
    local_14[0xb] = '\0';
    local_14[0xc] = '\0';
    local_14[0xd] = '\0';
    local_14[0xe] = '\0';
    local_14[0xf] = '\0';
    FUN_00451320(local_14,CONCAT31((int3)((uint)extraout_EDX >> 8),(char)uVar5));
    ExceptionList = local_10;
    return pcVar6;
  case 0x19:
    *param_3 = local_38 + 3;
    uVar4 = FUN_00442e70(param_2,local_38);
    pcVar6 = local_14;
    *local_14 = '\0';
    local_14[8] = '\0';
    local_14[9] = '\0';
    local_14[10] = '\0';
    local_14[0xb] = '\0';
    local_14[0xc] = '\0';
    local_14[0xd] = '\0';
    local_14[0xe] = '\0';
    local_14[0xf] = '\0';
    FUN_004512e0(local_14,(uint)uVar4);
    ExceptionList = local_10;
    return pcVar6;
  case 0x1a:
    *param_3 = local_38 + 5;
    param_3 = (uint *)FUN_00442f40(param_2,local_38);
    FUN_00440db0(local_14,&param_3);
    ExceptionList = local_10;
    return extraout_ECX_00;
  case 0x1b:
    *param_3 = local_38 + 9;
    local_1c = (double)FUN_00443020(param_2,local_38);
    pcVar6 = local_14;
    *local_14 = '\0';
    local_14[8] = '\0';
    local_14[9] = '\0';
    local_14[10] = '\0';
    local_14[0xb] = '\0';
    local_14[0xc] = '\0';
    local_14[0xd] = '\0';
    local_14[0xe] = '\0';
    local_14[0xf] = '\0';
    FUN_0044df70(local_14,(undefined4 *)&local_1c);
    ExceptionList = local_10;
    return pcVar6;
  case 0x1c:
  case 0x1d:
  case 0x1e:
  case 0x1f:
  case 0x3c:
  case 0x3d:
  case 0x3e:
  case 0x3f:
  case 0x40:
  case 0x41:
  case 0x42:
  case 0x43:
  case 0x44:
  case 0x45:
  case 0x46:
  case 0x47:
  case 0x48:
  case 0x49:
  case 0x4a:
  case 0x4b:
  case 0x4c:
  case 0x4d:
  case 0x4e:
  case 0x4f:
  case 0x50:
  case 0x51:
  case 0x52:
  case 0x53:
  case 0x54:
  case 0x55:
  case 0x56:
  case 0x57:
  case 0x58:
  case 0x59:
  case 0x5a:
  case 0x5b:
  case 0x5c:
  case 0x5d:
  case 0x5e:
  case 0x5f:
  case 0x7c:
  case 0x7d:
  case 0x7e:
  case 0x9c:
  case 0x9d:
  case 0x9e:
  case 0xbc:
  case 0xbd:
  case 0xbe:
  case 0xc0:
  case 0xc1:
  case 0xc2:
  case 0xc3:
  case 0xc4:
  case 0xc5:
  case 0xc6:
  case 199:
  case 200:
  case 0xc9:
  case 0xca:
  case 0xcb:
  case 0xcc:
  case 0xcd:
  case 0xce:
  case 0xcf:
  case 0xd0:
  case 0xd1:
  case 0xd2:
  case 0xd3:
  case 0xd4:
  case 0xd5:
  case 0xd6:
  case 0xd7:
  case 0xd8:
  case 0xd9:
  case 0xda:
  case 0xdb:
  case 0xdc:
  case 0xdd:
  case 0xde:
  case 0xdf:
  case 0xe0:
  case 0xe1:
  case 0xe2:
  case 0xe3:
  case 0xe4:
  case 0xe5:
  case 0xe6:
  case 0xe7:
  case 0xe8:
  case 0xe9:
  case 0xea:
  case 0xeb:
  case 0xec:
  case 0xed:
  case 0xee:
  case 0xef:
  case 0xf0:
  case 0xf1:
  case 0xf2:
  case 0xf3:
  case 0xf7:
  case 0xf8:
  default:
    puVar10 = (uint *)FUN_00403340(local_90,(uint)*local_34);
    local_8 = 0x33;
    puVar11 = (uint *)FUN_00403360(local_a8,local_38);
    local_8._0_1_ = 0x34;
    puVar11 = (uint *)FUN_00442600(local_c0,(uint *)"error parsing a CBOR @ ",puVar11);
    local_8._0_1_ = 0x35;
    puVar11 = (uint *)FUN_004412a0(local_d8,puVar11,(uint *)&DAT_0048cb64);
    local_8._0_1_ = 0x36;
    puVar12 = (undefined4 *)FUN_00441300(local_f0,puVar11,puVar10);
    local_8 = CONCAT31(local_8._1_3_,0x37);
    if (0xf < (uint)puVar12[5]) {
      puVar12 = (undefined4 *)*puVar12;
    }
    local_4c = std::exception::vftable;
    local_48 = 0;
    local_1c._0_5_ = CONCAT14(1,puVar12);
    ___std_exception_copy((undefined4 *)&local_1c,(undefined4 *)&local_48);
    local_4c = std::invalid_argument::vftable;
                    /* WARNING: Subroutine does not return */
    __CxxThrowException_8((int *)&local_4c,&DAT_00499edc);
  case 0x20:
  case 0x21:
  case 0x22:
  case 0x23:
  case 0x24:
  case 0x25:
  case 0x26:
  case 0x27:
  case 0x28:
  case 0x29:
  case 0x2a:
  case 0x2b:
  case 0x2c:
  case 0x2d:
  case 0x2e:
  case 0x2f:
  case 0x30:
  case 0x31:
  case 0x32:
  case 0x33:
  case 0x34:
  case 0x35:
  case 0x36:
  case 0x37:
    bVar2 = *local_34;
    *param_1 = '\0';
    param_1[8] = '\0';
    param_1[9] = '\0';
    param_1[10] = '\0';
    param_1[0xb] = '\0';
    param_1[0xc] = '\0';
    param_1[0xd] = '\0';
    param_1[0xe] = '\0';
    param_1[0xf] = '\0';
    FUN_004511e0(param_1,'\x1f' - bVar2);
    ExceptionList = local_10;
    return extraout_ECX_01;
  case 0x38:
    *param_3 = local_38 + 2;
    uVar13 = FUN_00442db0(param_2,local_38);
    uVar13 = uVar13 & 0xff;
    goto LAB_004386e4;
  case 0x39:
    *param_3 = local_38 + 3;
    uVar4 = FUN_00442e70(param_2,local_38);
    uVar13 = (uint)uVar4;
    goto LAB_004386e4;
  case 0x3a:
    *param_3 = local_38 + 5;
    uVar13 = FUN_00442f40(param_2,local_38);
LAB_004386e4:
    local_1c = (double)CONCAT44(0xffffffff,~uVar13);
LAB_004386e9:
    FUN_00443120(local_14,(undefined4 *)&local_1c);
    ExceptionList = local_10;
    return local_14;
  case 0x3b:
    *param_3 = local_38 + 9;
    uVar16 = FUN_00443020(param_2,local_38);
    local_1c = (double)CONCAT44(-1 - (int)((ulonglong)uVar16 >> 0x20),-1 - (int)uVar16);
    goto LAB_004386e9;
  case 0x60:
  case 0x61:
  case 0x62:
  case 99:
  case 100:
  case 0x65:
  case 0x66:
  case 0x67:
  case 0x68:
  case 0x69:
  case 0x6a:
  case 0x6b:
  case 0x6c:
  case 0x6d:
  case 0x6e:
  case 0x6f:
  case 0x70:
  case 0x71:
  case 0x72:
  case 0x73:
  case 0x74:
  case 0x75:
  case 0x76:
  case 0x77:
    iVar9 = param_2[1];
    uVar14 = *local_34 - 0x60;
    iVar3 = *param_2;
    *param_3 = uVar13 + uVar14;
    FUN_0043d590(iVar9 - iVar3,uVar14,uVar13);
    puVar12 = FUN_00435630(local_70,(uint *)(*param_2 + local_40),uVar14);
    local_8 = 0;
    break;
  case 0x78:
    uVar13 = FUN_00442db0(param_2,local_38);
    uVar13 = uVar13 & 0xff;
    uVar14 = local_38 + 2;
    *param_3 = *param_3 + uVar13 + 1;
    FUN_0043d590(local_30[1] - *local_30,uVar13,uVar14);
    puVar12 = FUN_00435630(local_70,(uint *)(*local_30 + uVar14),uVar13);
    local_8 = 1;
    break;
  case 0x79:
    uVar4 = FUN_00442e70(param_2,local_38);
    uVar14 = (uint)uVar4;
    uVar13 = local_38 + 3;
    *param_3 = *param_3 + uVar14 + 2;
    FUN_0043d590(local_30[1] - *local_30,uVar14,uVar13);
    puVar12 = FUN_00435630(local_70,(uint *)(*local_30 + uVar13),uVar14);
    local_8 = 2;
    break;
  case 0x7a:
    uVar13 = FUN_00442f40(param_2,local_38);
    uVar14 = local_38 + 5;
    *param_3 = *param_3 + uVar13 + 4;
    FUN_0043d590(local_30[1] - *local_30,uVar13,uVar14);
    puVar12 = FUN_00435630(local_70,(uint *)(*local_30 + uVar14),uVar13);
    local_8 = 3;
    break;
  case 0x7b:
    uVar16 = FUN_00443020(param_2,local_38);
    uVar13 = (uint)uVar16;
    uVar14 = local_38 + 9;
    *param_3 = *param_3 + uVar13 + 8;
    FUN_0043d590(local_30[1] - *local_30,uVar13,uVar14);
    puVar12 = FUN_00435630(local_70,(uint *)(*local_30 + uVar14),uVar13);
    local_8 = 4;
    break;
  case 0x7f:
    local_48 = 0xf00000000;
    local_58[0] = 0;
    local_8 = 5;
    if (uVar13 < (uint)(param_2[1] - *param_2)) {
      do {
        if (*(char *)(uVar13 + *param_2) == -1) {
          *puVar10 = *puVar10 + 1;
          FUN_00440c80(local_14,(undefined4 *)local_58);
          pbVar7 = local_58;
          goto LAB_00438792;
        }
        pcVar6 = FUN_00438530(local_2c,param_2,puVar10);
        local_8._0_1_ = 6;
        FUN_00440d90(pcVar6,(undefined4 *)local_70);
        local_8._0_1_ = 8;
        FUN_00434820(local_2c);
        FUN_0043b0c0(local_58,(undefined4 *)local_70,0,0xffffffff);
        local_8 = CONCAT31(local_8._1_3_,5);
        FUN_004061c0((undefined4 *)local_70);
        uVar13 = *puVar10;
      } while (uVar13 < (uint)(param_2[1] - *param_2));
    }
    goto LAB_0043857d;
  case 0x80:
  case 0x81:
  case 0x82:
  case 0x83:
  case 0x84:
  case 0x85:
  case 0x86:
  case 0x87:
  case 0x88:
  case 0x89:
  case 0x8a:
  case 0x8b:
  case 0x8c:
  case 0x8d:
  case 0x8e:
  case 0x8f:
  case 0x90:
  case 0x91:
  case 0x92:
  case 0x93:
  case 0x94:
  case 0x95:
  case 0x96:
  case 0x97:
    local_2c[0] = '\x02';
    FUN_004381d0(local_24,'\x02');
    local_8 = 9;
    for (param_3 = (uint *)(*(byte *)(*param_2 + local_38) - 0x80); param_3 != (uint *)0x0;
        param_3 = (uint *)((int)param_3 + -1)) {
      pcVar6 = FUN_00438530(local_50,param_2,puVar10);
      local_8._0_1_ = 10;
      FUN_00433e10(local_2c,pcVar6);
      local_8 = CONCAT31(local_8._1_3_,9);
      FUN_00434820(local_50);
    }
    FUN_00434900(local_14,local_2c);
    FUN_00434820(local_2c);
    ExceptionList = local_10;
    return local_14;
  case 0x98:
    local_2c[0] = '\x02';
    FUN_004381d0(local_24,'\x02');
    local_8 = 0xb;
    uVar13 = FUN_00442db0(param_2,local_38);
    *puVar10 = *puVar10 + 1;
    for (param_3 = (uint *)(uVar13 & 0xff); param_3 != (uint *)0x0;
        param_3 = (uint *)((int)param_3 - 1)) {
      pcVar6 = FUN_00438530(local_50,param_2,puVar10);
      local_8._0_1_ = 0xc;
      FUN_00433e10(local_2c,pcVar6);
      local_8 = CONCAT31(local_8._1_3_,0xb);
      FUN_00434820(local_50);
    }
    FUN_00434900(local_14,local_2c);
    FUN_00434820(local_2c);
    ExceptionList = local_10;
    return local_14;
  case 0x99:
    local_2c[0] = '\x02';
    FUN_004381d0(local_24,'\x02');
    local_8 = 0xd;
    uVar4 = FUN_00442e70(param_2,local_38);
    *puVar10 = *puVar10 + 2;
    for (param_3 = (uint *)(uint)uVar4; param_3 != (uint *)0x0; param_3 = (uint *)((int)param_3 - 1)
        ) {
      pcVar6 = FUN_00438530(local_50,param_2,puVar10);
      local_8._0_1_ = 0xe;
      FUN_00433e10(local_2c,pcVar6);
      local_8 = CONCAT31(local_8._1_3_,0xd);
      FUN_00434820(local_50);
    }
    FUN_00434900(local_14,local_2c);
    FUN_00434820(local_2c);
    ExceptionList = local_10;
    return local_14;
  case 0x9a:
    local_2c[0] = '\x02';
    FUN_004381d0(local_24,'\x02');
    local_8 = 0xf;
    param_3 = (uint *)FUN_00442f40(param_2,local_38);
    *puVar10 = *puVar10 + 4;
    for (; param_3 != (uint *)0x0; param_3 = (uint *)((int)param_3 + -1)) {
      pcVar6 = FUN_00438530(local_50,param_2,puVar10);
      local_8._0_1_ = 0x10;
      FUN_00433e10(local_2c,pcVar6);
      local_8 = CONCAT31(local_8._1_3_,0xf);
      FUN_00434820(local_50);
    }
    FUN_00434900(local_14,local_2c);
    FUN_00434820(local_2c);
    ExceptionList = local_10;
    return local_14;
  case 0x9b:
    local_2c[0] = '\x02';
    FUN_004381d0(local_24,'\x02');
    local_8 = 0x11;
    uVar16 = FUN_00443020(param_2,local_38);
    *puVar10 = *puVar10 + 8;
    for (param_3 = (uint *)uVar16; param_3 != (uint *)0x0; param_3 = (uint *)((int)param_3 + -1)) {
      pcVar6 = FUN_00438530(local_50,param_2,puVar10);
      local_8._0_1_ = 0x12;
      FUN_00433e10(local_2c,pcVar6);
      local_8 = CONCAT31(local_8._1_3_,0x11);
      FUN_00434820(local_50);
    }
    FUN_00434900(local_14,local_2c);
    FUN_00434820(local_2c);
    ExceptionList = local_10;
    return local_14;
  case 0x9f:
    local_2c[0] = '\x02';
    FUN_004381d0(local_24,'\x02');
    local_8 = 0x13;
    uVar13 = *puVar10;
    if (uVar13 < (uint)(param_2[1] - *param_2)) {
      do {
        if (*(char *)(uVar13 + *param_2) == -1) {
LAB_00438c47:
          *puVar10 = *puVar10 + 1;
          FUN_00434900(local_14,local_2c);
          FUN_00434820(local_2c);
          ExceptionList = local_10;
          return local_14;
        }
        pcVar6 = FUN_00438530(local_50,param_2,puVar10);
        local_8._0_1_ = 0x14;
        FUN_00433e10(local_2c,pcVar6);
        local_8 = CONCAT31(local_8._1_3_,0x13);
        FUN_00434820(local_50);
        uVar13 = *puVar10;
      } while (uVar13 < (uint)(param_2[1] - *param_2));
    }
    goto LAB_0043857d;
  case 0xa0:
  case 0xa1:
  case 0xa2:
  case 0xa3:
  case 0xa4:
  case 0xa5:
  case 0xa6:
  case 0xa7:
  case 0xa8:
  case 0xa9:
  case 0xaa:
  case 0xab:
  case 0xac:
  case 0xad:
  case 0xae:
  case 0xaf:
  case 0xb0:
  case 0xb1:
  case 0xb2:
  case 0xb3:
  case 0xb4:
  case 0xb5:
  case 0xb6:
  case 0xb7:
    local_2c[0] = '\x01';
    FUN_004381d0(local_24,'\x01');
    local_8 = 0x15;
    for (param_3 = (uint *)(*(byte *)(*param_2 + local_38) - 0xa0); param_3 != (uint *)0x0;
        param_3 = (uint *)((int)param_3 + -1)) {
      pcVar6 = FUN_00438530(local_50,param_2,puVar10);
      local_8._0_1_ = 0x16;
      uVar5 = 0x438cb5;
      FUN_00440d90(pcVar6,(undefined4 *)local_70);
      local_8._0_1_ = 0x18;
      uVar17 = 0x438cc1;
      FUN_00434820(local_50);
      local_1c = (double)CONCAT44(&stack0xfffffef8,(undefined4)local_1c);
      FUN_00438530(&stack0xfffffef8,param_2,puVar10);
      local_8._0_1_ = 0x19;
      puVar8 = FUN_00434440(local_2c,local_70);
      local_8._0_1_ = 0x18;
      FUN_004348c0(puVar8,(char)in_stack_fffffef8,in_stack_fffffefc,uVar5,uVar17);
      local_8 = CONCAT31(local_8._1_3_,0x15);
      FUN_004061c0((undefined4 *)local_70);
    }
    FUN_00434900(local_14,local_2c);
    FUN_00434820(local_2c);
    ExceptionList = local_10;
    return local_14;
  case 0xb8:
    local_2c[0] = '\x01';
    FUN_004381d0(local_24,'\x01');
    local_8 = 0x1a;
    uVar13 = FUN_00442db0(param_2,local_38);
    *puVar10 = *puVar10 + 1;
    for (param_3 = (uint *)(uVar13 & 0xff); param_3 != (uint *)0x0;
        param_3 = (uint *)((int)param_3 - 1)) {
      pcVar6 = FUN_00438530(local_50,param_2,puVar10);
      local_8._0_1_ = 0x1b;
      uVar5 = 0x438d70;
      FUN_00440d90(pcVar6,(undefined4 *)local_70);
      local_8._0_1_ = 0x1d;
      uVar17 = 0x438d7c;
      FUN_00434820(local_50);
      local_1c = (double)CONCAT44(&stack0xfffffef8,(undefined4)local_1c);
      FUN_00438530(&stack0xfffffef8,param_2,puVar10);
      local_8._0_1_ = 0x1e;
      puVar8 = FUN_00434440(local_2c,local_70);
      local_8._0_1_ = 0x1d;
      FUN_004348c0(puVar8,(char)in_stack_fffffef8,in_stack_fffffefc,uVar5,uVar17);
      local_8 = CONCAT31(local_8._1_3_,0x1a);
      FUN_004061c0((undefined4 *)local_70);
    }
    FUN_00434900(local_14,local_2c);
    FUN_00434820(local_2c);
    ExceptionList = local_10;
    return local_14;
  case 0xb9:
    local_2c[0] = '\x01';
    FUN_004381d0(local_24,'\x01');
    local_8 = 0x1f;
    uVar4 = FUN_00442e70(param_2,local_38);
    *puVar10 = *puVar10 + 2;
    for (param_3 = (uint *)(uint)uVar4; param_3 != (uint *)0x0; param_3 = (uint *)((int)param_3 - 1)
        ) {
      pcVar6 = FUN_00438530(local_50,param_2,puVar10);
      local_8._0_1_ = 0x20;
      uVar5 = 0x438e2d;
      FUN_00440d90(pcVar6,(undefined4 *)local_70);
      local_8._0_1_ = 0x22;
      uVar17 = 0x438e39;
      FUN_00434820(local_50);
      local_1c = (double)CONCAT44(&stack0xfffffef8,(undefined4)local_1c);
      FUN_00438530(&stack0xfffffef8,param_2,puVar10);
      local_8._0_1_ = 0x23;
      puVar8 = FUN_00434440(local_2c,local_70);
      local_8._0_1_ = 0x22;
      FUN_004348c0(puVar8,(char)in_stack_fffffef8,in_stack_fffffefc,uVar5,uVar17);
      local_8 = CONCAT31(local_8._1_3_,0x1f);
      FUN_004061c0((undefined4 *)local_70);
    }
    FUN_00434900(local_14,local_2c);
    FUN_00434820(local_2c);
    ExceptionList = local_10;
    return local_14;
  case 0xba:
    local_2c[0] = '\x01';
    FUN_004381d0(local_24,'\x01');
    local_8 = 0x24;
    param_3 = (uint *)FUN_00442f40(param_2,local_38);
    *puVar10 = *puVar10 + 4;
    for (; param_3 != (uint *)0x0; param_3 = (uint *)((int)param_3 + -1)) {
      pcVar6 = FUN_00438530(local_50,param_2,puVar10);
      local_8._0_1_ = 0x25;
      uVar5 = 0x438eed;
      FUN_00440d90(pcVar6,(undefined4 *)local_70);
      local_8._0_1_ = 0x27;
      uVar17 = 0x438ef9;
      FUN_00434820(local_50);
      local_1c = (double)CONCAT44(&stack0xfffffef8,(undefined4)local_1c);
      FUN_00438530(&stack0xfffffef8,param_2,puVar10);
      local_8._0_1_ = 0x28;
      puVar8 = FUN_00434440(local_2c,local_70);
      local_8._0_1_ = 0x27;
      FUN_004348c0(puVar8,(char)in_stack_fffffef8,in_stack_fffffefc,uVar5,uVar17);
      local_8 = CONCAT31(local_8._1_3_,0x24);
      FUN_004061c0((undefined4 *)local_70);
    }
    FUN_00434900(local_14,local_2c);
    FUN_00434820(local_2c);
    ExceptionList = local_10;
    return local_14;
  case 0xbb:
    local_2c[0] = '\x01';
    FUN_004381d0(local_24,'\x01');
    local_8 = 0x29;
    uVar16 = FUN_00443020(param_2,local_38);
    *puVar10 = *puVar10 + 8;
    for (param_3 = (uint *)uVar16; param_3 != (uint *)0x0; param_3 = (uint *)((int)param_3 + -1)) {
      pcVar6 = FUN_00438530(local_50,param_2,puVar10);
      local_8._0_1_ = 0x2a;
      uVar5 = 0x438fad;
      FUN_00440d90(pcVar6,(undefined4 *)local_70);
      local_8._0_1_ = 0x2c;
      uVar17 = 0x438fb9;
      FUN_00434820(local_50);
      local_1c = (double)CONCAT44(&stack0xfffffef8,(undefined4)local_1c);
      FUN_00438530(&stack0xfffffef8,param_2,puVar10);
      local_8._0_1_ = 0x2d;
      puVar8 = FUN_00434440(local_2c,local_70);
      local_8._0_1_ = 0x2c;
      FUN_004348c0(puVar8,(char)in_stack_fffffef8,in_stack_fffffefc,uVar5,uVar17);
      local_8 = CONCAT31(local_8._1_3_,0x29);
      FUN_004061c0((undefined4 *)local_70);
    }
    FUN_00434900(local_14,local_2c);
    FUN_00434820(local_2c);
    ExceptionList = local_10;
    return local_14;
  case 0xbf:
    local_2c[0] = '\x01';
    FUN_004381d0(local_24,'\x01');
    local_8 = 0x2e;
    uVar13 = *puVar10;
    if (uVar13 < (uint)(param_2[1] - *param_2)) {
      do {
        if (*(char *)(uVar13 + *param_2) == -1) goto LAB_00438c47;
        pcVar6 = FUN_00438530(local_50,param_2,puVar10);
        local_8._0_1_ = 0x2f;
        uVar5 = 0x43906d;
        FUN_00440d90(pcVar6,(undefined4 *)local_70);
        local_8._0_1_ = 0x31;
        uVar17 = 0x439079;
        FUN_00434820(local_50);
        param_3 = (uint *)&stack0xfffffef8;
        FUN_00438530(&stack0xfffffef8,param_2,puVar10);
        local_8._0_1_ = 0x32;
        puVar8 = FUN_00434440(local_2c,local_70);
        local_8._0_1_ = 0x31;
        FUN_004348c0(puVar8,(char)in_stack_fffffef8,in_stack_fffffefc,uVar5,uVar17);
        local_8 = CONCAT31(local_8._1_3_,0x2e);
        FUN_004061c0((undefined4 *)local_70);
        uVar13 = *puVar10;
      } while (uVar13 < (uint)(param_2[1] - *param_2));
    }
    goto LAB_0043857d;
  case 0xf4:
    param_3 = (uint *)((uint)param_3 & 0xffffff);
    goto LAB_004390c7;
  case 0xf5:
    param_3 = (uint *)CONCAT13(1,param_3._0_3_);
LAB_004390c7:
    FUN_00440fa0(param_1,(undefined1 *)((int)&param_3 + 3));
    ExceptionList = local_10;
    return extraout_ECX_02;
  case 0xf6:
    *param_1 = '\0';
    FUN_004381d0(param_1 + 8,'\0');
    ExceptionList = local_10;
    return local_14;
  case 0xf9:
    *param_3 = local_38 + 3;
    pbVar7 = (byte *)FUN_0043d810(param_2,uVar13);
    bVar2 = *pbVar7;
    puVar8 = (undefined1 *)FUN_0043d810(param_2,local_38 + 2);
    uVar4 = CONCAT11(bVar2,*puVar8) & 0x3ff;
    uVar13 = bVar2 >> 2 & 0x1f;
    if ((bVar2 & 0x7c) == 0) {
      fVar15 = FUN_0046590c((double)uVar4,-0x18);
      local_1c = (double)fVar15;
    }
    else if (uVar13 == 0x1f) {
      local_1c = DAT_0048f2a8;
      if ((CONCAT11(bVar2,*puVar8) & 0x3ff) == 0) {
        local_1c = DAT_0048f2a0;
      }
    }
    else {
      fVar15 = FUN_0046590c((double)(ushort)(uVar4 + 0x400),uVar13 - 0x19);
      local_1c = (double)fVar15;
    }
    if ((bVar2 & 0x80) != 0) {
      local_1c = (double)CONCAT44((uint)((ulonglong)local_1c >> 0x20) ^ _UNK_0048f2f4,
                                  SUB84(local_1c,0) ^ _DAT_0048f2f0);
    }
    FUN_00442760(local_14);
    ExceptionList = local_10;
    return local_14;
  case 0xfa:
    local_40 = param_2[1] - *param_2;
    uVar13 = local_38 + 1;
    local_30 = (int *)(-1 - local_38);
    iVar9 = *param_2;
    local_34 = (byte *)((int)&local_38 + 3);
    while (uVar13 < local_40) {
      pbVar7 = (byte *)(iVar9 + uVar13);
      uVar13 = uVar13 + 1;
      pbVar1 = local_34 + -1;
      *local_34 = *pbVar7;
      iVar9 = local_74;
      local_34 = pbVar1;
      if (3 < (int)local_30 + uVar13) {
        *param_1 = '\0';
        *param_3 = local_38 + 5;
        param_1[8] = '\0';
        param_1[9] = '\0';
        param_1[10] = '\0';
        param_1[0xb] = '\0';
        param_1[0xc] = '\0';
        param_1[0xd] = '\0';
        param_1[0xe] = '\0';
        param_1[0xf] = '\0';
        FUN_00451560(param_1);
        ExceptionList = local_10;
        return local_14;
      }
    }
    goto LAB_0043857d;
  case 0xfb:
    local_40 = param_2[1] - *param_2;
    uVar13 = local_38 + 1;
    local_30 = (int *)(-1 - local_38);
    iVar9 = *param_2;
    local_34 = (byte *)((int)&local_38 + 3);
    while (uVar13 < local_40) {
      pbVar7 = (byte *)(iVar9 + uVar13);
      uVar13 = uVar13 + 1;
      pbVar1 = local_34 + -1;
      *local_34 = *pbVar7;
      iVar9 = local_74;
      local_34 = pbVar1;
      if (7 < (int)local_30 + uVar13) {
        *param_1 = '\0';
        *param_3 = local_38 + 9;
        param_1[8] = '\0';
        param_1[9] = '\0';
        param_1[10] = '\0';
        param_1[0xb] = '\0';
        param_1[0xc] = '\0';
        param_1[0xd] = '\0';
        param_1[0xe] = '\0';
        param_1[0xf] = '\0';
        FUN_0044deb0(param_1);
        ExceptionList = local_10;
        return local_14;
      }
    }
LAB_0043857d:
                    /* WARNING: Subroutine does not return */
    FUN_00458ee4("invalid vector<T> subscript");
  }
  FUN_00440c80(local_14,puVar12);
  pbVar7 = local_70;
LAB_00438792:
  FUN_004061c0((undefined4 *)pbVar7);
  ExceptionList = local_10;
  return local_14;
}


