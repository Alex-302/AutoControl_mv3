// FUN_0041cbf0 @ 0041cbf0 size=625 callers=4

void __thiscall FUN_0041cbf0(void *this,char param_1,char param_2)

{
  char cVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined *puVar6;
  ushort uVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint local_40;
  ushort local_3c;
  SIZE local_28;
  tagRECT local_20;
  
  cVar1 = param_2;
  if (*(int *)((int)this + 0x18) == 0) {
    cVar1 = param_1;
  }
  if (*(int *)((int)this + 0x1c) == 0) {
    param_2 = param_1;
  }
  uVar7 = *(ushort *)((int)this + 0x3c);
  if (uVar7 == 0xffff) {
    uVar7 = (short)((*(int *)((int)this + 0x10) - *(int *)((int)this + 0xc)) / 0x14) -
            (ushort)('\0' < cVar1);
  }
  uVar11 = (uint)uVar7;
  local_40 = 0;
  iVar8 = *(int *)((int)this + 0x10) - *(int *)((int)this + 0xc);
  iVar10 = iVar8 >> 0x1f;
  if (iVar8 / 0x14 + iVar10 != iVar10) {
    do {
      iVar10 = (*(int *)((int)this + 0x10) - *(int *)((int)this + 0xc)) / 0x14;
      uVar9 = (iVar10 + (int)(uVar11 + (int)cVar1) % iVar10) % iVar10;
      uVar12 = uVar9 & 0xffff;
      uVar11 = uVar12;
      if (param_2 != '\0') {
        iVar10 = *(int *)((int)this + 0xc) + uVar12 * 0x14;
        iVar5 = *(int *)((int)this + 0xc) + uVar12 * 0x14 + 0xc;
        iVar8 = *(int *)(iVar5 + *(int *)((int)this + 0x18) * 4);
        iVar3 = *(int *)(iVar10 + 4 + *(int *)((int)this + 0x18) * 4);
        iVar4 = *(int *)((int)this + 0x1c);
        if (param_2 < '\x01') {
          iVar10 = *(int *)(iVar10 + 4 + iVar4 * 4);
        }
        else {
          iVar10 = *(int *)(iVar5 + iVar4 * 4);
        }
        local_28.cx = (LONG)*(short *)((int)this + iVar4 * 2 + 0x34);
        uVar13 = 0;
        local_20.left = param_2 * 10;
        do {
          iVar10 = (local_28.cx + (local_20.left + iVar10) % local_28.cx) % local_28.cx;
          uVar7 = FUN_0041cae0(this,(iVar8 + iVar3) / 2,iVar10);
          if ((uVar7 != 0xffff) &&
             (local_3c = (ushort)uVar9, uVar11 = (uint)uVar7, uVar7 != local_3c)) break;
          uVar13 = uVar13 + 1;
          uVar11 = uVar12;
        } while (uVar13 < 5);
      }
      uVar7 = (ushort)uVar11;
      puVar6 = FUN_00419890(*(uint *)(*(int *)((int)this + 0xc) + uVar11 * 0x14));
    } while ((puVar6[0x24] == '\x03') &&
            (local_40 = local_40 + 1,
            local_40 < (uint)((*(int *)((int)this + 0x10) - *(int *)((int)this + 0xc)) / 0x14)));
  }
  uVar2 = *(ushort *)((int)this + 0x3c);
  if (uVar7 != uVar2) {
    *(ushort *)((int)this + 0x3c) = uVar7;
    if (uVar7 == 0xffff) {
      DAT_004a29c0 = 0;
    }
    else {
      DAT_004a29c0 = *(undefined4 *)(*(int *)((int)this + 0xc) + (uint)uVar7 * 0x14);
    }
    FUN_0041c080(this,uVar2);
    FUN_0041c080(this,*(ushort *)((int)this + 0x3c));
    local_20.left = 0;
    local_20.top = 0;
    local_20.right = 0;
    local_20.bottom = 0;
    GetWindowRect(*(HWND *)((int)this + 0x28),&local_20);
    local_28.cy = local_20.bottom - local_20.top;
    local_28.cx = local_20.right - local_20.left;
    local_20.left = 0;
    local_20.top = 0;
    UpdateLayeredWindow(*(HWND *)((int)this + 0x28),(HDC)0x0,(POINT *)0x0,&local_28,
                        *(HDC *)((int)this + 0x2c),(POINT *)&local_20,0,
                        (BLENDFUNCTION *)&DAT_0049d9e8,2);
  }
  return;
}


