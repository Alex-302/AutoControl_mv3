// FUN_00453e50 @ 00453e50 size=131 callers=4

void __fastcall FUN_00453e50(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = operator_new(0x2c);
  puVar2[4] = 0;
  puVar2[1] = 7;
  puVar2[2] = 0;
  puVar2[3] = 0;
  *puVar2 = &PTR_FUN_0048e838;
  puVar2[5] = 0;
  puVar2[6] = 0;
  puVar2[7] = 0;
  puVar2[8] = 0;
  *(undefined2 *)(puVar2 + 9) = 0;
  puVar2[10] = 0;
  puVar2[4] = *(undefined4 *)(param_1 + 4);
  iVar1 = *(int *)(*(int *)(param_1 + 4) + 0xc);
  if (iVar1 != 0) {
    puVar2[3] = iVar1;
    *(undefined4 **)(*(int *)(*(int *)(param_1 + 4) + 0xc) + 0x10) = puVar2;
  }
  *(undefined4 **)(*(int *)(param_1 + 4) + 0xc) = puVar2;
  *(undefined4 **)(param_1 + 4) = puVar2;
  return;
}


