// FUN_00406ae0 @ 00406ae0 size=292 callers=1

void * __thiscall FUN_00406ae0(void *this,int *param_1)

{
  RECT *pRVar1;
  uint *puVar2;
  void *this_00;
  uint uVar3;
  int iVar4;
  uint *_Memory;
  RECT *pRVar5;
  uint *local_24;
  int local_20;
  int local_1c;
  int local_18;
  void *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_004795f0;
  local_10 = ExceptionList;
  local_24 = (uint *)0x0;
  local_20 = 0;
  local_1c = 0;
  local_8 = 0;
  local_18 = 0;
  ExceptionList = &local_10;
  local_14 = this;
  FUN_004330c0(&local_24,param_1);
  iVar4 = (param_1[3] - param_1[1]) * (param_1[2] - *param_1);
  if (iVar4 < 0) {
    iVar4 = 0;
  }
  local_8 = 1;
  pRVar1 = *(RECT **)((int)this + 4);
  puVar2 = local_24;
  this_00 = local_14;
  for (pRVar5 = *(RECT **)this; local_24 = puVar2, local_18 = iVar4, local_14 = this_00,
      pRVar5 != pRVar1; pRVar5 = pRVar5 + 1) {
    FUN_00406800(&local_24,pRVar5);
    iVar4 = local_18;
    puVar2 = local_24;
    this_00 = local_14;
  }
  FUN_00446b50(this_00,*(uint **)((int)this_00 + 4),puVar2,local_20);
  *(int *)((int)this_00 + 0xc) = *(int *)((int)this_00 + 0xc) + iVar4;
  if (puVar2 != (uint *)0x0) {
    uVar3 = local_1c - (int)puVar2 >> 4;
    if (0xfffffff < uVar3) {
                    /* WARNING: Subroutine does not return */
      FUN_00465fb2();
    }
    _Memory = puVar2;
    if (0xfff < uVar3 << 4) {
      if (((uint)puVar2 & 0x1f) != 0) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      _Memory = (uint *)puVar2[-1];
      if (puVar2 <= _Memory) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      if ((uint)((int)puVar2 - (int)_Memory) < 4) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      if (0x23 < (uint)((int)puVar2 - (int)_Memory)) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
    }
    FID_conflict__free(_Memory);
  }
  ExceptionList = local_10;
  return this_00;
}


