// FUN_00419190 @ 00419190 size=752 callers=2

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_00419190(void *this,int *param_1,char param_2)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  void *pvVar5;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 *puVar6;
  float10 fVar7;
  double dVar8;
  double dVar9;
  float fVar10;
  uint uVar11;
  uint uVar12;
  float fVar13;
  undefined **local_60;
  char local_5c;
  undefined ***local_3c;
  double local_38;
  undefined8 local_30;
  float local_28;
  char local_21;
  undefined1 *puStack_20;
  void *local_1c;
  undefined1 *puStack_18;
  undefined4 local_14;
  
  puStack_20 = &stack0xfffffffc;
  local_14 = 0xffffffff;
  puStack_18 = &LAB_0047b308;
  local_1c = ExceptionList;
  if ((param_2 != '\0') || (*(char *)((int)this + 0x38) != 'B')) {
    iVar3 = *(int *)((int)this + 0x18) - *param_1;
    iVar4 = *(int *)((int)this + 0x1c) - param_1[1];
    pvVar5 = (void *)(iVar4 * iVar4);
    dVar8 = (double)(int)(iVar3 * iVar3 + (int)pvVar5);
    ExceptionList = &local_1c;
    __libm_sse2_sqrt_precise(pvVar5);
    if ((double)DAT_0049d9ec <= dVar8) {
      iVar3 = param_1[1] - *(int *)((int)this + 0x1c);
      local_30 = (double)iVar3;
      fVar7 = (float10)FUN_00477f7a(iVar3);
      local_30 = (double)fVar7;
      local_28 = (float)fVar7 + DAT_004a2848;
      iVar3 = FUN_00419120(extraout_ECX);
      if ((char)iVar3 != *(char *)((int)this + 0x34)) {
        fVar13 = *(float *)((int)this + 0x2c) - local_28;
        dVar8 = (double)fVar13;
        uVar11 = (uint)DAT_0048f2e0;
        uVar12 = (uint)((ulonglong)DAT_0048f2e0 >> 0x20);
        fVar10 = (float)(double)CONCAT44((uint)((ulonglong)dVar8 >> 0x20) & uVar12,
                                         SUB84(dVar8,0) & uVar11);
        dVar8 = (double)(DAT_004a2848 * DAT_0048f248 - fVar10);
        dVar9 = (double)fVar13;
        dVar9 = (double)CONCAT44((uint)((ulonglong)dVar9 >> 0x20) & uVar12,SUB84(dVar9,0) & uVar11);
        if ((float)(double)CONCAT44((uint)((ulonglong)dVar8 >> 0x20) & uVar12,
                                    SUB84(dVar8,0) & uVar11) <= fVar10) {
          dVar8 = (double)(DAT_004a2848 * DAT_0048f248 - (float)dVar9);
          dVar9 = (double)CONCAT44((uint)((ulonglong)dVar8 >> 0x20) & uVar12,SUB84(dVar8,0) & uVar11
                                  );
        }
        if ((*(char *)((int)this + 0x35) == '\0') ||
           (((float)DAT_0049da08 * DAT_004a2848) / _DAT_0048f288 <
            (float)dVar9 - *(float *)((int)this + 0x30))) {
          *(undefined4 *)((int)this + 0x20) = *(undefined4 *)((int)this + 0x18);
          *(undefined4 *)((int)this + 0x24) = *(undefined4 *)((int)this + 0x1c);
          *(undefined1 *)((int)this + 0x35) = 1;
          *(float *)((int)this + 0x30) = (float)dVar9;
        }
      }
      *(float *)((int)this + 0x2c) = local_28;
      *(int *)((int)this + 0x18) = *param_1;
      *(int *)((int)this + 0x1c) = param_1[1];
    }
    if (*(char *)((int)this + 0x35) != '\0') {
      local_28 = (float)param_1[1];
      iVar4 = *(int *)((int)this + 0x24) - (int)local_28;
      iVar3 = *(int *)((int)this + 0x20) - *param_1;
      pvVar5 = (void *)(iVar4 * iVar4);
      local_30 = (double)CONCAT44(*param_1,(undefined4)local_30);
      dVar8 = (double)(int)(iVar3 * iVar3 + (int)pvVar5);
      __libm_sse2_sqrt_precise(pvVar5);
      puVar6 = &DAT_004a2538;
      if (0xf < DAT_004a254c) {
        puVar6 = DAT_004a2538;
      }
      if ((double)(int)((uint)(byte)(*(char *)((int)puVar6 + 0x2a) - *(char *)(puVar6 + 0xd)) *
                       DAT_0049da00) < dVar8) {
        iVar3 = (int)local_28 - *(int *)((int)this + 0x24);
        local_30 = (double)iVar3;
        local_38 = dVar8;
        fVar7 = (float10)FUN_00477f7a(iVar3);
        local_30 = (double)fVar7;
        iVar3 = FUN_00419120(extraout_ECX_00);
        local_21 = (char)iVar3;
        if (local_21 != *(char *)((int)this + 0x34)) {
          if (*(char *)((int)this + 0x37) != 'C') {
            *(undefined1 *)((int)this + 0x37) = 0x43;
            if (*(int *)((int)this + 0x28) != 0) {
              FUN_0040fb40((UINT_PTR *)(*(int *)((int)this + 0x28) + 0x10),'\x01');
            }
          }
          if (*(uint *)((int)this + 0x10) < 0x1e) {
            cVar1 = local_21 + '1';
            local_30._0_5_ = CONCAT14(cVar1,(undefined4)local_30);
            FUN_0043aef0(this,1,cVar1);
            bVar2 = FUN_004195f0(this,cVar1,(int)local_38 & 0xffff);
            if (!bVar2) {
              local_5c = local_21;
              local_3c = &local_60;
              local_60 = &PTR_LAB_0048e908;
              local_14 = 0;
              FUN_0040fad0((int *)local_3c);
              FUN_0040fe40((int *)&local_60);
            }
          }
          *(char *)((int)this + 0x34) = local_21;
        }
        *(undefined1 *)((int)this + 0x35) = 0;
        if (*(int *)((int)this + 0x28) != 0) {
          *(undefined1 *)(*(int *)((int)this + 0x28) + 0x1f) = 0x44;
        }
      }
    }
  }
  ExceptionList = local_1c;
  return;
}


