// FUN_00442bd0 @ 00442bd0 size=182 callers=1

void __thiscall FUN_00442bd0(void *this,int param_1,int param_2)

{
  undefined1 *puVar1;
  undefined1 uVar2;
  byte bVar3;
  bool bVar4;
  undefined1 *puVar5;
  uint uVar6;
  int iVar7;
  undefined1 *puVar8;
  uint uVar9;
  longlong lVar10;
  
  lVar10 = CONCAT44(param_2,param_1);
  if (param_1 == 0 && param_2 == 0) {
    FUN_0043e220(*(void **)this,0x30);
    return;
  }
  if ((param_2 < 1) && (param_2 < 0)) {
    bVar4 = true;
  }
  else {
    bVar4 = false;
  }
  uVar9 = 0;
  do {
    uVar6 = (uint)lVar10;
    if (0x3e < uVar9) break;
    lVar10 = __alldiv(uVar6,(uint)((ulonglong)lVar10 >> 0x20),10,0);
    iVar7 = uVar6 + (int)lVar10 * -10;
    bVar3 = (byte)(iVar7 >> 0x1f);
    *(byte *)(uVar9 + 4 + (int)this) = (((byte)iVar7 ^ bVar3) - bVar3) + '0';
    uVar9 = uVar9 + 1;
  } while (lVar10 != 0);
  if (bVar4) {
    *(undefined1 *)(uVar9 + 4 + (int)this) = 0x2d;
    uVar9 = uVar9 + 1;
  }
  puVar1 = (undefined1 *)((int)this + 4);
  puVar5 = puVar1 + uVar9;
  puVar8 = puVar1;
  if (puVar1 != puVar5) {
    do {
      puVar5 = puVar5 + -1;
      if (puVar8 == puVar5) break;
      uVar2 = *puVar8;
      *puVar8 = *puVar5;
      puVar8 = puVar8 + 1;
      *puVar5 = uVar2;
    } while (puVar8 != puVar5);
  }
  FUN_0043e0b0(*(void **)this,puVar1,uVar9,0);
  return;
}


