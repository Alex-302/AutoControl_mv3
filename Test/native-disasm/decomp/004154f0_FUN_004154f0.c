// FUN_004154f0 @ 004154f0 size=128 callers=1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint __fastcall FUN_004154f0(int *param_1)

{
  bool bVar1;
  int *piVar2;
  int iVar3;
  undefined4 local_14;
  undefined4 uStack_10;
  int iStack_c;
  undefined4 uStack_8;
  
  bVar1 = false;
  iVar3 = 0;
  do {
    if (param_1[0xb] == 0) {
      piVar2 = (int *)*param_1;
      local_14 = 0;
      uStack_10 = 0;
      iStack_c = 0;
      uStack_8 = 0;
      if (piVar2 != (int *)0x0) {
        (**(code **)(*piVar2 + 0x34))
                  (piVar2,_DAT_0048e618,_UNK_0048e61c,_UNK_0048e620,_UNK_0048e624,&local_14);
      }
      param_1[0xb] = iStack_c;
    }
    piVar2 = (int *)param_1[0xb];
    if (piVar2 == (int *)0x2b) {
      bVar1 = true;
    }
    else {
      if ((piVar2 == (int *)0x3c) && (bVar1)) {
        return 1;
      }
      if (piVar2 != (int *)0x10) break;
    }
    piVar2 = (int *)FUN_00414ec0(param_1);
    iVar3 = iVar3 + 1;
    param_1 = piVar2;
  } while (iVar3 < 5);
  return (uint)piVar2 & 0xffffff00;
}


