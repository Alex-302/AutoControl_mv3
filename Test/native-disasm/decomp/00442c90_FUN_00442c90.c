// FUN_00442c90 @ 00442c90 size=153 callers=1

void __thiscall FUN_00442c90(void *this,int param_1,uint param_2)

{
  undefined1 *puVar1;
  undefined1 uVar2;
  byte bVar3;
  undefined1 *puVar4;
  uint uVar5;
  int iVar6;
  undefined1 *puVar7;
  uint uVar8;
  longlong lVar9;
  
  lVar9 = CONCAT44(param_1,param_1);
  if (param_1 == 0 && param_2 == 0) {
    FUN_0043e220(*(void **)this,0x30);
    return;
  }
  uVar8 = 0;
  do {
    uVar5 = (uint)lVar9;
    if (0x3e < uVar8) break;
    lVar9 = __aulldiv(uVar5,param_2,10,0);
    param_2 = (uint)((ulonglong)lVar9 >> 0x20);
    iVar6 = uVar5 + (int)lVar9 * -10;
    bVar3 = (byte)(iVar6 >> 0x1f);
    *(byte *)(uVar8 + 4 + (int)this) = (((byte)iVar6 ^ bVar3) - bVar3) + '0';
    uVar8 = uVar8 + 1;
  } while (lVar9 != 0);
  puVar1 = (undefined1 *)((int)this + 4);
  puVar4 = puVar1 + uVar8;
  puVar7 = puVar1;
  if (puVar1 != puVar4) {
    do {
      puVar4 = puVar4 + -1;
      if (puVar7 == puVar4) break;
      uVar2 = *puVar7;
      *puVar7 = *puVar4;
      puVar7 = puVar7 + 1;
      *puVar4 = uVar2;
    } while (puVar7 != puVar4);
  }
  FUN_0043e0b0(*(void **)this,puVar1,uVar8,0);
  return;
}


