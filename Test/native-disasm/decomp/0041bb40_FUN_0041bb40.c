// FUN_0041bb40 @ 0041bb40 size=1200 callers=1

void * __thiscall FUN_0041bb40(void *this,void *param_1)

{
  short *psVar1;
  char cVar2;
  int *piVar3;
  int *piVar4;
  int iVar5;
  undefined8 uVar6;
  void *pvVar7;
  undefined4 uVar8;
  char *pcVar9;
  undefined *puVar10;
  int iVar11;
  short sVar12;
  void *this_00;
  short sVar13;
  int iVar14;
  int *piVar15;
  int local_a4 [4];
  void *local_94;
  WNDCLASSEXA local_90;
  uint local_60;
  int local_5c;
  int local_58;
  int local_54;
  int local_50;
  byte *local_4c;
  char *local_48;
  int *local_44;
  int local_40;
  int local_3c;
  void *local_38;
  int local_34;
  undefined *puStack_30;
  int local_2c [2];
  undefined2 local_24;
  undefined1 auStack_22 [6];
  int local_1c [3];
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047b808;
  local_10 = ExceptionList;
  local_1c[1] = 0;
  ExceptionList = &local_10;
  *(undefined4 *)this = 0;
  *(undefined4 *)((int)this + 4) = 0;
  *(undefined4 *)((int)this + 8) = 0;
  local_94 = this;
  FUN_00435bf0(this,this,local_1c + 1);
  pvVar7 = param_1;
  *(undefined4 *)((int)this + 0xc) = 0;
  *(undefined4 *)((int)this + 0x10) = 0;
  *(undefined4 *)((int)this + 0x14) = 0;
  *(undefined8 *)((int)this + 0x20) = 0;
  *(undefined4 *)((int)this + 0x28) = 0;
  *(undefined4 *)((int)this + 0x2c) = 0;
  *(undefined4 *)((int)this + 0x30) = 0;
  local_8 = 2;
  *(undefined4 *)((int)this + 0x34) = 0;
  *(undefined4 *)((int)this + 0x38) = 0;
  *(undefined1 *)((int)this + 0x40) = 0;
  local_1c[1] = 0;
  *(undefined4 *)((int)this + 0x3c) = 0xffff;
  FUN_00441da0(local_2c,local_1c + 1,param_1);
  FUN_00436250(&DAT_004a28e0,(int *)&param_1,&DAT_0048d5bc);
  if (param_1 == DAT_004a28e4) {
                    /* WARNING: Subroutine does not return */
    FUN_00458ee4("invalid unordered_map<K, T> key");
  }
  cVar2 = *(char *)((int)param_1 + 0x24);
  local_4c = (byte *)((int)param_1 + 0xc);
  _local_24 = 0;
  local_2c[0] = 0;
  local_2c[1] = 0;
  *(uint *)((int)this + 0x1c) = (uint)(cVar2 == 'R');
  *(uint *)((int)this + 0x18) = (uint)(cVar2 != 'R');
  pvVar7 = (void *)FUN_00440dd0(pvVar7,(uint *)"items");
  FUN_00434120(pvVar7,&local_48);
  FUN_004340a0(this_00,local_a4);
  uVar8 = FUN_004383a0(&local_48,local_a4);
  param_1 = (void *)auStack_22._2_4_;
  iVar14 = _local_24;
  if ((char)uVar8 == '\0') {
    local_1c[1] = _local_24;
    piVar15 = local_44;
    do {
      pcVar9 = FUN_00433bc0(&local_48);
      if (DAT_004a2904 == DAT_004a2908) {
        FUN_004364b0(&DAT_004a2900,1);
      }
      local_38 = DAT_004a2904;
      _local_34 = CONCAT44(DAT_004a2904,local_34);
      local_8._0_1_ = 3;
      if (DAT_004a2904 != (void *)0x0) {
        FUN_00410fb0(DAT_004a2904,pcVar9,0);
      }
      DAT_004a2904 = (void *)((int)DAT_004a2904 + 0x28);
      local_8 = CONCAT31(local_8._1_3_,2);
      local_38 = (void *)(((int)DAT_004a2904 - DAT_004a2900) / 0x28 - 1);
      puVar10 = FUN_00419890((uint)local_38);
      if ((puVar10[0x24] != '3') && (*(int *)(puVar10 + 0x20) != 0)) {
        *(undefined1 *)((int)this + 0x40) = 1;
      }
      if ((puVar10[0x26] & 8) != 0) {
        piVar3 = *(int **)((int)this + 4);
        local_2c[*(int *)((int)this + 0x18)] = 0;
        local_2c[*(int *)((int)this + 0x1c)] =
             local_2c[*(int *)((int)this + 0x1c)] +
             (int)*(short *)((int)piVar3 + *(int *)((int)this + 0x1c) * 2 + -4);
        local_1c[0] = 0;
        puStack_30 = puVar10;
        if (local_1c < piVar3) {
          piVar4 = *(int **)this;
          if (local_1c < piVar4) goto LAB_0041bd7e;
          if (piVar3 == *(int **)((int)this + 8)) {
            FUN_00435b90(this);
          }
          if (*(undefined4 **)((int)this + 4) != (undefined4 *)0x0) {
            **(undefined4 **)((int)this + 4) =
                 *(undefined4 *)(*(int *)this + ((int)local_1c - (int)piVar4 >> 2) * 4);
          }
        }
        else {
LAB_0041bd7e:
          if (piVar3 == *(int **)((int)this + 8)) {
            FUN_00435b90(this);
          }
          puStack_30 = puVar10;
          if (*(int **)((int)this + 4) != (int *)0x0) {
            **(int **)((int)this + 4) = local_1c[0];
          }
        }
        *(int *)((int)this + 4) = *(int *)((int)this + 4) + 4;
        if (local_1c[1] < *(int *)((int)this + 0x20)) {
          local_1c[1] = *(int *)((int)this + 0x20);
        }
        *(int *)((int)this + 0x24) = *(int *)((int)this + 0x24) + (int)param_1;
        *(int *)((int)this + 0x20) = local_1c[1];
        local_1c[1] = 0;
        param_1 = (void *)0x0;
        puVar10 = puStack_30;
      }
      _local_34 = 0;
      uVar8 = FUN_0041a4e0(local_4c,puVar10,0,&local_34);
      iVar14 = local_1c[1] + local_34;
      _local_24 = (undefined1  [6])CONCAT42(uVar8,local_24);
      uVar6 = _local_24;
      puVar10 = puStack_30;
      if ((int)puStack_30 < (int)param_1) {
        puVar10 = param_1;
      }
      local_60 = (uint)local_38;
      local_54 = (short)uVar8 + local_2c[0];
      auStack_22._2_2_ = (undefined2)((uint)uVar8 >> 0x10);
      local_50 = (short)auStack_22._2_2_ + local_2c[1];
      local_5c = local_2c[0];
      local_58 = local_2c[1];
      param_1 = puVar10;
      _local_24 = uVar6;
      local_1c[1] = iVar14;
      FUN_00432140((void *)((int)this + 0xc),&local_60);
      psVar1 = (short *)(*(int *)((int)this + 4) + -4 + *(int *)((int)this + 0x18) * 2);
      *psVar1 = *psVar1 + *(short *)(auStack_22 + *(int *)((int)this + 0x18) * 2);
      iVar11 = *(int *)((int)this + 0x1c);
      iVar5 = *(int *)((int)this + 4);
      sVar12 = *(short *)(auStack_22 + iVar11 * 2);
      if (sVar12 < *(short *)(iVar5 + -4 + iVar11 * 2)) {
        sVar12 = *(short *)(iVar5 + -4 + iVar11 * 2);
      }
      *(short *)(iVar5 + -4 + iVar11 * 2) = sVar12;
      local_2c[*(int *)((int)this + 0x18)] =
           local_2c[*(int *)((int)this + 0x18)] +
           (int)*(short *)(auStack_22 + *(int *)((int)this + 0x18) * 2);
      if (*local_48 == '\x01') {
        if (*(char *)((int)piVar15 + 0xd) == '\0') {
          piVar3 = (int *)piVar15[2];
          if (*(char *)((int)piVar3 + 0xd) == '\0') {
            cVar2 = *(char *)(*piVar3 + 0xd);
            piVar15 = piVar3;
            piVar3 = (int *)*piVar3;
            while (local_44 = piVar15, cVar2 == '\0') {
              cVar2 = *(char *)(*piVar3 + 0xd);
              piVar15 = piVar3;
              piVar3 = (int *)*piVar3;
            }
          }
          else {
            cVar2 = *(char *)(piVar15[1] + 0xd);
            piVar4 = (int *)piVar15[1];
            piVar3 = piVar15;
            while ((piVar15 = piVar4, local_44 = piVar15, cVar2 == '\0' &&
                   (piVar3 == (int *)piVar15[2]))) {
              cVar2 = *(char *)(piVar15[1] + 0xd);
              piVar4 = (int *)piVar15[1];
              piVar3 = piVar15;
            }
          }
        }
      }
      else if (*local_48 == '\x02') {
        local_40 = local_40 + 0x10;
      }
      else {
        local_3c = local_3c + 1;
      }
      uVar8 = FUN_004383a0(&local_48,local_a4);
    } while ((char)uVar8 == '\0');
  }
  if (iVar14 < *(int *)((int)this + 0x20)) {
    iVar14 = *(int *)((int)this + 0x20);
  }
  *(int *)((int)this + 0x24) = *(int *)((int)this + 0x24) + (int)param_1;
  *(int *)((int)this + 0x20) = iVar14;
  iVar14 = *(int *)((int)this + 4);
  for (iVar11 = *(int *)this; iVar11 != iVar14; iVar11 = iVar11 + 4) {
    iVar5 = *(int *)((int)this + 0x18);
    sVar12 = *(short *)((int)this + iVar5 * 2 + 0x34);
    sVar13 = *(short *)(iVar11 + iVar5 * 2);
    if (sVar13 < sVar12) {
      sVar13 = sVar12;
    }
    *(short *)((int)this + iVar5 * 2 + 0x34) = sVar13;
    psVar1 = (short *)((int)this + *(int *)((int)this + 0x1c) * 2 + 0x34);
    *psVar1 = *psVar1 + *(short *)(iVar11 + *(int *)((int)this + 0x1c) * 2);
  }
  if ((*(int *)(*(int *)ThreadLocalStoragePointer + 8) < DAT_004a2e9c) &&
     (FUN_0045a219(&DAT_004a2e9c), DAT_004a2e9c == -1)) {
    local_90.cbSize = 0x30;
    local_90.style = 0x20000;
    local_90.lpfnWndProc = FUN_0041d100;
    local_90.cbClsExtra = 0;
    local_90.cbWndExtra = 0;
    local_90.hInstance = GetModuleHandleA((LPCSTR)0x0);
    local_90.hIcon = (HICON)0x0;
    local_90.hCursor = LoadCursorA((HINSTANCE)0x0,&DAT_00007f00);
    local_90.hbrBackground = (HBRUSH)0x10;
    local_90.lpszMenuName = (LPCSTR)0x0;
    local_90.lpszClassName = "ACNH_menu";
    local_90.hIconSm = (HICON)0x0;
    RegisterClassExA(&local_90);
    FUN_0045a1da(&DAT_004a2e9c);
  }
  ExceptionList = local_10;
  return this;
}


