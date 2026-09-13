// FUN_00411a70 @ 00411a70 size=319 callers=1

void FUN_00411a70(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *this;
  void *pvVar3;
  uint *puVar4;
  int *piVar5;
  int *piVar6;
  int iVar7;
  void **ppvVar8;
  void *local_40 [5];
  uint local_2c;
  void *local_28 [4];
  undefined4 local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  this = param_1;
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047aa10;
  local_10 = ExceptionList;
  iVar7 = 0;
  piVar6 = &DAT_004a298c;
  ExceptionList = &local_10;
  do {
    ppvVar8 = local_40;
    pvVar3 = (void *)FUN_00434550(this,iVar7);
    FUN_00440d90(pvVar3,ppvVar8);
    local_8 = 0;
    puVar4 = FUN_00404220((uint *)local_28,(char *)local_40);
    local_8 = CONCAT31(local_8._1_3_,1);
    piVar5 = FUN_0040a960((int *)&param_1,puVar4);
    if (piVar6 != piVar5) {
      iVar1 = *piVar5;
      *piVar5 = 0;
      puVar2 = (undefined4 *)*piVar6;
      *piVar6 = iVar1;
      if (puVar2 != (undefined4 *)0x0) {
        (**(code **)*puVar2)(1);
      }
    }
    if (param_1 != (undefined4 *)0x0) {
      (**(code **)*param_1)(1);
    }
    local_8 = local_8 & 0xffffff00;
    if (0xf < local_14) {
      pvVar3 = local_28[0];
      if ((0xfff < local_14 + 1) &&
         ((((((uint)local_28[0] & 0x1f) != 0 ||
            (pvVar3 = *(void **)((int)local_28[0] + -4), local_28[0] <= pvVar3)) ||
           ((uint)((int)local_28[0] - (int)pvVar3) < 4)) ||
          (0x23 < (uint)((int)local_28[0] - (int)pvVar3))))) goto LAB_00411baa;
      FID_conflict__free(pvVar3);
    }
    local_8 = 0xffffffff;
    local_14 = 0xf;
    local_18 = 0;
    local_28[0] = (void *)((uint)local_28[0] & 0xffffff00);
    if (0xf < local_2c) {
      pvVar3 = local_40[0];
      if ((0xfff < local_2c + 1) &&
         (((((uint)local_40[0] & 0x1f) != 0 ||
           (pvVar3 = *(void **)((int)local_40[0] + -4), local_40[0] <= pvVar3)) ||
          (((uint)((int)local_40[0] - (int)pvVar3) < 4 ||
           (0x23 < (uint)((int)local_40[0] - (int)pvVar3))))))) {
LAB_00411baa:
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      FID_conflict__free(pvVar3);
    }
    piVar6 = piVar6 + 1;
    iVar7 = iVar7 + 1;
    if (0x4a2993 < (int)piVar6) {
      ExceptionList = local_10;
      return;
    }
  } while( true );
}


