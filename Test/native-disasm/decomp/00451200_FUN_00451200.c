// FUN_00451200 @ 00451200 size=209 callers=1

void __fastcall FUN_00451200(undefined1 *param_1,undefined4 *param_2)

{
  uint *puVar1;
  undefined1 *this;
  uint uVar2;
  uint *puVar3;
  void *local_3c [4];
  undefined4 local_2c;
  uint local_28;
  undefined1 *local_24;
  undefined1 *local_20;
  undefined1 *local_1c;
  undefined1 *local_18;
  undefined1 local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047e8c1;
  local_10 = ExceptionList;
  puVar1 = (uint *)*param_2;
  local_28 = 0xf;
  local_2c = 0;
  local_3c[0] = (void *)((uint)local_3c[0] & 0xffffff00);
  if ((char)*puVar1 == '\0') {
    uVar2 = 0;
  }
  else {
    puVar3 = puVar1;
    do {
      uVar2 = *puVar3;
      puVar3 = (uint *)((int)puVar3 + 1);
    } while ((char)uVar2 != '\0');
    uVar2 = (int)puVar3 - ((int)puVar1 + 1);
  }
  ExceptionList = &local_10;
  FUN_0043ace0(local_3c,puVar1,uVar2);
  local_8 = 0;
  *param_1 = 3;
  this = operator_new(0x18);
  local_24 = &local_11;
  local_8 = CONCAT31(local_8._1_3_,2);
  local_20 = this;
  local_1c = this;
  local_18 = this;
  if (this != (undefined1 *)0x0) {
    *(undefined4 *)(this + 0x14) = 0xf;
    *(undefined4 *)(this + 0x10) = 0;
    *this = 0;
    FUN_0043ade0(this,local_3c,0,0xffffffff);
  }
  *(undefined1 **)(param_1 + 8) = this;
  *(undefined1 **)(param_1 + 0xc) = local_20;
  if (0xf < local_28) {
    FUN_00402430(local_3c[0],local_28 + 1,1);
  }
  ExceptionList = local_10;
  return;
}


