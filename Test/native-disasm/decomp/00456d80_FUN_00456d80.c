// FUN_00456d80 @ 00456d80 size=504 callers=1

void __thiscall FUN_00456d80(void *this,uint *param_1,uint *param_2)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint *puVar5;
  void *_Memory;
  uint ****ppppuVar6;
  byte *pbVar7;
  uint uVar8;
  bool bVar9;
  void *local_64 [5];
  uint local_50;
  uint ***local_4c [4];
  uint local_3c;
  uint local_38;
  undefined4 *local_34;
  void *local_30;
  int local_2c;
  uint local_28;
  undefined1 local_21;
  undefined1 *local_20;
  void *local_1c;
  undefined1 *puStack_18;
  undefined4 local_14;
  
  local_20 = &stack0xfffffffc;
  local_14 = 0xffffffff;
  puStack_18 = &LAB_0047eb58;
  local_1c = ExceptionList;
  local_2c = *(int *)((int)this + 4);
  ExceptionList = &local_1c;
  local_30 = this;
  FUN_00457580((uint *)local_4c,param_1,param_2);
  local_14 = 0;
  local_28 = 0;
  do {
    local_21 = (undefined1)local_28;
    puVar5 = FUN_00457580((uint *)local_64,(uint *)&local_21,(uint *)&local_20);
    ppppuVar6 = local_4c;
    if (0xf < local_38) {
      ppppuVar6 = (uint ****)local_4c[0];
    }
    puVar1 = puVar5 + 4;
    if (0xf < puVar5[5]) {
      puVar5 = (uint *)*puVar5;
    }
    uVar2 = *puVar1;
    uVar8 = local_3c;
    if (uVar2 < local_3c) {
      uVar8 = uVar2;
    }
    if (uVar8 == 0) {
LAB_00456e77:
      if (uVar2 < local_3c) {
        uVar8 = 0xffffffff;
      }
      else {
        uVar8 = (uint)(local_3c < uVar2);
      }
    }
    else {
      while (uVar3 = uVar8 - 4, 3 < uVar8) {
        if ((uint ***)*puVar5 != *ppppuVar6) goto LAB_00456e3a;
        puVar5 = puVar5 + 1;
        ppppuVar6 = ppppuVar6 + 1;
        uVar8 = uVar3;
      }
      if (uVar3 == 0xfffffffc) {
LAB_00456e6e:
        uVar8 = 0;
      }
      else {
LAB_00456e3a:
        bVar9 = (byte)*puVar5 < *(byte *)ppppuVar6;
        if (((byte)*puVar5 == *(byte *)ppppuVar6) &&
           ((uVar3 == 0xfffffffd ||
            ((bVar9 = *(byte *)((int)puVar5 + 1) < *(byte *)((int)ppppuVar6 + 1),
             *(byte *)((int)puVar5 + 1) == *(byte *)((int)ppppuVar6 + 1) &&
             ((uVar3 == 0xfffffffe ||
              ((bVar9 = *(byte *)((int)puVar5 + 2) < *(byte *)((int)ppppuVar6 + 2),
               *(byte *)((int)puVar5 + 2) == *(byte *)((int)ppppuVar6 + 2) &&
               ((uVar3 == 0xffffffff ||
                (bVar9 = *(byte *)((int)puVar5 + 3) < *(byte *)((int)ppppuVar6 + 3),
                *(byte *)((int)puVar5 + 3) == *(byte *)((int)ppppuVar6 + 3)))))))))))))
        goto LAB_00456e6e;
        uVar8 = -(uint)bVar9 | 1;
      }
      if (uVar8 == 0) goto LAB_00456e77;
    }
    if (0xf < local_50) {
      _Memory = local_64[0];
      if ((0xfff < local_50 + 1) &&
         ((((((uint)local_64[0] & 0x1f) != 0 ||
            (_Memory = *(void **)((int)local_64[0] + -4), local_64[0] <= _Memory)) ||
           ((uint)((int)local_64[0] - (int)_Memory) < 4)) ||
          (0x23 < (uint)((int)local_64[0] - (int)_Memory))))) goto LAB_00456f31;
      FID_conflict__free(_Memory);
    }
    iVar4 = local_2c;
    if (uVar8 == 0) {
      if (*(int *)(local_2c + 0x18) == 0) {
        local_34 = operator_new(0x20);
        *local_34 = 0;
        local_34[1] = 0;
        local_34[2] = 0;
        local_34[3] = 0;
        local_34[4] = 0;
        local_34[5] = 0;
        local_34[6] = 0;
        local_34[7] = 0;
        *(undefined4 **)(iVar4 + 0x18) = local_34;
      }
      pbVar7 = (byte *)((local_28 >> 3) + *(int *)(iVar4 + 0x18));
      *pbVar7 = *pbVar7 | (byte)(1 << (local_28 & 7));
    }
    local_28 = local_28 + 1;
  } while (local_28 < 0x100);
  if (0xf < local_38) {
    ppppuVar6 = (uint ****)local_4c[0];
    if (0xfff < local_38 + 1) {
      if (((uint)local_4c[0] & 0x1f) != 0) {
LAB_00456f31:
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      ppppuVar6 = (uint ****)local_4c[0][-1];
      if (local_4c[0] <= ppppuVar6) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      if ((uint)((int)local_4c[0] - (int)ppppuVar6) < 4) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      if (0x23 < (uint)((int)local_4c[0] - (int)ppppuVar6)) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
    }
    FID_conflict__free(ppppuVar6);
  }
  ExceptionList = local_1c;
  return;
}


