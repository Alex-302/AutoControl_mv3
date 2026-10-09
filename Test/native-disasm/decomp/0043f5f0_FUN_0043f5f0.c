// FUN_0043f5f0 @ 0043f5f0 size=164 callers=19

void __thiscall FUN_0043f5f0(void *this,uint param_1)

{
  uint uVar1;
  void *pvVar2;
  uint uVar3;
  uint uVar4;
  void *pvStack_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0047df40;
  pvStack_10 = ExceptionList;
  uVar4 = param_1 | 0xf;
  if (uVar4 != 0xffffffff) {
    uVar1 = *(uint *)((int)this + 0x14);
    uVar3 = uVar1 >> 1;
    param_1 = uVar4;
    if ((uVar4 / 3 < uVar3) && (param_1 = uVar3 + uVar1, -uVar3 - 2 < uVar1)) {
      param_1 = 0xfffffffe;
    }
  }
  uVar4 = param_1 + 1;
  local_8 = 0;
  if (uVar4 == 0) {
    ExceptionList = &pvStack_10;
    FUN_0043f6bd();
    return;
  }
  if (uVar4 < 0x1000) {
    ExceptionList = &pvStack_10;
    operator_new(uVar4);
    FUN_0043f6bd();
    return;
  }
  if (uVar4 < param_1 + 0x24) {
    ExceptionList = &pvStack_10;
    pvVar2 = operator_new(param_1 + 0x24);
    *(void **)(((int)pvVar2 + 0x23U & 0xffffffe0) - 4) = pvVar2;
    FUN_0043f6bd();
    return;
  }
  ExceptionList = &pvStack_10;
                    /* WARNING: Subroutine does not return */
  FUN_00458e6a();
}


