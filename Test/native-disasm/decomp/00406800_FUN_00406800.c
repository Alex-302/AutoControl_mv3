// FUN_00406800 @ 00406800 size=245 callers=2

void ** __thiscall FUN_00406800(void *this,RECT *param_1)

{
  RECT *pRVar1;
  void **ppvVar2;
  int iVar3;
  void *pvVar4;
  uint uVar5;
  void *pvVar6;
  RECT *pRVar7;
  void *local_24;
  void *local_20;
  void *local_1c;
  void **local_18;
  void *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_004795a8;
  local_10 = ExceptionList;
  local_24 = (void *)0x0;
  local_20 = (void *)0x0;
  local_1c = (void *)0x0;
  local_8 = 0;
  pRVar1 = *(RECT **)((int)this + 4);
  pRVar7 = *(RECT **)this;
  local_14 = (void *)0x0;
  ExceptionList = &local_10;
  local_18 = this;
  pvVar6 = local_14;
  if (pRVar7 != pRVar1) {
    pvVar6 = (void *)0x0;
    ExceptionList = &local_10;
    do {
      iVar3 = FUN_00406700(pRVar7,param_1,&local_24);
      pRVar7 = pRVar7 + 1;
      pvVar6 = (void *)((int)pvVar6 + iVar3);
    } while (pRVar7 != pRVar1);
  }
  local_14 = pvVar6;
  ppvVar2 = local_18;
  pvVar4 = local_1c;
  pvVar6 = local_24;
  if (local_18 != &local_24) {
    pvVar6 = *local_18;
    *local_18 = local_24;
    local_18[1] = local_20;
    pvVar4 = local_18[2];
    local_18[2] = local_1c;
  }
  local_18[3] = local_14;
  if (pvVar6 != (void *)0x0) {
    uVar5 = (int)pvVar4 - (int)pvVar6 >> 4;
    if (0xfffffff < uVar5) {
                    /* WARNING: Subroutine does not return */
      FUN_00465fb2();
    }
    pvVar4 = pvVar6;
    if (0xfff < uVar5 << 4) {
      if (((uint)pvVar6 & 0x1f) != 0) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      pvVar4 = *(void **)((int)pvVar6 + -4);
      if (pvVar6 <= pvVar4) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      if ((uint)((int)pvVar6 - (int)pvVar4) < 4) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      if (0x23 < (uint)((int)pvVar6 - (int)pvVar4)) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
    }
    FID_conflict__free(pvVar4);
  }
  ExceptionList = local_10;
  return ppvVar2;
}


