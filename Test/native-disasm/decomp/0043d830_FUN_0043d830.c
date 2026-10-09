// FUN_0043d830 @ 0043d830 size=119 callers=16

void __thiscall FUN_0043d830(void *this,uint param_1)

{
  uint uVar1;
  uint *puVar2;
  uint uVar3;
  undefined4 extraout_ECX;
  uint uVar4;
  void *pvStack_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0047de80;
  pvStack_10 = ExceptionList;
  uVar4 = param_1 | 7;
  if (uVar4 < 0x7fffffff) {
    uVar1 = *(uint *)((int)this + 0x14);
    uVar3 = uVar1 >> 1;
    param_1 = uVar4;
    if ((uVar4 / 3 < uVar3) && (param_1 = uVar3 + uVar1, 0x7ffffffe - uVar3 < uVar1)) {
      param_1 = 0x7ffffffe;
    }
  }
  local_8 = 0;
  ExceptionList = &pvStack_10;
  puVar2 = FUN_0043ec70(param_1 + 1);
  FUN_0043d8d0(extraout_ECX,puVar2);
  return;
}


