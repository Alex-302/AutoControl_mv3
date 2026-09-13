// FUN_00432850 @ 00432850 size=198 callers=1

int __fastcall FUN_00432850(int *param_1)

{
  uint *puVar1;
  int iVar2;
  int iVar3;
  
  puVar1 = (uint *)param_1[1];
  iVar3 = (int)puVar1 - *param_1;
  iVar2 = iVar3 * 0x66666667;
  if (1 < (uint)(iVar3 / 0x28)) {
    iVar2 = FUN_004479e0(puVar1 + (1 - iVar3 / 0x28) * 10,puVar1);
    param_1[1] = (int)(puVar1 + (1 - iVar3 / 0x28) * 10);
    return iVar2;
  }
  if (iVar3 / 0x28 == 0) {
    FUN_004364b0(param_1,1);
    FUN_00447320((undefined2 *)param_1[1],1 - (param_1[1] - *param_1) / 0x28);
    iVar2 = ((param_1[1] - *param_1) / 0x28) * -0x28 + 0x28;
    param_1[1] = param_1[1] + iVar2;
  }
  return iVar2;
}


