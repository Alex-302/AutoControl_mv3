// FUN_0044aef0 @ 0044aef0 size=351 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool __thiscall FUN_0044aef0(void *this,double *param_1)

{
  uint *puVar1;
  int iVar2;
  char cVar3;
  lconv *plVar4;
  void *pvVar5;
  wchar_t ****ppppwVar6;
  void *pvVar7;
  int iVar8;
  bool bVar9;
  wchar_t **local_7c [17];
  wchar_t ***local_38 [4];
  undefined4 local_28;
  uint local_24;
  wchar_t *local_20;
  undefined8 local_1c;
  char local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_004792a8;
  local_10 = ExceptionList;
  local_24 = 0xf;
  local_28 = 0;
  local_38[0] = (wchar_t ***)((uint)local_38[0] & 0xffffff00);
  local_8 = 0;
  iVar8 = *(int *)((int)this + 4) - *(int *)this;
  ExceptionList = &local_10;
  plVar4 = _localeconv();
  if (plVar4->decimal_point == (char *)0x0) {
    local_11 = '.';
  }
  else {
    local_11 = *plVar4->decimal_point;
  }
  ppppwVar6 = *(wchar_t *****)this;
  if (local_11 != '.') {
    local_1c._4_4_ = *(void **)((int)this + 4);
    pvVar5 = _memchr(ppppwVar6,0x2e,(int)*(void **)((int)this + 4) - (int)ppppwVar6);
    puVar1 = *(uint **)this;
    pvVar7 = local_1c._4_4_;
    if (pvVar5 != (void *)0x0) {
      pvVar7 = pvVar5;
    }
    local_1c = (double)CONCAT44((int)pvVar7 - (int)puVar1,(undefined4)local_1c);
    if ((int)pvVar7 - (int)puVar1 != iVar8) {
      if (iVar8 + 1U < 0x40) {
        FUN_0045b0e0((uint *)local_7c,puVar1,*(int *)((int)this + 4) - (int)puVar1);
        cVar3 = local_11;
        iVar2 = (int)local_1c._4_4_;
        *(undefined1 *)((int)local_7c + iVar8) = 0;
        *(char *)((int)local_7c + iVar2) = cVar3;
        ppppwVar6 = (wchar_t ****)local_7c;
      }
      else {
        FUN_0044d8d0(local_38,puVar1,*(uint **)((int)this + 4));
        ppppwVar6 = local_38;
        if (0xf < local_24) {
          ppppwVar6 = (wchar_t ****)local_38[0];
        }
        *(char *)((int)ppppwVar6 + (int)local_1c._4_4_) = local_11;
        ppppwVar6 = local_38;
        if (0xf < local_24) {
          ppppwVar6 = (wchar_t ****)local_38[0];
        }
      }
    }
  }
  local_20 = (wchar_t *)0x0;
  *param_1 = 0.0;
  local_1c = FID_conflict__strtod((wchar_t *)ppppwVar6,&local_20);
  bVar9 = local_20 == (wchar_t *)((int)ppppwVar6 + iVar8);
  *param_1 = local_1c;
  if (((bVar9) && (local_1c == _DAT_0048f210)) && (*(char *)ppppwVar6 == '-')) {
    *param_1 = DAT_0048f2b0;
  }
  if (0xf < local_24) {
    FUN_00402430(local_38[0],local_24 + 1,1);
  }
  ExceptionList = local_10;
  return bVar9;
}


