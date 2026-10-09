// FUN_00414e60 @ 00414e60 size=84 callers=5

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int * __fastcall FUN_00414e60(int *param_1)

{
  int *piVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  int iVar6;
  undefined4 local_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 auStack_8 [2];
  
  iVar2 = _DAT_0048e618;
  if (param_1[0xf] == -1) {
    piVar1 = (int *)*param_1;
    puVar3 = (undefined4 *)0x0;
    puVar4 = (undefined4 *)0x0;
    puVar5 = (undefined4 *)0x0;
    local_14 = 0;
    uStack_10 = 0;
    uStack_c = 0;
    auStack_8[0] = 0;
    iVar6 = 0;
    if (piVar1 != (int *)0x0) {
      puVar5 = auStack_8;
      puVar4 = &uStack_c;
      puVar3 = &uStack_10;
      (**(code **)(*piVar1 + 0x58))(piVar1,&local_14);
      iVar6 = iVar2;
    }
    param_1[0xd] = (int)puVar3;
    param_1[0xe] = (int)puVar4;
    param_1[0xf] = (int)puVar5;
    param_1[0x10] = iVar6;
  }
  return param_1 + 0xd;
}


