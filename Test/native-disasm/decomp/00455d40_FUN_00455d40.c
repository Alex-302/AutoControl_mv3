// FUN_00455d40 @ 00455d40 size=79 callers=1

void __fastcall FUN_00455d40(int param_1)

{
  uint *puVar1;
  undefined4 *puVar2;
  
  *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + 1;
  puVar2 = FUN_00449540((void *)(param_1 + 0x24),*(undefined4 *)(param_1 + 0xc));
  FUN_0044ecb0((int *)param_1);
  FUN_004494b0((void *)(param_1 + 0x24),(int)puVar2);
  FUN_0044d710((void *)(param_1 + 0x14),*(int *)(param_1 + 0xc) + 1);
  puVar1 = (uint *)(*(int *)(param_1 + 0x14) + ((uint)puVar2[5] >> 5) * 4);
  *puVar1 = *puVar1 | 1 << (puVar2[5] & 0x1f);
  return;
}


