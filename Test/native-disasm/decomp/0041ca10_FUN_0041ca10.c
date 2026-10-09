// FUN_0041ca10 @ 0041ca10 size=203 callers=3

void __thiscall FUN_0041ca10(void *this,char param_1)

{
  uint uVar1;
  char cVar2;
  ushort uVar3;
  undefined *puVar4;
  undefined **local_40 [9];
  undefined ***local_1c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  cVar2 = param_1;
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047b848;
  local_10 = ExceptionList;
  if (*(ushort *)((int)this + 0x3c) != 0xffff) {
    uVar1 = *(uint *)(*(int *)((int)this + 0xc) + (uint)*(ushort *)((int)this + 0x3c) * 0x14);
    ExceptionList = &local_10;
    puVar4 = FUN_00419890(uVar1);
    uVar3 = FUN_0041a020(puVar4[0x24],param_1);
    if ((char)(uVar3 >> 8) != '\0') {
      local_1c = local_40;
      local_40[0] = &PTR_LAB_0048ea08;
      local_8 = 0;
      FUN_0040f6b0(DAT_004a23dc,(int *)local_1c,0);
      local_8 = 0xffffffff;
      if (local_1c != (undefined ***)0x0) {
        (*(code *)(*local_1c)[4])(local_1c != local_40);
        local_1c = (undefined ***)0x0;
      }
    }
    param_1 = (char)uVar3;
    if (param_1 != '\0') {
      FUN_00419cf0(uVar1,cVar2);
    }
  }
  ExceptionList = local_10;
  return;
}


