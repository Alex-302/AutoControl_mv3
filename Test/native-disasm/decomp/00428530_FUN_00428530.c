// FUN_00428530 @ 00428530 size=595 callers=1

undefined1 * __cdecl FUN_00428530(undefined1 *param_1,HMONITOR param_2)

{
  int *piVar1;
  POINT pt;
  int *piVar2;
  char cVar3;
  undefined4 uVar4;
  char *pcVar5;
  int iVar6;
  char *pcVar7;
  void *this;
  void *_Memory;
  void *this_00;
  int *piVar8;
  void *local_74 [4];
  undefined4 local_64;
  uint local_60;
  int local_5c [4];
  char *local_4c;
  int *local_48;
  int local_44;
  int local_40;
  int *local_3c;
  int *local_38;
  int local_34;
  undefined1 local_30;
  undefined4 local_2c;
  uint local_28;
  HMONITOR *local_24;
  int local_20;
  uint local_1c;
  uint local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004791a6;
  local_10 = ExceptionList;
  local_2c = 0;
  ExceptionList = &local_10;
  FUN_00434120(param_2,&local_4c);
  FUN_004340a0(this,local_5c);
  uVar4 = FUN_004383a0(&local_4c,local_5c);
  cVar3 = (char)uVar4;
  piVar8 = local_48;
  do {
    if (cVar3 != '\0') {
      local_8 = 0;
      *param_1 = 0;
      FUN_004381d0(param_1 + 8,'\0');
      ExceptionList = local_10;
      return param_1;
    }
    pcVar5 = FUN_00433bc0(&local_4c);
    local_60 = 0xf;
    local_64 = 0;
    local_74[0] = (void *)((uint)local_74[0] & 0xffffff00);
    FUN_0043ace0(local_74,(uint *)&DAT_0048d9a8,3);
    if (*pcVar5 == '\x01') {
      FUN_004437f0(*(void **)(pcVar5 + 8),(int *)&local_3c,(byte *)local_74);
      iVar6 = FUN_00447a70(local_3c,local_38);
    }
    else {
      iVar6 = 0;
    }
    if (0xf < local_60) {
      _Memory = local_74[0];
      if ((0xfff < local_60 + 1) &&
         ((((((uint)local_74[0] & 0x1f) != 0 ||
            (_Memory = *(void **)((int)local_74[0] + -4), local_74[0] <= _Memory)) ||
           ((uint)((int)local_74[0] - (int)_Memory) < 4)) ||
          (0x23 < (uint)((int)local_74[0] - (int)_Memory))))) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      FID_conflict__free(_Memory);
    }
    if (iVar6 != 0) {
      pcVar7 = (char *)FUN_00440e70(pcVar5,(uint *)&DAT_0048d9a8);
      FUN_004536b0(pcVar7,&local_14);
      if (local_14 != 0) {
        pcVar7 = (char *)FUN_00440e70(pcVar5,(uint *)&DAT_0048d65c);
        FUN_004536b0(pcVar7,&local_1c);
        pcVar7 = (char *)FUN_00440e70(pcVar5,(uint *)&DAT_0048d660);
        FUN_004536b0(pcVar7,&local_18);
        pt.y = local_18;
        pt.x = local_1c;
        param_2 = MonitorFromPoint(pt,0);
        pcVar5 = (char *)FUN_00440e70(pcVar5,(uint *)&DAT_0048d9a8);
        FUN_00453810(pcVar5,&local_28);
        FUN_00436e20(&local_20,(byte *)&param_2);
        if (local_20 == DAT_004a2804) {
          local_24 = &param_2;
          FUN_0044a810(this_00,&local_34,this_00,&local_24);
        }
        else {
          local_34 = local_20;
          local_30 = 0;
        }
        *(uint *)(local_34 + 0xc) = local_28;
      }
    }
    if (*local_4c == '\x01') {
      if (*(char *)((int)piVar8 + 0xd) == '\0') {
        piVar1 = (int *)piVar8[2];
        if (*(char *)((int)piVar1 + 0xd) == '\0') {
          cVar3 = *(char *)(*piVar1 + 0xd);
          piVar8 = piVar1;
          piVar1 = (int *)*piVar1;
          while (local_48 = piVar8, cVar3 == '\0') {
            cVar3 = *(char *)(*piVar1 + 0xd);
            piVar8 = piVar1;
            piVar1 = (int *)*piVar1;
          }
        }
        else {
          cVar3 = *(char *)(piVar8[1] + 0xd);
          piVar2 = (int *)piVar8[1];
          piVar1 = piVar8;
          while ((piVar8 = piVar2, local_48 = piVar8, cVar3 == '\0' && (piVar1 == (int *)piVar8[2]))
                ) {
            cVar3 = *(char *)(piVar8[1] + 0xd);
            piVar2 = (int *)piVar8[1];
            piVar1 = piVar8;
          }
        }
      }
    }
    else if (*local_4c == '\x02') {
      local_44 = local_44 + 0x10;
    }
    else {
      local_40 = local_40 + 1;
    }
    uVar4 = FUN_004383a0(&local_4c,local_5c);
    cVar3 = (char)uVar4;
  } while( true );
}


