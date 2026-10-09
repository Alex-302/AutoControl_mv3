// FUN_00422310 @ 00422310 size=965 callers=1

undefined4 __fastcall FUN_00422310(void *param_1)

{
  byte **ppbVar1;
  HDC__ *pHVar2;
  byte *pbVar3;
  uint uVar4;
  int iVar5;
  HDC__ HVar6;
  char cVar7;
  uint uVar8;
  BOOL BVar9;
  HWND pHVar10;
  undefined4 uVar11;
  uint uVar12;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  uint uVar13;
  int *piVar14;
  int *piVar15;
  undefined4 *puVar16;
  undefined8 uVar17;
  byte *local_80 [2];
  int local_78;
  int local_74;
  byte *local_70;
  _FILETIME local_68;
  int local_60;
  undefined1 local_5c;
  int local_58;
  undefined1 local_54;
  int local_50;
  undefined1 local_4c;
  int local_48;
  int local_44;
  byte *local_40;
  byte *local_3c;
  byte *local_38;
  int local_34;
  int local_30;
  int local_2c;
  int local_28;
  uint local_24;
  byte *local_20;
  uint local_1c;
  uint local_18;
  HDC__ local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047bd10;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  do {
    uVar12 = *(uint *)((int)param_1 + 8);
    uVar13 = (uint)*(byte *)((int)param_1 + 0x3a);
    uVar4 = (uint)(*(uint *)((int)param_1 + 0x30) < uVar12 % uVar13);
    if (uVar12 / uVar13 + uVar4 == 0) {
      uVar8 = 1;
    }
    else {
      uVar8 = uVar12 / uVar13 + uVar4;
    }
    local_1c = (uint)*(byte *)((int)param_1 + 0x3b);
    if (uVar8 <= local_1c) {
      if (uVar12 / uVar13 + uVar4 == 0) {
        local_1c = 1;
      }
      else {
        local_1c = uVar4 + uVar12 / uVar13;
      }
    }
    local_18 = 0;
    local_24 = 0;
    uVar12 = 0;
    piVar14 = (int *)**(int **)((int)param_1 + 4);
    if ((int *)**(int **)((int)param_1 + 4) != *(int **)((int)param_1 + 4)) {
      do {
        cVar7 = FUN_00409750((HWND)piVar14[2]);
        if (cVar7 == '\0') {
          piVar15 = (int *)*piVar14;
          FUN_00431c40(param_1,&local_48,piVar14);
        }
        else {
          pHVar10 = (HWND)piVar14[2];
          BVar9 = IsWindowVisible(pHVar10);
          if ((((BVar9 != 0) && (BVar9 = IsIconic(pHVar10), BVar9 == 0)) &&
              (piVar14[2] != *(int *)((int)param_1 + 0x34))) &&
             ((local_24 = local_24 + 1, local_18 < local_1c && (piVar14[3] != 0)))) {
            for (piVar15 = *(int **)((int)param_1 + 0x20);
                (piVar15 != *(int **)((int)param_1 + 0x24) && (*piVar15 != piVar14[3]));
                piVar15 = piVar15 + 1) {
            }
            if (((piVar15 == *(int **)((int)param_1 + 0x24)) ||
                ((int)piVar15 - (int)*(int **)((int)param_1 + 0x20) >> 2 == -1)) &&
               (pHVar10 = FUN_0040e800((HWND)piVar14[2]), pHVar10 == (HWND)0x0)) {
              FUN_0040e8d0(&local_14,(HWND)piVar14[2],(uint)*(ushort *)((int)param_1 + 0x38),
                           (HDC)(uint)*(ushort *)((int)param_1 + 0x38));
              local_8 = 0;
              GetSystemTimeAsFileTime(&local_68);
              uVar17 = __alldiv(local_68.dwLowDateTime,local_68.dwHighDateTime,10000,0);
              local_28 = (uint)uVar17 + 0xcf499800;
              local_2c = ((int)((ulonglong)uVar17 >> 0x20) + -0xa97) -
                         (uint)((uint)uVar17 < 0x30b66800);
              if ((undefined4 *)local_14.unused == (undefined4 *)0x0) {
LAB_0042261f:
                FUN_00432e80((void *)((int)param_1 + 0x20),piVar14 + 3);
              }
              else {
                uVar11 = FUN_0040ae30(local_14.unused,'\0');
                if (((char)uVar11 == '\0') ||
                   (*(char *)((int)param_1 + 0x3c) = *(char *)((int)param_1 + 0x3c) + '\x01',
                   3 < *(byte *)((int)param_1 + 0x3c))) {
                  pbVar3 = (byte *)(piVar14 + 3);
                  *(undefined1 *)((int)param_1 + 0x3c) = 0;
                  FUN_00436250(&DAT_004a290c,&local_30,pbVar3);
                  if (local_30 == DAT_004a2910) {
                    local_20 = pbVar3;
                    FUN_0044a600(&DAT_004a290c,&local_50,extraout_ECX,&local_20);
                  }
                  else {
                    local_50 = local_30;
                    local_4c = 0;
                  }
                  local_80[0] = *(byte **)(local_50 + 0xc);
                  *(undefined4 *)(local_50 + 0xc) = 0;
                  local_78 = local_28;
                  local_74 = local_2c;
                  local_70 = *(byte **)pbVar3;
                  local_8 = CONCAT31(local_8._1_3_,1);
                  local_40 = local_70;
                  local_3c = local_80[0];
                  local_20 = local_80[0];
                  FUN_00436250(&DAT_004a294c,&local_34,(byte *)(piVar14 + 2));
                  if (local_34 == DAT_004a2950) {
                    local_38 = (byte *)(piVar14 + 2);
                    FUN_0044a5a0(&DAT_004a294c,&local_58,extraout_ECX_00,&local_38);
                  }
                  else {
                    local_58 = local_34;
                    local_54 = 0;
                  }
                  iVar5 = local_58;
                  ppbVar1 = (byte **)(local_58 + 0x10);
                  if (ppbVar1 != local_80) {
                    pbVar3 = *ppbVar1;
                    local_20 = (byte *)0x0;
                    *ppbVar1 = local_3c;
                    if (pbVar3 != (byte *)0x0) {
                      (*(code *)**(undefined4 **)pbVar3)(1);
                    }
                  }
                  *(int *)(iVar5 + 0x18) = local_28;
                  *(int *)(iVar5 + 0x1c) = local_2c;
                  *(byte **)(iVar5 + 0x20) = local_40;
                  local_8 = local_8 & 0xffffff00;
                  if (local_20 != (byte *)0x0) {
                    (*(code *)**(undefined4 **)local_20)(1);
                  }
                  pbVar3 = (byte *)(piVar14 + 3);
                  FUN_00436250(&DAT_004a290c,&local_44,pbVar3);
                  if (local_44 == DAT_004a2910) {
                    local_40 = pbVar3;
                    FUN_0044a600(&DAT_004a290c,&local_60,extraout_ECX_01,&local_40);
                  }
                  else {
                    local_60 = local_44;
                    local_5c = 0;
                  }
                  HVar6.unused = local_14.unused;
                  pHVar2 = (HDC__ *)(local_60 + 0xc);
                  if (pHVar2 != &local_14) {
                    local_14.unused = 0;
                    puVar16 = (undefined4 *)pHVar2->unused;
                    pHVar2->unused = HVar6.unused;
                    if (puVar16 != (undefined4 *)0x0) {
                      (**(code **)*puVar16)(1);
                    }
                  }
                  if (DAT_004a299c != (void *)0x0) {
                    FUN_0041cfa0(DAT_004a299c,*(int *)pbVar3);
                  }
                  goto LAB_0042261f;
                }
              }
              local_18 = local_18 + 1;
              local_8 = 0xffffffff;
              if ((undefined4 *)local_14.unused != (undefined4 *)0x0) {
                (*(code *)**(undefined4 **)local_14.unused)(1);
              }
            }
          }
          piVar15 = (int *)*piVar14;
        }
        piVar14 = piVar15;
      } while (piVar15 != *(int **)((int)param_1 + 4));
      uVar12 = local_24;
      if (local_18 != 0) {
LAB_00422689:
        uVar12 = *(int *)((int)param_1 + 0x30) + 1;
        *(uint *)((int)param_1 + 0x30) = uVar12 % (uint)*(byte *)((int)param_1 + 0x3a);
        *(undefined4 *)((int)param_1 + 0x34) = 0;
        puVar16 = &DAT_004a2538;
        if (0xf < DAT_004a254c) {
          puVar16 = DAT_004a2538;
        }
        ExceptionList = local_10;
        return CONCAT31((int3)((ulonglong)uVar12 / (ulonglong)*(byte *)((int)param_1 + 0x3a) >> 8),
                        *(char *)(puVar16 + 3) == *(char *)(puVar16 + 8));
      }
    }
    if (((*(int *)((int)param_1 + 0x24) - *(int *)((int)param_1 + 0x20) & 0xfffffffcU) == 0) ||
       ((uVar12 < *(byte *)((int)param_1 + 0x3a) && (*(int *)((int)param_1 + 0x30) != 0))))
    goto LAB_00422689;
    *(undefined4 *)((int)param_1 + 0x24) = *(undefined4 *)((int)param_1 + 0x20);
  } while( true );
}


