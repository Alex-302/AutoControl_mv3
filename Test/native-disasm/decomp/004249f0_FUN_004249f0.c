// FUN_004249f0 @ 004249f0 size=637 callers=1

void __cdecl FUN_004249f0(undefined1 *param_1,void *param_2)

{
  int *piVar1;
  code *pcVar2;
  HWND hWnd;
  int *piVar3;
  char cVar4;
  char *pcVar5;
  undefined4 *this;
  undefined4 uVar6;
  BOOL BVar7;
  void *this_00;
  int iVar8;
  int *piVar9;
  bool bVar10;
  void *local_5c [2];
  int local_54 [2];
  undefined4 local_4c;
  uint local_48;
  char local_44 [20];
  char *local_30;
  int *local_2c;
  int local_28;
  int local_24;
  undefined4 local_20;
  UINT local_1c;
  HWND local_18;
  char local_13;
  char local_12;
  byte local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047bfd0;
  local_10 = ExceptionList;
  local_20 = 0;
  local_48 = 0xf;
  local_4c = 0;
  local_5c[0] = (void *)((uint)local_5c[0] & 0xffffff00);
  ExceptionList = &local_10;
  FUN_0043ace0(local_5c,(uint *)"noAnim",6);
  local_8 = 0;
  cVar4 = FUN_00441100(param_2,local_5c);
  local_8 = 0xffffffff;
  local_13 = cVar4;
  if (0xf < local_48) {
    FUN_00402430(local_5c[0],local_48 + 1,1);
  }
  pcVar2 = SystemParametersInfoA_exref;
  if (cVar4 == '\0') {
    local_11 = 0;
  }
  else {
    local_1c = 8;
    local_18 = (HWND)0x0;
    SystemParametersInfoA(0x48,8,&local_1c,0);
    local_11 = local_18 != (HWND)0x0;
    if ((bool)local_11) {
      local_18 = (HWND)0x0;
      SystemParametersInfoA(0x49,local_1c,&local_1c,0);
    }
  }
  pcVar5 = (char *)FUN_00440e70(param_2,(uint *)&DAT_0048d818);
  FUN_00455dc0(pcVar5,&local_12);
  this = FUN_00440e70(param_2,(uint *)&DAT_0048d820);
  FUN_00434120(this,&local_30);
  FUN_004340a0(this_00,local_54);
  uVar6 = FUN_004383a0(&local_30,local_54);
  cVar4 = (char)uVar6;
  piVar9 = local_2c;
  iVar8 = local_24;
  while (cVar4 == '\0') {
    pcVar5 = FUN_00433bc0(&local_30);
    FUN_00434940(local_44,pcVar5);
    local_8 = 1;
    FUN_004536b0(local_44,(uint *)&local_18);
    hWnd = local_18;
    BVar7 = IsIconic(local_18);
    if ((bool)local_12 != (BVar7 != 0)) {
      if (BVar7 != 0) {
        SendMessageA(hWnd,0x112,0xf120,0);
      }
      else {
        ShowWindow(hWnd,7);
      }
    }
    local_8 = 0xffffffff;
    FUN_00434820(local_44);
    if (*local_30 == '\x01') {
      if (*(char *)((int)piVar9 + 0xd) == '\0') {
        piVar1 = (int *)piVar9[2];
        if (*(char *)((int)piVar1 + 0xd) == '\0') {
          cVar4 = *(char *)(*piVar1 + 0xd);
          piVar9 = piVar1;
          piVar1 = (int *)*piVar1;
          while (local_2c = piVar9, cVar4 == '\0') {
            cVar4 = *(char *)(*piVar1 + 0xd);
            piVar9 = piVar1;
            piVar1 = (int *)*piVar1;
          }
        }
        else {
          cVar4 = *(char *)(piVar9[1] + 0xd);
          piVar3 = (int *)piVar9[1];
          piVar1 = piVar9;
          while ((piVar9 = piVar3, local_2c = piVar9, cVar4 == '\0' && (piVar1 == (int *)piVar9[2]))
                ) {
            cVar4 = *(char *)(piVar9[1] + 0xd);
            piVar3 = (int *)piVar9[1];
            piVar1 = piVar9;
          }
        }
      }
    }
    else if (*local_30 == '\x02') {
      local_28 = local_28 + 0x10;
    }
    else {
      iVar8 = iVar8 + 1;
      local_24 = iVar8;
    }
    uVar6 = FUN_004383a0(&local_30,local_54);
    pcVar2 = SystemParametersInfoA_exref;
    cVar4 = (char)uVar6;
  }
  if (local_13 == '\0') {
    bVar10 = false;
  }
  else {
    local_1c = 8;
    local_18 = (HWND)0x0;
    (*pcVar2)(0x48,8,&local_1c,0);
    bVar10 = local_18 != (HWND)0x0;
    if ((bool)local_11 != bVar10) {
      local_18 = (HWND)(uint)local_11;
      (*pcVar2)(0x49,local_1c,&local_1c,0);
    }
  }
  local_1c = CONCAT31(local_1c._1_3_,bVar10);
  *(undefined8 *)(param_1 + 8) = 0;
  *(UINT *)(param_1 + 8) = local_1c;
  *(HWND *)(param_1 + 0xc) = local_18;
  *param_1 = 4;
  ExceptionList = local_10;
  return;
}


