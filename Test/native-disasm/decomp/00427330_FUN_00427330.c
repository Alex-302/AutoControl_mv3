// FUN_00427330 @ 00427330 size=253 callers=1

void __fastcall FUN_00427330(uint *param_1)

{
  undefined4 *puVar1;
  void *this;
  undefined *puVar2;
  uint uVar3;
  undefined **local_3c;
  undefined4 local_38;
  undefined ***local_18;
  uint *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047afd8;
  local_10 = ExceptionList;
  if (*param_1 < (uint)((DAT_004a2904 - DAT_004a2900) / 0x28)) {
    ExceptionList = &local_10;
    local_14 = param_1;
    puVar2 = FUN_00419890(*param_1);
    this = DAT_004a299c;
    if (DAT_004a2998 == 0) {
      if (DAT_004a299c != (void *)0x0) {
        puVar2[0x24] = 3;
        uVar3 = FUN_0041c880(this,*local_14);
        FUN_0041c080(this,(ushort)uVar3);
        FUN_0041c140((int)this);
        puVar1 = (undefined4 *)(*(int *)((int)this + 0xc) + 4 + (uVar3 & 0xffff) * 0x14);
        *puVar1 = 0;
        puVar1[1] = 0;
        puVar1[2] = 0;
        puVar1[3] = 0;
      }
    }
    else {
      FUN_0041d600(*(HMENU *)(puVar2 + 0x1c),*param_1);
      local_38 = *(undefined4 *)(puVar2 + 0x1c);
      local_18 = &local_3c;
      local_3c = &PTR_LAB_0048e88c;
      local_8 = 0;
      FUN_0040fd50(0x96,(int *)local_18);
      if (local_18 != (undefined ***)0x0) {
        (*(code *)(*local_18)[4])(local_18 != &local_3c);
        ExceptionList = local_10;
        return;
      }
    }
  }
  ExceptionList = local_10;
  return;
}


