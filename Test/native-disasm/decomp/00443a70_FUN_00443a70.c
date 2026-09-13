// FUN_00443a70 @ 00443a70 size=61 callers=1

void __fastcall FUN_00443a70(undefined2 *param_1,undefined2 *param_2)

{
  undefined2 uVar1;
  undefined2 *puVar2;
  int iVar3;
  
  if (param_1 != param_2) {
    iVar3 = 0;
    if (param_1 <= param_1 + 8) {
      puVar2 = param_1;
      do {
        uVar1 = *puVar2;
        iVar3 = iVar3 + 1;
        *puVar2 = *(undefined2 *)(((int)param_2 - (int)param_1) + (int)puVar2);
        *(undefined2 *)(((int)param_2 - (int)param_1) + -2 + (int)(puVar2 + 1)) = uVar1;
        puVar2 = puVar2 + 1;
      } while (iVar3 != (-(uint)(param_1 + 8 < param_1) & 0xfffffff8) + 8);
    }
  }
  return;
}


