// FUN_00424c70 @ 00424c70 size=483 callers=1

void __cdecl FUN_00424c70(undefined1 *param_1,void *param_2)

{
  int *piVar1;
  HWND hWnd;
  int *piVar2;
  char cVar3;
  char *pcVar4;
  undefined4 *this;
  undefined4 uVar5;
  BOOL BVar6;
  void *this_00;
  int iVar7;
  int *piVar8;
  bool bVar9;
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
  uint local_1c;
  HWND local_18;
  char local_12;
  char local_11;
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
  local_12 = FUN_00441100(param_2,local_5c);
  local_8 = 0xffffffff;
  if (0xf < local_48) {
    FUN_00402430(local_5c[0],local_48 + 1,1);
  }
  pcVar4 = (char *)FUN_00440e70(param_2,(uint *)&DAT_0048d818);
  FUN_00455dc0(pcVar4,&local_11);
  this = FUN_00440e70(param_2,(uint *)&DAT_0048d820);
  FUN_00434120(this,&local_30);
  FUN_004340a0(this_00,local_54);
  uVar5 = FUN_004383a0(&local_30,local_54);
  cVar3 = (char)uVar5;
  piVar8 = local_2c;
  iVar7 = local_24;
  while (cVar3 == '\0') {
    pcVar4 = FUN_00433bc0(&local_30);
    FUN_00434940(local_44,pcVar4);
    local_8 = 1;
    FUN_004536b0(local_44,(uint *)&local_18);
    hWnd = local_18;
    BVar6 = IsZoomed(local_18);
    bVar9 = BVar6 != 0;
    if ((bool)local_11 != bVar9) {
      if (local_12 == '\0') {
        ShowWindow(hWnd,bVar9 + 3);
      }
      else {
        FUN_00406470(hWnd,!bVar9);
      }
    }
    local_8 = 0xffffffff;
    FUN_00434820(local_44);
    if (*local_30 == '\x01') {
      if (*(char *)((int)piVar8 + 0xd) == '\0') {
        piVar1 = (int *)piVar8[2];
        if (*(char *)((int)piVar1 + 0xd) == '\0') {
          cVar3 = *(char *)(*piVar1 + 0xd);
          piVar8 = piVar1;
          piVar1 = (int *)*piVar1;
          while (local_2c = piVar8, cVar3 == '\0') {
            cVar3 = *(char *)(*piVar1 + 0xd);
            piVar8 = piVar1;
            piVar1 = (int *)*piVar1;
          }
        }
        else {
          cVar3 = *(char *)(piVar8[1] + 0xd);
          piVar2 = (int *)piVar8[1];
          piVar1 = piVar8;
          while ((piVar8 = piVar2, local_2c = piVar8, cVar3 == '\0' && (piVar1 == (int *)piVar8[2]))
                ) {
            cVar3 = *(char *)(piVar8[1] + 0xd);
            piVar2 = (int *)piVar8[1];
            piVar1 = piVar8;
          }
        }
      }
    }
    else if (*local_30 == '\x02') {
      local_28 = local_28 + 0x10;
    }
    else {
      iVar7 = iVar7 + 1;
      local_24 = iVar7;
    }
    uVar5 = FUN_004383a0(&local_30,local_54);
    cVar3 = (char)uVar5;
  }
  local_1c = local_1c & 0xffffff00;
  *(undefined8 *)(param_1 + 8) = 0;
  *(uint *)(param_1 + 8) = local_1c;
  *(HWND *)(param_1 + 0xc) = local_18;
  *param_1 = 4;
  ExceptionList = local_10;
  return;
}


