// FUN_004459d0 @ 004459d0 size=55 callers=2

undefined1 * __thiscall FUN_004459d0(void *this,undefined1 *param_1)

{
  uint *puVar1;
  int iVar2;
  
  puVar1 = *(uint **)((int)this + 0x38);
  iVar2 = *(int *)((int)this + 0x40);
  *(undefined4 *)(param_1 + 0x14) = 0xf;
  *(undefined4 *)(param_1 + 0x10) = 0;
  *param_1 = 0;
  FUN_0043ace0(param_1,puVar1,iVar2 - (int)puVar1);
  return param_1;
}


