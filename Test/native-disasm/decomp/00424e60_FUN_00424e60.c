// FUN_00424e60 @ 00424e60 size=619 callers=1

void * __cdecl FUN_00424e60(void *param_1,void *param_2)

{
  char cVar1;
  int *piVar2;
  undefined8 uVar3;
  int *piVar4;
  char *pcVar5;
  undefined4 *this;
  undefined4 uVar6;
  BOOL BVar7;
  int nCmdShow;
  void *this_00;
  void *this_01;
  int iVar8;
  int *piVar9;
  int iVar10;
  char local_94 [16];
  undefined1 local_84 [16];
  int local_74 [4];
  char local_64 [16];
  char local_54 [8];
  undefined8 local_4c;
  undefined4 local_40;
  char local_3c [8];
  undefined8 local_34;
  char *local_28;
  int *local_24;
  int local_20;
  int local_1c;
  HWND local_18;
  byte local_13;
  char local_12;
  char local_11;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_0047c02a;
  local_10 = ExceptionList;
  local_8 = 0;
  local_40 = 0;
  ExceptionList = &local_10;
  pcVar5 = (char *)FUN_00440e70(param_2,(uint *)&DAT_0048d818);
  FUN_00455dc0(pcVar5,&local_11);
  FUN_00434b00(local_94,(char *)0x0,(char *)0x0);
  local_8 = 1;
  FUN_00434b00(local_84,(char *)0x0,(char *)0x0);
  local_8 = 2;
  FUN_00434b50(param_1,local_94,(char *)local_74,'\x01','\x02');
  local_40 = 1;
  local_8 = local_8 & 0xffffff00;
  _eh_vector_destructor_iterator_(local_94,0x10,2,FUN_00434820);
  this = FUN_00440e70(param_2,(uint *)&DAT_0048d820);
  FUN_00434120(this,&local_28);
  FUN_004340a0(this_01,local_74);
  uVar6 = FUN_004383a0(&local_28,local_74);
  iVar8 = local_20;
  piVar9 = local_24;
  iVar10 = local_1c;
  if ((char)uVar6 == '\0') {
    do {
      pcVar5 = FUN_00433bc0(&local_28);
      FUN_00434940(local_64,pcVar5);
      local_8 = 3;
      FUN_004536b0(local_64,(uint *)&local_18);
      BVar7 = IsWindowVisible(local_18);
      local_13 = BVar7 == 0;
      if (local_11 != local_13) {
        nCmdShow = 0;
        if ((bool)local_13) {
          nCmdShow = 8;
        }
        ShowWindow(local_18,nCmdShow);
        local_12 = '\0';
        local_4c = 0;
        local_3c[0] = '\0';
        local_34 = 0;
        FUN_00450f50(local_3c,(int)local_18);
        local_54[0] = local_3c[0];
        local_3c[0] = local_12;
        uVar3 = local_34;
        local_34 = local_4c;
        local_4c = uVar3;
        FUN_00434820(local_3c);
        pcVar5 = local_54;
        local_8 = CONCAT31(local_8._1_3_,4);
        this_00 = (void *)FUN_00434600(param_1,(uint)local_13);
        FUN_00433e10(this_00,pcVar5);
        FUN_00434820(local_54);
      }
      local_8 = local_8 & 0xffffff00;
      FUN_00434820(local_64);
      if (*local_28 == '\x01') {
        if (*(char *)((int)piVar9 + 0xd) == '\0') {
          piVar2 = (int *)piVar9[2];
          if (*(char *)((int)piVar2 + 0xd) == '\0') {
            cVar1 = *(char *)(*piVar2 + 0xd);
            piVar9 = piVar2;
            piVar2 = (int *)*piVar2;
            while (local_24 = piVar9, cVar1 == '\0') {
              cVar1 = *(char *)(*piVar2 + 0xd);
              piVar9 = piVar2;
              piVar2 = (int *)*piVar2;
            }
          }
          else {
            cVar1 = *(char *)(piVar9[1] + 0xd);
            piVar4 = (int *)piVar9[1];
            piVar2 = piVar9;
            while ((piVar9 = piVar4, local_24 = piVar9, cVar1 == '\0' &&
                   (piVar2 == (int *)piVar9[2]))) {
              cVar1 = *(char *)(piVar9[1] + 0xd);
              piVar4 = (int *)piVar9[1];
              piVar2 = piVar9;
            }
          }
        }
      }
      else if (*local_28 == '\x02') {
        iVar8 = iVar8 + 0x10;
        local_20 = iVar8;
      }
      else {
        iVar10 = iVar10 + 1;
        local_1c = iVar10;
      }
      uVar6 = FUN_004383a0(&local_28,local_74);
    } while ((char)uVar6 == '\0');
    ExceptionList = local_10;
    return param_1;
  }
  ExceptionList = local_10;
  return param_1;
}


