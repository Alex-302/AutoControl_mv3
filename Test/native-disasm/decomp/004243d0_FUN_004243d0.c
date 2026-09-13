// FUN_004243d0 @ 004243d0 size=350 callers=1

undefined1 * __cdecl FUN_004243d0(undefined1 *param_1,void *param_2)

{
  int *piVar1;
  HWND hWnd;
  int *piVar2;
  char cVar3;
  char *pcVar4;
  undefined4 *this;
  undefined4 uVar5;
  uint uVar6;
  void *this_00;
  int iVar7;
  int *piVar8;
  int local_3c [4];
  char *local_2c;
  int *local_28;
  int local_24;
  int local_20;
  undefined4 local_1c;
  HWND local_18;
  byte local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004791a6;
  local_10 = ExceptionList;
  local_1c = 0;
  ExceptionList = &local_10;
  pcVar4 = (char *)FUN_00440e70(param_2,(uint *)&DAT_0048d818);
  FUN_00455dc0(pcVar4,(char *)&local_11);
  this = FUN_00440e70(param_2,(uint *)&DAT_0048d820);
  FUN_00434120(this,&local_2c);
  FUN_004340a0(this_00,local_3c);
  uVar5 = FUN_004383a0(&local_2c,local_3c);
  cVar3 = (char)uVar5;
  piVar8 = local_28;
  iVar7 = local_20;
  while (cVar3 == '\0') {
    pcVar4 = FUN_00433bc0(&local_2c);
    FUN_004536b0(pcVar4,(uint *)&local_18);
    hWnd = local_18;
    uVar6 = GetWindowLongA(local_18,-0x14);
    if (local_11 != ((byte)(uVar6 >> 3) & 1)) {
      SetWindowPos(hWnd,(HWND)(((uVar6 >> 3 & 1) == 0) - 2),0,0,0,0,0x13);
    }
    if (*local_2c == '\x01') {
      if (*(char *)((int)piVar8 + 0xd) == '\0') {
        piVar1 = (int *)piVar8[2];
        if (*(char *)((int)piVar1 + 0xd) == '\0') {
          cVar3 = *(char *)(*piVar1 + 0xd);
          piVar8 = piVar1;
          piVar1 = (int *)*piVar1;
          while (local_28 = piVar8, cVar3 == '\0') {
            cVar3 = *(char *)(*piVar1 + 0xd);
            piVar8 = piVar1;
            piVar1 = (int *)*piVar1;
          }
        }
        else {
          cVar3 = *(char *)(piVar8[1] + 0xd);
          piVar2 = (int *)piVar8[1];
          piVar1 = piVar8;
          while ((piVar8 = piVar2, local_28 = piVar8, cVar3 == '\0' && (piVar1 == (int *)piVar8[2]))
                ) {
            cVar3 = *(char *)(piVar8[1] + 0xd);
            piVar2 = (int *)piVar8[1];
            piVar1 = piVar8;
          }
        }
      }
    }
    else if (*local_2c == '\x02') {
      local_24 = local_24 + 0x10;
    }
    else {
      iVar7 = iVar7 + 1;
      local_20 = iVar7;
    }
    uVar5 = FUN_004383a0(&local_2c,local_3c);
    cVar3 = (char)uVar5;
  }
  local_8 = 0;
  *param_1 = 0;
  FUN_004381d0(param_1 + 8,'\0');
  ExceptionList = local_10;
  return param_1;
}


