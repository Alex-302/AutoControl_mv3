// FUN_00443ab0 @ 00443ab0 size=57 callers=1

void __fastcall FUN_00443ab0(undefined1 *param_1,undefined1 *param_2)

{
  undefined1 uVar1;
  undefined1 *puVar2;
  int iVar3;
  
  if (param_1 != param_2) {
    iVar3 = 0;
    if (param_1 <= param_1 + 0x10) {
      puVar2 = param_1;
      do {
        uVar1 = *puVar2;
        iVar3 = iVar3 + 1;
        *puVar2 = puVar2[(int)param_2 - (int)param_1];
        (puVar2 + 1)[((int)param_2 - (int)param_1) + -1] = uVar1;
        puVar2 = puVar2 + 1;
      } while (iVar3 != (-(uint)(param_1 + 0x10 < param_1) & 0xfffffff0) + 0x10);
    }
  }
  return;
}


