// FUN_0041c1c0 @ 0041c1c0 size=1424 callers=1

void __thiscall FUN_0041c1c0(void *this,uint param_1,LONG param_2,LONG param_3)

{
  POINT pt;
  uint uVar1;
  HMONITOR hMonitor;
  uint uVar2;
  void *pvVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  undefined *puVar7;
  int iVar8;
  HWND hWnd;
  short sVar9;
  int *piVar10;
  float10 fVar11;
  float fVar12;
  int iStack_bc;
  int iStack_b8;
  int iStack_b4;
  int local_b0;
  LONG LStack_ac;
  LONG LStack_a8;
  LONG LStack_a4;
  undefined8 local_a0;
  tagMONITORINFO local_98;
  undefined4 local_6c;
  int local_68;
  float local_64;
  byte *local_60;
  float local_5c [3];
  int local_50;
  int local_4c;
  undefined4 local_48;
  int local_44;
  void *local_40;
  HDC local_3c;
  HGDIOBJ local_38;
  uint local_34;
  float local_30;
  int *local_2c;
  int *local_28;
  undefined4 local_24;
  undefined1 *puStack_20;
  void *local_1c;
  undefined1 *puStack_18;
  undefined4 local_14;
  
  puStack_20 = &stack0xfffffffc;
  local_14 = 0xffffffff;
  puStack_18 = &LAB_0047b830;
  local_1c = ExceptionList;
  ExceptionList = &local_1c;
  local_28 = this;
  FUN_00436250(&DAT_004a28e0,(int *)&local_30,&DAT_0048d5bc);
  if (local_30 == DAT_004a28e4) {
                    /* WARNING: Subroutine does not return */
    FUN_00458ee4("invalid unordered_map<K, T> key");
  }
  local_60 = (byte *)((int)local_30 + 0xc);
  FUN_00436020(&DAT_004a296c,(int *)&local_34,local_60);
  uVar2 = local_34;
  if (local_34 == DAT_004a2970) {
                    /* WARNING: Subroutine does not return */
    FUN_00458ee4("invalid unordered_map<K, T> key");
  }
  pt.y = param_3;
  pt.x = param_2;
  hMonitor = MonitorFromPoint(pt,2);
  local_98.cbSize = 0x28;
  local_98.dwFlags = 0;
  local_98.rcMonitor.left = 0;
  local_98.rcMonitor.top = 0;
  local_98.rcMonitor.right = 0;
  local_98.rcMonitor.bottom = 0;
  local_98.rcWork.left = 0;
  local_98.rcWork.top = 0;
  local_98.rcWork.right = 0;
  local_98.rcWork.bottom = 0;
  GetMonitorInfoA(hMonitor,&local_98);
  uVar1 = local_34;
  uVar2 = (uint)*(ushort *)(uVar2 + 0x9e);
  local_a0 = CONCAT44(local_98.dwFlags,local_98.rcWork.bottom);
  local_24 = uVar2 * 2;
  iStack_bc = local_98.rcMonitor.left;
  iStack_b8 = local_98.rcMonitor.top;
  iStack_b4 = local_98.rcMonitor.right;
  local_40 = (void *)((local_98.rcMonitor.right - local_98.rcMonitor.left) + -0x20);
  pvVar3 = (void *)(local_24 + *(short *)((int)this + 0x34));
  if ((int)pvVar3 < (int)local_40) {
    local_40 = pvVar3;
  }
  local_b0 = local_98.rcMonitor.bottom;
  LStack_ac = local_98.rcWork.left;
  LStack_a8 = local_98.rcWork.top;
  LStack_a4 = local_98.rcWork.right;
  iVar4 = local_24 + *(short *)((int)this + 0x36);
  local_44 = (local_98.rcMonitor.bottom - local_98.rcMonitor.top) + -0x20;
  if (iVar4 < local_44) {
    local_44 = iVar4;
  }
  fVar12 = (float)(int)((int)local_40 + uVar2 * -2);
  local_64 = fVar12 / (float)(int)*(short *)((int)this + 0x34);
  local_5c[1] = (float)(int)(local_44 + uVar2 * -2) / (float)(int)*(short *)((int)this + 0x36);
  local_5c[0] = local_64;
  local_30 = local_5c[1];
  if (((*(int *)((int)this + 0x1c) != 0) && (*(int *)((int)this + 0x24) != 0)) &&
     (local_64 < local_5c[1])) {
    local_2c = (int *)(fVar12 / (float)*(int *)((int)this + 0x20));
    fVar11 = roundf((float)((local_24 - *(int *)((int)this + 0x24)) +
                           (int)*(short *)((int)this + 0x36)) +
                    (float)*(int *)((int)this + 0x24) * (float)local_2c);
    local_30 = (float)fVar11;
    if ((int)fVar11 <= local_44) {
      fVar11 = roundf((float)(((int)*(short *)((int)this + 0x36) - *(int *)((int)this + 0x24)) +
                             local_24) + (float)*(int *)((int)this + 0x24) * (float)local_2c);
      local_44 = (int)fVar11;
    }
    local_30 = (float)(local_44 - local_24) / (float)(int)*(short *)((int)this + 0x36);
  }
  local_5c[1] = local_30;
  local_2c = FUN_0040a870(&local_3c,local_40,local_44);
  DeleteDC(*(HDC *)((int)this + 0x2c));
  DeleteObject(*(HGDIOBJ *)((int)this + 0x30));
  local_28[0xb] = *local_2c;
  local_28[0xc] = local_2c[1];
  *local_2c = 0;
  local_2c[1] = 0;
  DeleteDC(local_3c);
  DeleteObject(local_38);
  local_48 = 0;
  iVar4 = GdipCreateFromHDC(local_28[0xb],&local_48);
  local_6c = local_48;
  local_14 = 0;
  iVar5 = GdipGraphicsClear(local_48,*(undefined4 *)(local_34 + 0x90));
  local_5c[2] = 0.0;
  if (iVar5 != 0) {
    iVar4 = iVar5;
  }
  local_50 = GdipCreatePen1(0x78808080,0x3f800000,0,local_5c + 2);
  local_14 = CONCAT31(local_14._1_3_,1);
  iVar5 = GdipSetPenMode(local_5c[2],1);
  if (iVar5 != 0) {
    local_50 = iVar5;
  }
  iVar5 = GdipDrawRectangleI(local_48,local_5c[2],0,0,(int)local_40 + -1,local_44 + -1);
  local_68 = iVar4;
  if (iVar5 != 0) {
    local_68 = iVar5;
  }
  local_4c = 0;
  local_34 = 0;
  iVar4 = local_28[4] - local_28[3] >> 0x1f;
  piVar10 = local_28;
  if ((local_28[4] - local_28[3]) / 0x14 + iVar4 != iVar4) {
    piVar6 = (int *)0x0;
    do {
      local_38 = (HGDIOBJ)((int)piVar6 * 0x14);
      puVar7 = FUN_00419890(*(uint *)(piVar10[3] + (int)local_38));
      iVar4 = local_4c + 1;
      if ((puVar7[0x26] & 8) == 0) {
        iVar4 = local_4c;
      }
      local_2c = (int *)0x0;
      sVar9 = 0;
      local_24 = 0;
      if (local_60[0x19] != 0) {
        iVar5 = piVar10[6];
        iVar8 = ((int)*(short *)((int)local_28 + iVar5 * 2 + 0x34) -
                (int)*(short *)(*local_28 + (iVar5 + iVar4 * 2) * 2)) / 2;
        *(short *)((int)&local_24 + iVar5 * 2) = (short)iVar8;
        local_2c = (int *)CONCAT22((short)((uint)iVar8 >> 0x10),local_24._2_2_);
        sVar9 = (short)local_24;
        piVar10 = local_28;
      }
      iVar5 = piVar10[3] + (int)local_38;
      local_4c = iVar4;
      fVar11 = roundf((float)((int)sVar9 + *(int *)(iVar5 + 4)) * local_64);
      local_38 = (HGDIOBJ)(float)fVar11;
      *(uint *)(iVar5 + 4) = (uint)*(ushort *)(uVar1 + 0x9e) + (int)fVar11;
      fVar11 = roundf((float)((int)(short)local_2c + *(int *)(iVar5 + 8)) * local_30);
      local_38 = (HGDIOBJ)(float)fVar11;
      *(uint *)(iVar5 + 8) = (uint)*(ushort *)(uVar1 + 0x9e) + (int)fVar11;
      iVar4 = local_28[6];
      fVar11 = roundf((float)(*(int *)(iVar5 + 0xc + iVar4 * 4) +
                             (int)*(short *)((int)&local_24 + iVar4 * 2)) * local_5c[iVar4]);
      local_38 = (HGDIOBJ)(float)fVar11;
      *(uint *)(iVar5 + 0xc + local_28[6] * 4) = (uint)*(ushort *)(uVar1 + 0x9e) + (int)fVar11;
      iVar4 = local_28[7];
      fVar11 = roundf((float)(int)*(short *)(*local_28 + (iVar4 + local_4c * 2) * 2) *
                      local_5c[iVar4] + (float)*(int *)(iVar5 + 4 + iVar4 * 4));
      piVar10 = local_28;
      local_38 = (HGDIOBJ)(float)fVar11;
      *(int *)(iVar5 + 0xc + local_28[7] * 4) = (int)fVar11;
      FUN_0041c080(local_28,(ushort)local_34);
      local_34 = local_34 + 1;
      piVar6 = (int *)(local_34 & 0xffff);
      local_2c = piVar6;
    } while (piVar6 < (int *)((piVar10[4] - piVar10[3]) / 0x14));
  }
  iVar4 = local_44;
  FUN_0041c750(&param_2,(int)local_40,local_44,&iStack_bc,param_1);
  hWnd = CreateWindowExA(0x8080088,"ACNH_menu","",0x80000000,param_2,param_3,(int)local_40,iVar4,
                         (HWND)0x0,(HMENU)0x0,(HINSTANCE)0x0,(LPVOID)0x0);
  piVar10[10] = (int)hWnd;
  ShowWindow(hWnd,4);
  FUN_0041c140((int)piVar10);
  GdipDeletePen(local_5c[2]);
  GdipDeleteGraphics(local_48);
  ExceptionList = local_1c;
  return;
}


