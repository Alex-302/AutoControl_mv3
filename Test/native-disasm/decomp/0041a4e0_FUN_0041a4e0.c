// FUN_0041a4e0 @ 0041a4e0 size=718 callers=2

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __fastcall FUN_0041a4e0(byte *param_1,void *param_2,undefined4 param_3,int *param_4)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  float10 fVar7;
  float fVar8;
  float fVar9;
  ulonglong uVar10;
  undefined4 local_2c;
  int local_28;
  float local_24;
  float local_20;
  float local_1c;
  undefined4 local_18;
  double local_14;
  double local_c;
  
  FUN_00436020(&DAT_004a296c,&local_18,param_1);
  iVar3 = (int)local_18;
  if (local_18 == (float)DAT_004a2970) {
                    /* WARNING: Subroutine does not return */
    FUN_00458ee4("invalid unordered_map<K, T> key");
  }
  fVar8 = (float)DAT_004a29c8 * _DAT_0048f218;
  local_1c = (float)((int)*(short *)((int)local_18 + 0x30) + (int)*(short *)((int)local_18 + 0x2c) +
                    (int)*(short *)((int)local_18 + 0x2e)) * fVar8;
  fVar9 = (float)((int)*(short *)((int)local_18 + 0x32) + (int)*(short *)((int)local_18 + 0x2c) +
                 (int)*(short *)((int)local_18 + 0x2e)) * fVar8;
  local_c = (double)CONCAT44(local_c._4_4_,fVar9);
  if (*(char *)((int)param_2 + 0x24) != '\x01') {
    uVar1 = CONCAT31(local_24._1_3_,~(*(byte *)((int)param_2 + 0x26) >> 4));
    local_24 = (float)(uVar1 & 0xffffff01);
    uVar10 = CONCAT44(param_3,uVar1) & 0xffffffffffffff01;
    local_20 = fVar8;
    local_18 = (float)*(ushort *)((int)local_18 + 0x9c) * fVar8;
    FUN_0041a440(param_2,(char)uVar10,(char)(uVar10 >> 0x20));
    local_24 = 0.0;
    iVar4 = FUN_0041a380((int)param_2);
    if (iVar4 != 0) {
      fVar7 = roundf((float)*(byte *)((int)param_2 + 0x25) * local_20 * _DAT_0048f26c);
      iVar6 = (int)fVar7;
      local_28 = 0;
      local_18 = local_1c + local_1c + (float)iVar6;
      local_14 = (double)CONCAT44(local_14._4_4_,(iVar6 << 4) / 9 + 1);
      iVar5 = GdipGetImageHeight(*(undefined4 *)(iVar4 + 4),&local_28);
      iVar2 = local_28;
      if (iVar5 != 0) {
        *(int *)(iVar4 + 8) = iVar5;
      }
      local_24 = 0.0;
      iVar5 = GdipGetImageWidth(*(undefined4 *)(iVar4 + 4),&local_24);
      if (iVar5 != 0) {
        *(int *)(iVar4 + 8) = iVar5;
      }
      iVar4 = (iVar2 * iVar6) / (int)local_24;
      if (local_14._0_4_ < iVar4) {
        iVar6 = (local_14._0_4_ * iVar6) / iVar4;
        iVar4 = local_14._0_4_;
      }
      if (fVar8 <= (float)iVar6) {
        fVar8 = (float)iVar6;
      }
      local_24 = (float)(int)*(short *)(iVar3 + 0x38) * local_20 + (float)iVar4;
      if (param_4 != (int *)0x0) {
        *param_4 = iVar6;
        param_4[1] = iVar4;
      }
    }
    fVar8 = local_1c + local_1c + fVar8;
    fVar9 = local_18;
    if (fVar8 <= local_18) {
      fVar9 = fVar8;
    }
    local_14 = (double)fVar9;
    fVar7 = FUN_004766c0(local_14);
    local_14 = (double)fVar7;
    local_18 = (float)CONCAT22(local_18._2_2_,(short)(int)fVar7);
    local_c = (double)(local_c._0_4_ + local_c._0_4_ + (float)DAT_004a29c8 + local_24);
    fVar7 = FUN_004766c0(local_c);
    local_18 = (float)CONCAT22((short)(int)fVar7,(undefined2)local_18);
    return (int)local_18;
  }
  fVar9 = fVar8 + fVar8 + fVar9;
  local_2c = CONCAT22((short)(int)(fVar9 + fVar9),10);
  return local_2c;
}


