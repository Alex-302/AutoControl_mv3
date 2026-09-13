// FUN_00413390 @ 00413390 size=1661 callers=9

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint __fastcall FUN_00413390(undefined4 param_1,char param_2)

{
  UINT_PTR *pUVar1;
  int iVar2;
  undefined4 uVar3;
  bool bVar4;
  char cVar10;
  undefined4 uVar5;
  int *piVar6;
  char *pcVar7;
  char *pcVar8;
  uint uVar9;
  uint extraout_ECX;
  uint extraout_ECX_00;
  ushort uVar11;
  undefined4 unaff_EBX;
  void *pvVar12;
  uint *puVar13;
  ushort *puVar14;
  uint *puVar15;
  void *pvVar16;
  byte bVar17;
  uint *in_stack_ffffff88;
  undefined8 uVar18;
  char local_60 [16];
  char local_50 [8];
  undefined8 local_48;
  char local_40 [8];
  undefined8 local_38;
  undefined4 local_30;
  void *local_2c;
  void *local_28;
  uint local_24;
  int *local_20;
  undefined4 local_1c;
  undefined4 local_18;
  char local_13;
  char local_12;
  char local_11;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047ab88;
  local_10 = ExceptionList;
  local_20 = DAT_004a29e8;
  if (DAT_004a29e8 == (int *)0x0) {
    return 0;
  }
  local_1c._0_2_ = (short)param_1;
  uVar11 = (short)local_1c + (char)(DAT_004a255c / 0x5609);
  local_1c = CONCAT22((short)((uint)param_1 >> 0x10),uVar11);
  ExceptionList = &local_10;
  local_12 = param_2;
  if (DAT_004a263c != 0) {
    ExceptionList = &local_10;
    FUN_0040fb40((UINT_PTR *)(DAT_004a263c + 0x10),'\x01');
  }
  uVar9 = local_1c;
  FUN_00413270(&local_18,(ushort)local_1c);
  if ((((DAT_004a26c2 != 0) && ((uVar9 & 0xfc00) != 0x1800)) &&
      (bVar4 = FUN_00413200((ushort *)&local_18), bVar4)) && (DAT_004a25ec != DAT_004a25f0)) {
    puVar15 = (uint *)((int)DAT_004a25ec + 2);
    puVar13 = DAT_004a25ec;
    do {
      in_stack_ffffff88 = (uint *)0x41344d;
      FUN_004376f0(&local_24,(byte *)puVar13);
      if (local_24 == DAT_004a29f4) {
                    /* WARNING: Subroutine does not return */
        FUN_00458ee4("invalid unordered_map<K, T> key");
      }
      uVar5 = FUN_0041fdf0((undefined4 *)(local_24 + 0xc));
      if ((char)uVar5 == '\0') {
        in_stack_ffffff88 = puVar13;
        FUN_0045b0e0(puVar13,puVar15,(int)DAT_004a25f0 - (int)puVar15);
        DAT_004a25f0 = (uint *)((int)DAT_004a25f0 + -2);
      }
      else {
        puVar13 = (uint *)((int)puVar13 + 2);
        puVar15 = (uint *)((int)puVar15 + 2);
      }
    } while (puVar13 != DAT_004a25f0);
  }
  pcVar8 = (char *)&DAT_004a2538;
  if (0xf < DAT_004a254c) {
    pcVar8 = DAT_004a2538;
  }
  _DAT_004a26b0 = local_18;
  local_2c = (void *)CONCAT31((int3)(CONCAT22((short)((uint)unaff_EBX >> 0x10),uVar11) >> 8),
                              *pcVar8 != pcVar8[0x18]);
  pcVar8 = (char *)&DAT_004a2538;
  if (0xf < DAT_004a254c) {
    pcVar8 = DAT_004a2538;
  }
  local_13 = pcVar8[10] != pcVar8[0x3e];
  uVar9 = 0;
  local_24 = 0;
  DAT_004a26c2 = uVar11;
  if (DAT_004a26c6 != '\0') {
    if ((((local_18._3_1_ != '\x01') || (local_18._2_1_ == '\0')) ||
        (pvVar12 = local_2c, (short)local_18 != 1)) &&
       ((pvVar12 = (void *)0x1, local_18._3_1_ != '\v' &&
        ((local_18._3_1_ != '\x01' || (local_18._2_1_ != '\0')))))) {
      cVar10 = '\0';
      uVar18 = 0;
      FUN_004512e0(&stack0xffffff84,local_1c);
      FUN_004088a0('E',cVar10,in_stack_ffffff88,(int)uVar18,(int)((ulonglong)uVar18 >> 0x20));
      uVar9 = local_24;
    }
    goto LAB_0041393e;
  }
  if (DAT_004a2608 != DAT_004a260c) {
    puVar15 = DAT_004a2608 + 1;
    puVar13 = DAT_004a2608;
    local_18 = puVar15;
    do {
      local_28 = (void *)*puVar13;
      pUVar1 = (UINT_PTR *)((int)local_28 + 0x10);
      if ((*(int *)((int)local_28 + 0x10) == 0) ||
         (piVar6 = FUN_00420570(local_28,uVar9,local_20), (char)piVar6 == '\0')) {
        if (*pUVar1 != 0) {
          iVar2 = *(int *)ThreadLocalStoragePointer;
          KillTimer(*(HWND *)(&DAT_004a2470 + *(int *)(iVar2 + 4) * 4),*pUVar1);
          iVar2 = *(int *)(iVar2 + 4);
          FUN_00436350(&DAT_004a2850 + iVar2 * 0x20,(int *)&local_38,(byte *)((int)local_28 + 0x10))
          ;
          for (piVar6 = (int *)local_38; piVar6 != local_38._4_4_; piVar6 = (int *)*piVar6) {
          }
          FUN_00436710(&DAT_004a2850 + iVar2 * 0x20,&local_30,(int *)local_38,local_38._4_4_);
          puVar15 = local_18;
        }
        FUN_0045b0e0(puVar13,puVar15,(int)DAT_004a260c - (int)puVar15);
        DAT_004a260c = DAT_004a260c + -1;
        uVar9 = extraout_ECX_00;
      }
      else {
        puVar13 = puVar13 + 1;
        puVar15 = puVar15 + 1;
        uVar9 = extraout_ECX;
        local_18 = puVar15;
      }
    } while (puVar13 != DAT_004a260c);
  }
  pvVar12 = local_2c;
  bVar17 = (byte)local_2c;
  FUN_00437350(local_20 + 3,(int *)&local_2c,(byte *)&local_1c);
  if (local_2c != (void *)local_20[4]) {
    DAT_004a264a = 0;
    pvVar16 = (void *)0x0;
    puVar14 = *(ushort **)((int)local_2c + 0xc);
    local_11 = '\0';
    local_28 = (void *)((uint)((int)*(ushort **)((int)local_2c + 0x10) + (1 - (int)puVar14)) >> 1);
    if (*(ushort **)((int)local_2c + 0x10) < puVar14) {
      local_28 = (void *)0x0;
    }
    if (local_28 != (void *)0x0) {
      do {
        local_2c = (void *)(*local_20 + (uint)*puVar14 * 0x24);
        piVar6 = FUN_00420570(local_2c,(uint)*puVar14 * 9,local_20);
        *(char *)((int)local_2c + 0x20) = (char)piVar6;
        if ((char)piVar6 != '\0') {
          local_24 = local_24 & 0xff;
          if (local_12 != '\0') {
            local_24 = 1;
          }
          FUN_004207f0(local_2c,(undefined1 *)&local_18,local_2c,local_20);
          pvVar12 = (void *)(uint)(byte)((byte)pvVar12 | (byte)local_18);
          cVar10 = (char)((uint)local_18 >> 8);
          if ((cVar10 != '\0') && (local_11 != 'N')) {
            local_11 = cVar10;
          }
        }
        bVar17 = (byte)pvVar12;
        pvVar16 = (void *)((int)pvVar16 + 1);
        puVar14 = puVar14 + 1;
      } while (pvVar16 != local_28);
    }
    if (3 < (uint)((int)DAT_004a25e4 - (int)ram0x004a25e0)) {
      FUN_00410800('\x01');
      FUN_00434a40(local_60,(char *)0x0,(char *)0x0);
      local_8 = 0;
      if ((DAT_004a26c2 & 0xfc00) == 0x1000) {
        uVar5 = local_38._4_4_;
        local_38 = CONCAT71(local_38._1_7_,1);
        iVar2 = (int)(int *)local_38;
        local_50[0] = '\x04';
        local_48 = CONCAT44(uVar5,(int *)local_38);
        local_8 = 1;
        pcVar7 = (char *)FUN_00440e70(local_60,(uint *)"mouseGest");
        local_50[0] = *pcVar7;
        *pcVar7 = '\x04';
        local_48 = *(undefined8 *)(pcVar7 + 8);
        pcVar8 = local_50;
        *(int *)(pcVar7 + 8) = iVar2;
        *(undefined4 *)(pcVar7 + 0xc) = uVar5;
LAB_004137cb:
        FUN_00434820(pcVar8);
      }
      else if ((DAT_004a26c2 & 0xfc00) == 0x800) {
        local_40[0] = '\0';
        local_38 = 0;
        FUN_004511e0(local_40,DAT_004a26c4);
        local_8 = CONCAT31(local_8._1_3_,2);
        pcVar7 = (char *)FUN_00440e70(local_60,(uint *)"trigInstId");
        cVar10 = *pcVar7;
        *pcVar7 = local_40[0];
        uVar18 = *(undefined8 *)(pcVar7 + 8);
        *(int **)(pcVar7 + 8) = (int *)local_38;
        pcVar8 = local_40;
        *(int **)(pcVar7 + 0xc) = local_38._4_4_;
        local_40[0] = cVar10;
        local_38 = uVar18;
        goto LAB_004137cb;
      }
      uVar3 = DAT_004a26d4;
      uVar5 = DAT_004a26d0;
      local_18 = (uint *)CONCAT13(DAT_004a26c8,(undefined3)local_18);
      if (DAT_004a26c8 == '\x01') {
        local_38 = 0;
        DAT_004a26d0 = 0;
        local_50[0] = DAT_004a26c8;
        local_48 = CONCAT44(DAT_004a26d4,uVar5);
        DAT_004a26c8 = '\0';
        DAT_004a26d4 = 0;
        local_8 = CONCAT31(local_8._1_3_,3);
        pcVar8 = (char *)FUN_00440e70(local_60,(uint *)"extEvtData");
        local_50[0] = *pcVar8;
        *pcVar8 = local_18._3_1_;
        local_48 = *(undefined8 *)(pcVar8 + 8);
        *(undefined4 *)(pcVar8 + 8) = uVar5;
        *(undefined4 *)(pcVar8 + 0xc) = uVar3;
        FUN_00434820(local_50);
      }
      piVar6 = ram0x004a25e0;
      if (ram0x004a25e0 != DAT_004a25e4) {
        do {
          local_40[0] = '\0';
          local_38 = 0;
          FUN_00451040(local_40,(*piVar6 - _DAT_004a23c0) + DAT_004a255c);
          local_8._0_1_ = 4;
          pcVar8 = (char *)FUN_00440e70(local_60,(uint *)&DAT_0048cf30);
          local_8 = (uint)local_8._1_3_ << 8;
          cVar10 = *pcVar8;
          *pcVar8 = local_40[0];
          uVar18 = *(undefined8 *)(pcVar8 + 8);
          *(int **)(pcVar8 + 8) = (int *)local_38;
          *(int **)(pcVar8 + 0xc) = local_38._4_4_;
          local_40[0] = cVar10;
          local_38 = uVar18;
          FUN_00434820(local_40);
          FUN_00408600(0x2ee,local_60);
          piVar6 = piVar6 + 1;
        } while (piVar6 != DAT_004a25e4);
      }
      DAT_004a25e4 = ram0x004a25e0;
      local_8 = 0xffffffff;
      FUN_00434820(local_60);
    }
    if ((local_11 == 'Y') && (bVar17 == 0)) {
      pcVar8 = (char *)&DAT_004a2538;
      if (0xf < DAT_004a254c) {
        pcVar8 = DAT_004a2538;
      }
      bVar17 = pcVar8[2] == pcVar8[0x30];
      local_13 = bVar17;
    }
  }
  bVar4 = FUN_0041e3b0(local_1c,bVar17);
  pvVar12 = (void *)(uint)(bVar17 | bVar4);
  uVar9 = local_24;
LAB_0041393e:
  cVar10 = (char)pvVar12;
  if (local_12 != '\0') {
    ExceptionList = local_10;
    return uVar9 & 0xff;
  }
  if ((DAT_004a23a3 != '\0') && (DAT_004a26b3 == '\0')) {
    if ((DAT_004a26b2 == '\0') || ((0x1ff < DAT_004a26b0 && (DAT_004a26b0 < 0x204)))) {
      bVar4 = (char)(DAT_004a255c / 0x5609) == '\0';
    }
    else {
      bVar4 = ((*(uint *)(DAT_004a28b0 + (uint)(DAT_004a26b0 >> 5) * 4) &
               1 << ((byte)_DAT_004a26b0 & 0x1f)) != 0) != (bool)DAT_004a23a2;
    }
    if (!bVar4) {
      cVar10 = '\x01';
    }
  }
  if (local_13 == '\0') {
    uVar9 = 0;
    if (cVar10 != '\0') {
      uVar9 = 3;
    }
    ExceptionList = local_10;
    return uVar9;
  }
  ExceptionList = local_10;
  return 2;
}


