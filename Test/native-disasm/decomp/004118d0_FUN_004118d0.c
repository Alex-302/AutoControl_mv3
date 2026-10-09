// FUN_004118d0 @ 004118d0 size=414 callers=1

void FUN_004118d0(void *param_1)

{
  char cVar1;
  int *piVar2;
  int *piVar3;
  undefined4 uVar4;
  byte *pbVar5;
  char *pcVar6;
  undefined4 *puVar7;
  void *this;
  int iVar8;
  void *_Memory;
  undefined4 *puVar9;
  undefined1 local_14c [128];
  undefined4 local_cc [32];
  void *local_4c [5];
  uint local_38;
  int local_34 [4];
  char *local_24;
  int *local_20;
  int local_1c;
  int local_18;
  int *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047a9e8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00434120(param_1,&local_24);
  FUN_004340a0(this,local_34);
  uVar4 = FUN_004383a0(&local_24,local_34);
  if ((char)uVar4 == '\0') {
    local_14 = local_20;
    do {
      pbVar5 = FUN_00433b30(&local_24,(undefined1 *)local_4c);
      local_8 = 0;
      pcVar6 = FUN_00433bc0(&local_24);
      puVar7 = FUN_004123b0(local_14c,pcVar6);
      puVar9 = local_cc;
      for (iVar8 = 0x20; iVar8 != 0; iVar8 = iVar8 + -1) {
        *puVar9 = *puVar7;
        puVar7 = puVar7 + 1;
        puVar9 = puVar9 + 1;
      }
      pbVar5 = FUN_00432630(&DAT_004a296c,pbVar5);
      puVar7 = local_cc;
      for (iVar8 = 0x20; iVar8 != 0; iVar8 = iVar8 + -1) {
        *(undefined4 *)pbVar5 = *puVar7;
        puVar7 = puVar7 + 1;
        pbVar5 = pbVar5 + 4;
      }
      local_8 = 0xffffffff;
      if (0xf < local_38) {
        _Memory = local_4c[0];
        if ((0xfff < local_38 + 1) &&
           ((((((uint)local_4c[0] & 0x1f) != 0 ||
              (_Memory = *(void **)((int)local_4c[0] + -4), local_4c[0] <= _Memory)) ||
             ((uint)((int)local_4c[0] - (int)_Memory) < 4)) ||
            (0x23 < (uint)((int)local_4c[0] - (int)_Memory))))) {
                    /* WARNING: Subroutine does not return */
          FUN_00465fb2();
        }
        FID_conflict__free(_Memory);
      }
      if (*local_24 == '\x01') {
        if (*(char *)((int)local_14 + 0xd) == '\0') {
          local_20 = (int *)local_14[2];
          if (*(char *)((int)local_20 + 0xd) == '\0') {
            cVar1 = *(char *)(*local_20 + 0xd);
            piVar2 = (int *)*local_20;
            while (local_14 = local_20, cVar1 == '\0') {
              cVar1 = *(char *)(*piVar2 + 0xd);
              local_20 = piVar2;
              piVar2 = (int *)*piVar2;
            }
          }
          else {
            cVar1 = *(char *)(local_14[1] + 0xd);
            piVar3 = (int *)local_14[1];
            piVar2 = local_14;
            while ((local_20 = piVar3, local_14 = local_20, cVar1 == '\0' &&
                   (piVar2 == (int *)local_20[2]))) {
              cVar1 = *(char *)(local_20[1] + 0xd);
              piVar3 = (int *)local_20[1];
              piVar2 = local_20;
            }
          }
        }
      }
      else if (*local_24 == '\x02') {
        local_1c = local_1c + 0x10;
      }
      else {
        local_18 = local_18 + 1;
      }
      FUN_004340a0(param_1,local_34);
      uVar4 = FUN_004383a0(&local_24,local_34);
    } while ((char)uVar4 == '\0');
  }
  ExceptionList = local_10;
  return;
}


