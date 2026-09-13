// FUN_004532c0 @ 004532c0 size=148 callers=3

undefined4 * __thiscall
FUN_004532c0(void *this,undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047e9c0;
  local_10 = ExceptionList;
  puVar3 = *(undefined4 **)this;
  if (*(char *)((int)param_1 + 0xd) == '\0') {
    ExceptionList = &local_10;
    puVar1 = FUN_00453140(this,param_1 + 4);
    puVar1[1] = param_2;
    *(undefined1 *)(puVar1 + 3) = *(undefined1 *)(param_1 + 3);
    local_8 = 0;
    if (*(char *)((int)puVar3 + 0xd) != '\0') {
      puVar3 = puVar1;
    }
    puVar2 = FUN_004532c0(this,(undefined4 *)*param_1,puVar1,param_3);
    *puVar1 = puVar2;
    puVar2 = FUN_004532c0(this,(undefined4 *)param_1[2],puVar1,param_3);
    puVar1[2] = puVar2;
  }
  ExceptionList = local_10;
  return puVar3;
}


