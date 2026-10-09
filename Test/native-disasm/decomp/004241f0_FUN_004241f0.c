// FUN_004241f0 @ 004241f0 size=477 callers=1

void * __cdecl FUN_004241f0(void *param_1,HWND param_2)

{
  int *piVar1;
  uint uVar2;
  int *piVar3;
  char cVar4;
  undefined4 uVar5;
  char *pcVar6;
  uint uVar7;
  byte *pbVar8;
  void *this;
  void *_Memory;
  int *piVar9;
  void *local_6c [5];
  uint local_58;
  int local_54 [4];
  char local_44 [8];
  ulonglong local_3c;
  char *local_34;
  int *local_30;
  int local_2c;
  int local_28;
  uint local_24;
  undefined4 local_20;
  uint local_18;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0047bf89;
  local_10 = ExceptionList;
  local_8 = 0;
  local_14 = 0;
  ExceptionList = &local_10;
  FUN_00434a40(param_1,(char *)0x0,(char *)0x0);
  local_8 = 0;
  local_14 = 1;
  FUN_00434120(param_2,&local_34);
  FUN_004340a0(this,local_54);
  uVar5 = FUN_004383a0(&local_34,local_54);
  cVar4 = (char)uVar5;
  piVar9 = local_30;
  do {
    if (cVar4 != '\0') {
      ExceptionList = local_10;
      return param_1;
    }
    pcVar6 = FUN_00433bc0(&local_34);
    FUN_004536b0(pcVar6,(uint *)&param_2);
    uVar7 = GetWindowLongA(param_2,-0x14);
    uVar7 = CONCAT31(local_24._1_3_,(char)(uVar7 >> 3));
    local_24 = uVar7 & 0xffffff01;
    uVar2 = local_24;
    local_44[0] = '\x04';
    local_3c = CONCAT44(local_20,uVar7) & 0xffffffffffffff01;
    local_8 = 1;
    FUN_004536b0(pcVar6,&local_18);
    pbVar8 = FUN_00403340((undefined1 *)local_6c,local_18);
    local_8._0_1_ = 2;
    pcVar6 = FUN_00434440(param_1,pbVar8);
    local_44[0] = *pcVar6;
    *pcVar6 = '\x04';
    local_3c = *(ulonglong *)(pcVar6 + 8);
    *(uint *)(pcVar6 + 8) = uVar2;
    *(undefined4 *)(pcVar6 + 0xc) = local_20;
    FUN_00434820(local_44);
    local_8 = (uint)local_8._1_3_ << 8;
    if (0xf < local_58) {
      _Memory = local_6c[0];
      if ((0xfff < local_58 + 1) &&
         ((((((uint)local_6c[0] & 0x1f) != 0 ||
            (_Memory = *(void **)((int)local_6c[0] + -4), local_6c[0] <= _Memory)) ||
           ((uint)((int)local_6c[0] - (int)_Memory) < 4)) ||
          (0x23 < (uint)((int)local_6c[0] - (int)_Memory))))) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      FID_conflict__free(_Memory);
    }
    if (*local_34 == '\x01') {
      if (*(char *)((int)piVar9 + 0xd) == '\0') {
        piVar1 = (int *)piVar9[2];
        if (*(char *)((int)piVar1 + 0xd) == '\0') {
          cVar4 = *(char *)(*piVar1 + 0xd);
          piVar9 = piVar1;
          piVar1 = (int *)*piVar1;
          while (local_30 = piVar9, cVar4 == '\0') {
            cVar4 = *(char *)(*piVar1 + 0xd);
            piVar9 = piVar1;
            piVar1 = (int *)*piVar1;
          }
        }
        else {
          cVar4 = *(char *)(piVar9[1] + 0xd);
          piVar3 = (int *)piVar9[1];
          piVar1 = piVar9;
          while ((piVar9 = piVar3, local_30 = piVar9, cVar4 == '\0' && (piVar1 == (int *)piVar9[2]))
                ) {
            cVar4 = *(char *)(piVar9[1] + 0xd);
            piVar3 = (int *)piVar9[1];
            piVar1 = piVar9;
          }
        }
      }
    }
    else if (*local_34 == '\x02') {
      local_2c = local_2c + 0x10;
    }
    else {
      local_28 = local_28 + 1;
    }
    uVar5 = FUN_004383a0(&local_34,local_54);
    cVar4 = (char)uVar5;
  } while( true );
}


