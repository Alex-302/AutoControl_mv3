// FUN_0045c1d2 @ 0045c1d2 size=155 callers=2

undefined4 __cdecl FUN_0045c1d2(int param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  int *in_EAX;
  int iVar3;
  int *piVar4;
  undefined1 uVar5;
  int iVar6;
  int local_c;
  int local_8;
  
  if (param_2 == (int *)0x0) {
                    /* WARNING: Subroutine does not return */
    FUN_00464131();
  }
  iVar6 = *param_2;
  uVar5 = 0;
  if (0 < iVar6) {
    local_8 = 0;
    piVar4 = *(int **)(*(int *)(param_1 + 0x1c) + 0xc);
    iVar1 = *piVar4;
    in_EAX = piVar4 + 1;
    uVar5 = 0;
    do {
      if (0 < iVar1) {
        iVar2 = param_2[1];
        piVar4 = in_EAX;
        local_c = iVar1;
        do {
          iVar3 = ___TypeMatch((byte *)(iVar2 + local_8),(byte *)*piVar4,*(byte **)(param_1 + 0x1c))
          ;
          if (iVar3 != 0) {
            uVar5 = 1;
            break;
          }
          local_c = local_c + -1;
          piVar4 = piVar4 + 1;
        } while (0 < local_c);
      }
      local_8 = local_8 + 0x10;
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
  }
  return CONCAT31((int3)((uint)in_EAX >> 8),uVar5);
}


