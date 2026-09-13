// FUN_0040e3a0 @ 0040e3a0 size=529 callers=4

int * __fastcall FUN_0040e3a0(HWND param_1,int *param_2,int *param_3,char param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  HWND pHVar5;
  DWORD DVar6;
  int *piVar7;
  bool bVar8;
  tagRECT local_34;
  int local_24;
  int iStack_20;
  int iStack_1c;
  int iStack_18;
  int local_14;
  int iStack_10;
  int iStack_c;
  int iStack_8;
  
  piVar4 = param_3;
  *param_3 = 0;
  param_3[1] = 0;
  param_3[2] = 0;
  param_3[3] = 0;
  param_3 = (int *)0x0;
  local_14 = 0;
  iStack_10 = 0;
  iStack_c = 0;
  iStack_8 = 0;
  pHVar5 = GetWindow(param_1,5);
  if (pHVar5 != (HWND)0x0) {
    do {
      local_34.left = 0;
      local_34.top = 0;
      local_34.right = 0;
      local_34.bottom = 0;
      GetWindowRect(pHVar5,&local_34);
      iStack_1c = local_34.right - local_34.left;
      iStack_18 = local_34.bottom - local_34.top;
      local_24 = local_34.left;
      iStack_20 = local_34.top;
      if ((((((*param_2 <= local_34.left) && (param_2[1] + 0x14 < local_34.top)) &&
            (iStack_1c <= param_2[2])) && (iStack_18 <= param_2[3])) &&
          ((bVar8 = iStack_18 * iStack_1c - piVar4[3] * piVar4[2] == 0,
           !bVar8 && piVar4[3] * piVar4[2] <= iStack_18 * iStack_1c ||
           (((bVar8 && (*piVar4 <= local_34.left)) && (piVar4[1] <= local_34.top)))))) &&
         (DVar6 = GetWindowThreadProcessId(pHVar5,(LPDWORD)0x0), DVar6 == DAT_004a2460)) {
        param_3 = (int *)((int)param_3 + 1);
        *piVar4 = local_24;
        piVar4[1] = iStack_20;
        piVar4[2] = iStack_1c;
        piVar4[3] = iStack_18;
      }
      pHVar5 = GetWindow(pHVar5,2);
    } while (pHVar5 != (HWND)0x0);
    if (param_3 != (int *)0x0) {
      if (param_4 != '\0') {
        if ((piVar4[2] < 0x1e) || (piVar4[3] < 5)) {
          iVar1 = param_2[1];
          iVar2 = param_2[2];
          iVar3 = param_2[3];
          *piVar4 = *param_2;
          piVar4[1] = iVar1;
          piVar4[2] = iVar2;
          piVar4[3] = iVar3;
        }
        for (pHVar5 = GetWindow(param_1,5); pHVar5 != (HWND)0x0; pHVar5 = GetWindow(pHVar5,2)) {
          local_34.left = 0;
          local_34.top = 0;
          local_34.right = 0;
          local_34.bottom = 0;
          GetWindowRect(pHVar5,&local_34);
          iStack_1c = local_34.right - local_34.left;
          iStack_18 = local_34.bottom - local_34.top;
          local_24 = local_34.left;
          iStack_20 = local_34.top;
          if (((((*piVar4 <= local_34.left) && (iVar1 = piVar4[2], local_34.left < *piVar4 + iVar1))
               && (piVar4[1] <= local_34.top)) &&
              (iVar2 = piVar4[3], local_34.top < piVar4[1] + iVar2)) &&
             (((iStack_1c == iVar1 && (iStack_18 < iVar2)) ||
              ((iStack_18 == iVar2 && (iStack_1c < iVar1)))))) {
            local_14 = local_34.left;
            iStack_10 = local_34.top;
            iStack_c = iStack_1c;
            iStack_8 = iStack_18;
          }
        }
        if ((iStack_c != 0) && (iStack_8 != 0)) {
          *piVar4 = local_14;
          piVar4[1] = iStack_10;
          piVar4[2] = iStack_c;
          piVar4[3] = iStack_8;
        }
      }
      goto LAB_0040e591;
    }
  }
  piVar7 = FUN_0040e2b0(param_1,&local_14);
  iVar1 = piVar7[1];
  iVar2 = piVar7[2];
  iVar3 = piVar7[3];
  *piVar4 = *piVar7;
  piVar4[1] = iVar1;
  piVar4[2] = iVar2;
  piVar4[3] = iVar3;
LAB_0040e591:
  if ((piVar4[2] < 0x1e) || (piVar4[3] < 5)) {
    iVar1 = param_2[1];
    iVar2 = param_2[2];
    iVar3 = param_2[3];
    *piVar4 = *param_2;
    piVar4[1] = iVar1;
    piVar4[2] = iVar2;
    piVar4[3] = iVar3;
  }
  return piVar4;
}


