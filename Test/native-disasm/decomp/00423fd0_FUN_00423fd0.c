// FUN_00423fd0 @ 00423fd0 size=451 callers=1

undefined1 * __cdecl FUN_00423fd0(undefined1 *param_1,HWND param_2)

{
  char cVar1;
  int *piVar2;
  int *piVar3;
  HWND pHVar4;
  undefined4 uVar5;
  char *pcVar6;
  uint uVar7;
  BOOL BVar8;
  void *this;
  int iVar9;
  int *piVar10;
  int iVar11;
  UINT gaFlags;
  int local_4c [4];
  char local_3c [16];
  char *local_2c;
  int *local_28;
  int local_24;
  int local_20;
  undefined4 local_1c;
  HWND local_18;
  char local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047bf4e;
  local_10 = ExceptionList;
  gaFlags = 3;
  local_1c = 0;
  ExceptionList = &local_10;
  pHVar4 = GetForegroundWindow();
  local_18 = GetAncestor(pHVar4,gaFlags);
  local_11 = '\0';
  FUN_00434120(param_2,&local_2c);
  FUN_004340a0(this,local_4c);
  uVar5 = FUN_004383a0(&local_2c,local_4c);
  iVar9 = local_24;
  piVar10 = local_28;
  iVar11 = local_20;
  if ((char)uVar5 == '\0') {
    do {
      pcVar6 = FUN_00433bc0(&local_2c);
      FUN_00434940(local_3c,pcVar6);
      local_8 = 0;
      FUN_004536b0(local_3c,(uint *)&param_2);
      if ((local_11 != '\0') || (local_11 = '\0', param_2 == local_18)) {
        local_11 = '\x01';
      }
      SetWindowPos(param_2,(HWND)0x1,0,0,0,0,0x13);
      local_8 = 0xffffffff;
      FUN_00434820(local_3c);
      if (*local_2c == '\x01') {
        if (*(char *)((int)piVar10 + 0xd) == '\0') {
          piVar2 = (int *)piVar10[2];
          if (*(char *)((int)piVar2 + 0xd) == '\0') {
            cVar1 = *(char *)(*piVar2 + 0xd);
            piVar10 = piVar2;
            piVar2 = (int *)*piVar2;
            while (local_28 = piVar10, cVar1 == '\0') {
              cVar1 = *(char *)(*piVar2 + 0xd);
              piVar10 = piVar2;
              piVar2 = (int *)*piVar2;
            }
          }
          else {
            cVar1 = *(char *)(piVar10[1] + 0xd);
            piVar3 = (int *)piVar10[1];
            piVar2 = piVar10;
            while ((piVar10 = piVar3, local_28 = piVar10, cVar1 == '\0' &&
                   (piVar2 == (int *)piVar10[2]))) {
              cVar1 = *(char *)(piVar10[1] + 0xd);
              piVar3 = (int *)piVar10[1];
              piVar2 = piVar10;
            }
          }
        }
      }
      else if (*local_2c == '\x02') {
        iVar9 = iVar9 + 0x10;
        local_24 = iVar9;
      }
      else {
        iVar11 = iVar11 + 1;
        local_20 = iVar11;
      }
      uVar5 = FUN_004383a0(&local_2c,local_4c);
    } while ((char)uVar5 == '\0');
    if (local_11 != '\0') {
      for (pHVar4 = GetWindow(local_18,0); pHVar4 != (HWND)0x0; pHVar4 = GetWindow(pHVar4,2)) {
        uVar7 = GetWindowLongA(pHVar4,-0x10);
        if ((((uVar7 & 0x80000) != 0) && (BVar8 = IsWindowVisible(pHVar4), BVar8 != 0)) &&
           (BVar8 = IsIconic(pHVar4), BVar8 == 0)) {
          FUN_0040ee50(pHVar4);
          break;
        }
      }
    }
  }
  local_8 = 1;
  *param_1 = 0;
  FUN_004381d0(param_1 + 8,'\0');
  ExceptionList = local_10;
  return param_1;
}


