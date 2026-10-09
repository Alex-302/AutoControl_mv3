// FUN_00424530 @ 00424530 size=594 callers=1

void __cdecl FUN_00424530(undefined1 *param_1,void *param_2)

{
  int *piVar1;
  code *pcVar2;
  int *piVar3;
  char cVar4;
  undefined4 *this;
  undefined4 uVar5;
  char *pcVar6;
  void *this_00;
  int iVar7;
  int *piVar8;
  int iVar9;
  bool bVar10;
  void *local_64 [2];
  int local_5c [2];
  undefined4 local_54;
  uint local_50;
  char local_4c [20];
  char *local_38;
  int *local_34;
  int local_30;
  int local_2c;
  undefined4 local_28;
  UINT local_24;
  HWND local_20 [2];
  uint local_18;
  char local_12;
  byte local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047bfb0;
  local_10 = ExceptionList;
  local_28 = 0;
  local_50 = 0xf;
  local_54 = 0;
  local_64[0] = (void *)((uint)local_64[0] & 0xffffff00);
  ExceptionList = &local_10;
  FUN_0043ace0(local_64,(uint *)"noAnim",6);
  local_8 = 0;
  cVar4 = FUN_00441100(param_2,local_64);
  local_8 = 0xffffffff;
  local_12 = cVar4;
  if (0xf < local_50) {
    FUN_00402430(local_64[0],local_50 + 1,1);
  }
  pcVar2 = SystemParametersInfoA_exref;
  if (cVar4 == '\0') {
    local_11 = 0;
  }
  else {
    local_24 = 8;
    local_20[0] = (HWND)0x0;
    SystemParametersInfoA(0x48,8,&local_24,0);
    local_11 = local_20[0] != (HWND)0x0;
    if ((bool)local_11) {
      local_20[0] = (HWND)0x0;
      SystemParametersInfoA(0x49,local_24,&local_24,0);
    }
  }
  this = FUN_00440e70(param_2,(uint *)&DAT_0048d820);
  FUN_00434120(this,&local_38);
  FUN_004340a0(this_00,local_5c);
  uVar5 = FUN_004383a0(&local_38,local_5c);
  cVar4 = (char)uVar5;
  piVar8 = local_34;
  iVar7 = local_30;
  iVar9 = local_2c;
  while (cVar4 == '\0') {
    pcVar6 = FUN_00433bc0(&local_38);
    FUN_00434940(local_4c,pcVar6);
    local_8 = 1;
    pcVar6 = (char *)FUN_00440e70(param_2,(uint *)"state");
    FUN_004536b0(pcVar6,&local_18);
    FUN_004536b0(local_4c,(uint *)local_20);
    ShowWindow(local_20[0],local_18);
    local_8 = 0xffffffff;
    FUN_00434820(local_4c);
    if (*local_38 == '\x01') {
      if (*(char *)((int)piVar8 + 0xd) == '\0') {
        piVar1 = (int *)piVar8[2];
        if (*(char *)((int)piVar1 + 0xd) == '\0') {
          cVar4 = *(char *)(*piVar1 + 0xd);
          piVar8 = piVar1;
          piVar1 = (int *)*piVar1;
          while (local_34 = piVar8, cVar4 == '\0') {
            cVar4 = *(char *)(*piVar1 + 0xd);
            piVar8 = piVar1;
            piVar1 = (int *)*piVar1;
          }
        }
        else {
          cVar4 = *(char *)(piVar8[1] + 0xd);
          piVar3 = (int *)piVar8[1];
          piVar1 = piVar8;
          while ((piVar8 = piVar3, local_34 = piVar8, cVar4 == '\0' && (piVar1 == (int *)piVar8[2]))
                ) {
            cVar4 = *(char *)(piVar8[1] + 0xd);
            piVar3 = (int *)piVar8[1];
            piVar1 = piVar8;
          }
        }
      }
    }
    else if (*local_38 == '\x02') {
      iVar7 = iVar7 + 0x10;
      local_30 = iVar7;
    }
    else {
      iVar9 = iVar9 + 1;
      local_2c = iVar9;
    }
    uVar5 = FUN_004383a0(&local_38,local_5c);
    pcVar2 = SystemParametersInfoA_exref;
    cVar4 = (char)uVar5;
  }
  if (local_12 == '\0') {
    bVar10 = false;
  }
  else {
    local_24 = 8;
    local_20[0] = (HWND)0x0;
    (*pcVar2)(0x48,8,&local_24,0);
    bVar10 = local_20[0] != (HWND)0x0;
    if ((bool)local_11 != bVar10) {
      local_20[0] = (HWND)(uint)local_11;
      (*pcVar2)(0x49,local_24,&local_24,0);
    }
  }
  local_24 = CONCAT31(local_24._1_3_,bVar10);
  *(undefined8 *)(param_1 + 8) = 0;
  *(UINT *)(param_1 + 8) = local_24;
  *(HWND *)(param_1 + 0xc) = local_20[0];
  *param_1 = 4;
  ExceptionList = local_10;
  return;
}


