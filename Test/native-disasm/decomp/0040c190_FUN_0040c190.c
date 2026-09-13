// FUN_0040c190 @ 0040c190 size=1101 callers=15

int * __fastcall FUN_0040c190(int *param_1,char *param_2,undefined4 param_3,char param_4)

{
  char cVar1;
  POINT pt;
  ushort uVar2;
  char *pcVar3;
  UINT UVar4;
  uint uVar5;
  int iVar6;
  undefined4 uVar7;
  undefined1 *puVar8;
  char *pcVar9;
  HMONITOR pHVar10;
  char *extraout_ECX;
  uint uVar11;
  undefined4 *puVar12;
  uint uVar13;
  float10 fVar14;
  float10 fVar15;
  float in_XMM0_Da;
  char local_7c [16];
  char local_6c [8];
  undefined8 local_64;
  int local_58;
  int local_54;
  int local_50;
  int local_4c;
  float local_48;
  uint local_44;
  uint local_40;
  uint local_3c;
  char *local_38;
  int *local_34;
  uint local_30;
  char *local_2c;
  char *local_28;
  int local_24;
  uint local_20;
  uint local_1c;
  char local_16;
  byte local_15;
  char local_14;
  char local_13;
  char local_12;
  char local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00479f9b;
  local_10 = ExceptionList;
  local_8 = 0;
  local_1c = 0;
  cVar1 = *param_2;
  local_13 = '\x01';
  local_12 = '\x01';
  if (cVar1 == '\0') {
    uVar11 = 0;
  }
  else if (cVar1 == '\x01') {
    uVar11 = *(uint *)(*(int *)(param_2 + 8) + 4);
  }
  else if (cVar1 == '\x02') {
    uVar11 = (*(int **)(param_2 + 8))[1] - **(int **)(param_2 + 8) >> 4;
  }
  else {
    uVar11 = 1;
  }
  ExceptionList = &local_10;
  local_38 = param_2;
  local_34 = param_1;
  local_20 = uVar11;
  FUN_00432ba0(param_1,uVar11);
  local_8 = 0;
  local_30 = 0;
  uVar13 = 1;
  local_1c = 1;
  if (uVar11 == 0) {
    ExceptionList = local_10;
    return param_1;
  }
  local_24 = 0;
  do {
    pcVar3 = (char *)FUN_00434550(local_38,local_30);
    local_16 = *pcVar3 == '\x02';
    local_28 = pcVar3;
    if ((bool)local_16) {
      pcVar3 = (char *)FUN_00434550(pcVar3,0);
    }
    FUN_00453970(pcVar3,(ushort *)&local_3c);
    uVar11 = local_3c & 0x3ff;
    local_11 = (local_3c & 0xfc00) == 0x400;
    uVar2 = (ushort)uVar11;
    puVar12 = (undefined4 *)(*param_1 + local_24);
    if ((((ushort)(uVar2 - 1) < 6) && (uVar2 != 3)) || ((0x1ff < uVar2 && (uVar2 < 0x204)))) {
      *puVar12 = 0;
      if (uVar2 < 7) {
        if (uVar2 < 5) {
          if (local_12 != '\0') {
            local_12 = '\0';
            iVar6 = GetSystemMetrics(0x17);
            local_14 = iVar6 != 0;
          }
          if (uVar2 == 1) {
            iVar6 = 2;
            if (local_14 != '\0') {
              iVar6 = 8;
            }
            puVar12[4] = ((local_11 != '\0') + 1) * iVar6;
          }
          else if (uVar2 == 2) {
            iVar6 = 8;
            if (local_14 != '\0') {
              iVar6 = 2;
            }
            puVar12[4] = ((local_11 != '\0') + 1) * iVar6;
          }
          else {
            puVar12[4] = ((local_11 != '\0') + 1) * 0x20;
          }
        }
        else {
          uVar7 = 0x80;
          if ((bool)local_11) {
            uVar7 = 0x100;
          }
          puVar12[4] = uVar7;
          puVar12[3] = (uVar2 != 5) + 1;
        }
      }
      else if (uVar2 < 0x202) {
        uVar7 = 0x1000;
        if (uVar2 == 0x200) {
          uVar7 = 0x800;
        }
        puVar12[4] = uVar7;
        cVar1 = *local_28;
        if (cVar1 == '\0') {
LAB_0040c430:
          in_XMM0_Da = 0.0;
          local_6c[0] = '\0';
          local_64 = 0;
          FUN_00450f50(local_6c,1);
          local_8 = 2;
          uVar11 = uVar13 | 4;
          pcVar3 = extraout_ECX;
        }
        else {
          if (cVar1 == '\x01') {
            uVar11 = *(uint *)(*(int *)(local_28 + 8) + 4);
          }
          else {
            if (cVar1 != '\x02') goto LAB_0040c430;
            uVar11 = (*(int **)(local_28 + 8))[1] - **(int **)(local_28 + 8) >> 4;
          }
          if (uVar11 < 4) goto LAB_0040c430;
          puVar8 = (undefined1 *)FUN_00434550(local_28,3);
          pcVar3 = FUN_00434940(local_7c,puVar8);
          local_8 = 1;
          uVar11 = uVar13 | 2;
        }
        local_1c = uVar11;
        FUN_00451420(pcVar3,(char *)&local_15);
        puVar12[3] = ((uint)((uVar2 == 0x200) == (bool)local_11) * 2 + -1) * (uint)local_15 * 0x78;
        if ((uVar11 & 4) != 0) {
          uVar11 = uVar11 & 0xfffffffb;
          local_1c = uVar11;
          FUN_00434820(local_6c);
        }
        local_8 = 0;
        uVar13 = local_1c;
        if ((uVar11 & 2) != 0) {
          local_1c = uVar11 & 0xfffffffd;
          FUN_00434820(local_7c);
          uVar13 = local_1c;
        }
      }
      if (local_16 != '\0') {
        if (local_13 != '\0') {
          local_13 = '\0';
          local_4c = GetSystemMetrics(0x4c);
          local_54 = GetSystemMetrics(0x4d);
          local_50 = GetSystemMetrics(0x4e);
          local_50 = local_50 + -1;
          local_58 = GetSystemMetrics(0x4f);
          local_58 = local_58 + -1;
        }
        pcVar3 = local_28;
        pcVar9 = (char *)FUN_00434550(local_28,1);
        FUN_004536b0(pcVar9,(uint *)&local_2c);
        local_28 = local_2c;
        pcVar3 = (char *)FUN_00434550(pcVar3,2);
        FUN_004536b0(pcVar3,&local_40);
        pcVar3 = local_28;
        local_44 = local_40;
        uVar11 = local_40;
        pcVar9 = local_2c;
        if (param_4 != '\0') {
          pt.y = local_40;
          pt.x = (LONG)local_28;
          pHVar10 = MonitorFromPoint(pt,2);
          FUN_00406610(pHVar10);
          local_48 = in_XMM0_Da;
          fVar14 = roundf((float)(int)pcVar3 * in_XMM0_Da);
          local_28 = (char *)(float)fVar14;
          in_XMM0_Da = (float)(int)local_44 * local_48;
          fVar15 = roundf(in_XMM0_Da);
          local_48 = (float)fVar15;
          uVar11 = (int)fVar15;
          pcVar9 = (char *)(int)fVar14;
        }
        puVar12[1] = (((int)pcVar9 - local_4c) * 0xffff) / local_50;
        puVar12[4] = puVar12[4] | 0xe001;
        puVar12[2] = (int)((uVar11 - local_54) * 0xffff) / local_58;
      }
      puVar12[6] = param_3;
    }
    else {
      *puVar12 = 1;
      *(short *)(puVar12 + 1) = (short)(local_3c & 0xff);
      UVar4 = MapVirtualKeyA(local_3c & 0xff,0);
      *(short *)((int)puVar12 + 6) = (short)UVar4;
      uVar5 = 0;
      if (local_11 != '\0') {
        uVar5 = 2;
      }
      puVar12[2] = uVar11 >> 8 & 1 | uVar5;
      puVar12[4] = param_3;
    }
    local_24 = local_24 + 0x1c;
    local_30 = local_30 + 1;
    param_1 = local_34;
    if (local_20 <= local_30) {
      ExceptionList = local_10;
      return local_34;
    }
  } while( true );
}


