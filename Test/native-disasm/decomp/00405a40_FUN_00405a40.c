// FUN_00405a40 @ 00405a40 size=566 callers=1

undefined4 * __fastcall FUN_00405a40(undefined4 *param_1,void *param_2)

{
  undefined4 *puVar1;
  int *piVar2;
  char cVar3;
  undefined4 uVar4;
  char *pcVar5;
  int *piVar6;
  int iVar7;
  void *this;
  void *_Memory;
  int iVar8;
  int *piVar9;
  void *local_64 [5];
  uint local_50;
  int local_4c [4];
  char *local_3c;
  int *local_38;
  int local_34;
  int local_30;
  int local_2c [2];
  void *local_24;
  long local_20;
  char *local_1c;
  undefined4 local_18;
  undefined4 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_00479451;
  local_10 = ExceptionList;
  local_8 = 0;
  local_18 = 0;
  ExceptionList = &local_10;
  local_24 = param_2;
  local_14 = param_1;
  FUN_00433740(param_1);
  local_8 = 0;
  local_18 = 1;
  FUN_00434120(param_2,&local_3c);
  FUN_004340a0(this,local_4c);
  uVar4 = FUN_004383a0(&local_3c,local_4c);
  cVar3 = (char)uVar4;
  piVar9 = local_38;
  iVar8 = local_30;
  while( true ) {
    if (cVar3 != '\0') {
      ExceptionList = local_10;
      return param_1;
    }
    pcVar5 = FUN_00433b30(&local_3c,(undefined1 *)local_64);
    local_8 = 1;
    if (0xf < *(uint *)(pcVar5 + 0x14)) {
      pcVar5 = *(char **)pcVar5;
    }
    piVar6 = __errno();
    *piVar6 = 0;
    local_20 = _strtol(pcVar5,&local_1c,10);
    if (pcVar5 == local_1c) {
                    /* WARNING: Subroutine does not return */
      FUN_00458ea4("invalid stoi argument");
    }
    piVar6 = __errno();
    if (*piVar6 == 0x22) {
                    /* WARNING: Subroutine does not return */
      FUN_00458ee4("stoi argument out of range");
    }
    pcVar5 = FUN_00433bc0(&local_3c);
    puVar1 = *(undefined4 **)local_14[1];
    iVar7 = FUN_0044f0d0(puVar1,(undefined4 *)puVar1[1],(undefined2 *)&local_20,pcVar5);
    param_1 = local_14;
    if (local_14[2] == 0x30c30c2) break;
    local_14[2] = local_14[2] + 1;
    puVar1[1] = iVar7;
    **(int **)(iVar7 + 4) = iVar7;
    FUN_004469d0(local_14,local_2c,(byte *)(*(int **)local_14[1] + 2),*(int **)local_14[1]);
    local_8 = local_8 & 0xffffff00;
    if (0xf < local_50) {
      _Memory = local_64[0];
      if ((0xfff < local_50 + 1) &&
         ((((((uint)local_64[0] & 0x1f) != 0 ||
            (_Memory = *(void **)((int)local_64[0] + -4), local_64[0] <= _Memory)) ||
           ((uint)((int)local_64[0] - (int)_Memory) < 4)) ||
          (0x23 < (uint)((int)local_64[0] - (int)_Memory))))) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      FID_conflict__free(_Memory);
    }
    if (*local_3c == '\x01') {
      if (*(char *)((int)piVar9 + 0xd) == '\0') {
        piVar6 = (int *)piVar9[2];
        if (*(char *)((int)piVar6 + 0xd) == '\0') {
          cVar3 = *(char *)(*piVar6 + 0xd);
          piVar9 = piVar6;
          piVar6 = (int *)*piVar6;
          while (local_38 = piVar9, cVar3 == '\0') {
            cVar3 = *(char *)(*piVar6 + 0xd);
            piVar9 = piVar6;
            piVar6 = (int *)*piVar6;
          }
        }
        else {
          cVar3 = *(char *)(piVar9[1] + 0xd);
          piVar2 = (int *)piVar9[1];
          piVar6 = piVar9;
          while ((piVar9 = piVar2, local_38 = piVar9, cVar3 == '\0' && (piVar6 == (int *)piVar9[2]))
                ) {
            cVar3 = *(char *)(piVar9[1] + 0xd);
            piVar2 = (int *)piVar9[1];
            piVar6 = piVar9;
          }
        }
      }
    }
    else if (*local_3c == '\x02') {
      local_34 = local_34 + 0x10;
    }
    else {
      iVar8 = iVar8 + 1;
      local_30 = iVar8;
    }
    FUN_004340a0(local_24,local_4c);
    uVar4 = FUN_004383a0(&local_3c,local_4c);
    cVar3 = (char)uVar4;
  }
                    /* WARNING: Subroutine does not return */
  FUN_00458ec4("list<T> too long");
}


