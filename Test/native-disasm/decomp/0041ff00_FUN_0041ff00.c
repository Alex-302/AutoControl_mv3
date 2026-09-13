// FUN_0041ff00 @ 0041ff00 size=335 callers=1

bool __thiscall FUN_0041ff00(void *this,byte param_1,undefined4 param_2,ushort param_3)

{
  short sVar1;
  void *pvVar2;
  char *_Buf;
  bool bVar3;
  void *pvVar4;
  uint uVar5;
  void *pvVar6;
  int iVar7;
  uint uVar8;
  tagPOINT tVar9;
  
  pvVar2 = *(void **)((int)this + 4);
  _Buf = *(char **)this;
  if (((int)pvVar2 - (int)_Buf != 1) || (*_Buf != '\0')) {
    pvVar4 = _memchr(_Buf,(uint)*(byte *)((int)this + 0x44),(int)pvVar2 - (int)_Buf);
    pvVar6 = pvVar2;
    if (pvVar4 != (void *)0x0) {
      pvVar6 = pvVar4;
    }
    if (pvVar6 != pvVar2) {
      bVar3 = FUN_00413200((ushort *)&DAT_004a26b0);
      if (bVar3) {
        FUN_004059a0(this,*(byte *)((int)this + 0x44));
        goto LAB_00420025;
      }
    }
    pvVar2 = *(void **)((int)this + 4);
    pvVar4 = _memchr(*(void **)this,(uint)param_1,(int)pvVar2 - (int)*(void **)this);
    pvVar6 = pvVar2;
    if (pvVar4 != (void *)0x0) {
      pvVar6 = pvVar4;
    }
    if (pvVar6 != pvVar2) {
      bVar3 = FUN_00413200((ushort *)&DAT_004a26b0);
      if ((bVar3) && ((DAT_004a26c2 & 0xfc00) != 0x1800)) {
        iVar7 = *(int *)((int)this + 0x14);
      }
      else {
        iVar7 = *(int *)((int)this + 0x30);
        if ((uint)(*(int *)((int)this + 0x14) - *(int *)((int)this + 0x30)) < 0x7fffffff) {
          iVar7 = *(int *)((int)this + 0x14);
        }
      }
      sVar1 = *(short *)((int)this + 0x18);
      if ((int)(uint)param_3 < DAT_004a26b4 - iVar7) {
LAB_0041ffdc:
        FUN_004059a0(this,param_1);
        return false;
      }
      if (((DAT_004a26b0 == sVar1) && ((ushort)(sVar1 - 1U) < 6)) && (sVar1 != 3)) {
        tVar9 = FUN_00404b80();
        uVar5 = tVar9.x - *(int *)((int)this + 0xc);
        uVar8 = (int)uVar5 >> 0x1f;
        if ((5 < (int)((uVar5 ^ uVar8) - uVar8)) ||
           (uVar5 = tVar9.y - *(int *)((int)this + 0x10), uVar8 = (int)uVar5 >> 0x1f,
           5 < (int)((uVar5 ^ uVar8) - uVar8))) goto LAB_0041ffdc;
      }
    }
  }
LAB_00420025:
  pvVar2 = *(void **)((int)this + 4);
  pvVar4 = _memchr(*(void **)this,(uint)param_1,(int)pvVar2 - (int)*(void **)this);
  pvVar6 = pvVar2;
  if (pvVar4 != (void *)0x0) {
    pvVar6 = pvVar4;
  }
  return pvVar6 != pvVar2;
}


