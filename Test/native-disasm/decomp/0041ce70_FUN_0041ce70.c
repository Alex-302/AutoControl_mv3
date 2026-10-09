// FUN_0041ce70 @ 0041ce70 size=293 callers=1

void __thiscall FUN_0041ce70(void *this,char param_1)

{
  int iVar1;
  undefined *puVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  SIZE local_28;
  tagRECT local_20;
  
  uVar5 = 0;
  local_20.left = (LONG)*(ushort *)((int)this + 0x3e);
  iVar3 = *(int *)((int)this + 0x10) - *(int *)((int)this + 0xc);
  iVar1 = iVar3 >> 0x1f;
  if (iVar3 / 0x14 + iVar1 != iVar1) {
    local_28.cx = (LONG)param_1;
    do {
      iVar1 = (*(int *)((int)this + 0x10) - *(int *)((int)this + 0xc)) / 0x14;
      uVar4 = (iVar1 + (int)((uint)*(ushort *)((int)this + 0x3e) + local_28.cx) % iVar1) % iVar1;
      *(short *)((int)this + 0x3e) = (short)uVar4;
      DAT_004a29bc = *(uint *)(*(int *)((int)this + 0xc) + (uVar4 & 0xffff) * 0x14);
      puVar2 = FUN_00419890(DAT_004a29bc);
      if (puVar2[0x24] != '\x03') break;
      uVar5 = uVar5 + 1;
    } while (uVar5 < (uint)((*(int *)((int)this + 0x10) - *(int *)((int)this + 0xc)) / 0x14));
  }
  FUN_0041c080(this,(ushort)local_20.left);
  FUN_0041c080(this,*(ushort *)((int)this + 0x3e));
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
                      *(HDC *)((int)this + 0x2c),(POINT *)&local_20,0,(BLENDFUNCTION *)&DAT_0049d9e8
                      ,2);
  return;
}


