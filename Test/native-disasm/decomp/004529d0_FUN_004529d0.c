// FUN_004529d0 @ 004529d0 size=133 callers=1

undefined4 * __thiscall FUN_004529d0(void *this,undefined4 param_1,undefined4 *param_2)

{
  undefined4 *this_00;
  uint *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047e946;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  puVar2 = FUN_004488f0(this);
  local_8 = 0;
  this_00 = puVar2 + 4;
  *(undefined2 *)(puVar2 + 3) = 0;
  if (this_00 != (undefined4 *)0x0) {
    puVar1 = (uint *)*param_2;
    puVar2[9] = 0xf;
    puVar2[8] = 0;
    puVar3 = this_00;
    if (0xf < (uint)puVar2[9]) {
      puVar3 = (undefined4 *)*this_00;
    }
    *(undefined1 *)puVar3 = 0;
    FUN_0043b1c0(this_00,puVar1);
    local_8 = CONCAT31(local_8._1_3_,1);
    *(undefined1 *)(puVar2 + 10) = 0;
    FUN_004381d0(puVar2 + 0xc,'\0');
  }
  ExceptionList = local_10;
  return puVar2;
}


