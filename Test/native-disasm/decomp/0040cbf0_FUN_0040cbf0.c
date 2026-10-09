// FUN_0040cbf0 @ 0040cbf0 size=1133 callers=1

void __fastcall
FUN_0040cbf0(HWND param_1,int *param_2,char param_3,short param_4,char param_5,char param_6)

{
  void **ppvVar1;
  int *piVar2;
  short sVar3;
  void *_Memory;
  int *extraout_EDX;
  uint uVar4;
  char cVar5;
  uint uVar6;
  int iVar7;
  LONG X;
  undefined4 uVar8;
  undefined4 uVar9;
  char in_stack_0000000f;
  char local_f4 [16];
  undefined1 local_e4 [16];
  char local_d4 [4];
  int local_d0 [3];
  char local_c4 [16];
  char local_b4 [8];
  undefined8 local_ac;
  undefined1 local_a4 [8];
  undefined8 local_9c;
  undefined1 local_94 [8];
  undefined8 local_8c;
  undefined1 local_84 [8];
  undefined8 local_7c;
  char local_74 [8];
  undefined8 local_6c;
  undefined1 local_64 [8];
  undefined8 local_5c;
  undefined1 local_54 [8];
  undefined8 local_4c;
  char local_44 [4];
  void *local_40 [2];
  int local_38;
  void *local_34;
  undefined4 local_30;
  int local_2c;
  HWND local_28;
  ULONG_PTR local_24;
  uint local_20;
  void *local_1c;
  tagPOINT local_18;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047a12a;
  local_10 = ExceptionList;
  local_20 = 0;
  local_28 = param_1;
  if (param_6 == '\0') {
    ExceptionList = &local_10;
    ppvVar1 = (void **)FUN_0040c920((int *)&local_34);
    uVar6 = 2;
    piVar2 = extraout_EDX;
  }
  else {
    local_1c = (void *)0x0;
    local_18.x = 0;
    local_18.y = 0;
    ppvVar1 = &local_1c;
    uVar6 = 1;
    piVar2 = param_2;
    ExceptionList = &local_10;
  }
  local_8 = (uint)(param_6 == '\0');
  local_20 = uVar6;
  FUN_004335f0((int *)local_40,piVar2,(int *)ppvVar1);
  local_8 = 2;
  if (((uVar6 & 2) != 0) && (uVar6 = uVar6 & 0xfffffffd, local_34 != (void *)0x0)) {
    FUN_00402430(local_34,local_2c - (int)local_34 >> 1,2);
    local_34 = (void *)0x0;
    local_30 = 0;
    local_2c = 0;
  }
  local_8._0_1_ = 4;
  if (((uVar6 & 1) != 0) && (local_1c != (void *)0x0)) {
    FUN_00402430(local_1c,local_18.y - (int)local_1c >> 1,2);
  }
  if ((param_5 == '\x01') || ((param_3 == 'H' && (DAT_004a24ae == '\0')))) {
    GetCursorPos(&local_18);
    X = local_18.x;
    if ((local_18.x == *param_2) && (local_18.y == param_2[1])) {
      cVar5 = '\0';
    }
    else {
      cVar5 = '\x01';
    }
    local_20 = (uint)(0 < param_4);
    in_stack_0000000f = cVar5;
    if (param_6 == '\0') {
      Sleep(0x14);
    }
    if (cVar5 != '\0') {
      SetCursorPos(*param_2,param_2[1]);
    }
    uVar6 = local_20;
    uVar4 = (int)param_4 >> 0x1f;
    iVar7 = ((int)param_4 ^ uVar4) - uVar4;
    if (0 < iVar7) {
      do {
        SendMessageTimeoutA(local_28,(param_3 == 'V') + 0x114,uVar6,0,3,500,&local_24);
        iVar7 = iVar7 + -1;
        X = local_18.x;
        cVar5 = in_stack_0000000f;
      } while (iVar7 != 0);
    }
    if (cVar5 != '\0') {
      SetCursorPos(X,local_18.y);
    }
  }
  else if (param_5 == '\x02') {
    GetCursorPos(&local_18);
    local_b4[0] = '\0';
    uVar8 = 0;
    uVar9 = 0;
    local_ac = 0;
    FUN_004512e0(local_b4,(param_3 != 'V') + 0x200);
    local_a4[0] = 0;
    local_9c = CONCAT44(uVar9,uVar8);
    FUN_00450f50(local_a4,*param_2);
    local_94[0] = 0;
    local_8c = CONCAT44(uVar9,uVar8);
    FUN_00450f50(local_94,param_2[1]);
    local_84[0] = 0;
    local_7c = CONCAT44(uVar9,uVar8);
    FUN_00451300(local_84,param_4);
    local_8._0_1_ = 5;
    FUN_00434b50(local_f4,local_b4,local_74,'\x01','\x02');
    local_8._0_1_ = 7;
    _eh_vector_destructor_iterator_(local_b4,0x10,4,FUN_00434820);
    uVar8 = 0;
    uVar9 = 0;
    local_74[0] = '\0';
    local_6c = 0;
    FUN_004512e0(local_74,0x202);
    local_64[0] = 0;
    local_5c = CONCAT44(uVar9,uVar8);
    FUN_00450f50(local_64,local_18.x);
    local_54[0] = 0;
    local_4c = CONCAT44(uVar9,uVar8);
    FUN_00450f50(local_54,local_18.y);
    local_8._0_1_ = 8;
    FUN_00434b50(local_e4,local_74,local_44,'\x01','\x02');
    local_8._0_1_ = 10;
    _eh_vector_destructor_iterator_(local_74,0x10,3,FUN_00434820);
    local_8._0_1_ = 0xb;
    FUN_00434b50(local_c4,local_f4,local_d4,'\x01','\x02');
    local_8._0_1_ = 0xc;
    piVar2 = FUN_0040c190(local_d0,local_c4,0xd6c18935,'\0');
    SendInput((piVar2[1] - *piVar2) / 0x1c,(LPINPUT)*piVar2,0x1c);
    FUN_00432b50(local_d0);
    FUN_00434820(local_c4);
    local_8._0_1_ = 4;
    _eh_vector_destructor_iterator_(local_f4,0x10,2,FUN_00434820);
  }
  else {
    if (param_6 == '\0') {
      Sleep(0x14);
    }
    sVar3 = 1;
    if (param_3 == 'V') {
      sVar3 = -1;
    }
    SendMessageTimeoutA(param_1,(uint)(param_3 != 'V') * 4 + 0x20a,
                        (uint)(ushort)(sVar3 * param_4 * 0x78) << 0x10,
                        CONCAT22((short)param_2[1],(short)*param_2),3,500,&local_24);
  }
  if ((param_6 == '\0') && (FUN_0040cab0((uint *)&local_1c,local_40), local_1c != (void *)0x0)) {
    FUN_00402430(local_1c,local_18.y - (int)local_1c >> 1,2);
  }
  if (local_40[0] != (void *)0x0) {
    uVar6 = local_38 - (int)local_40[0] >> 1;
    if (0x7fffffff < uVar6) {
                    /* WARNING: Subroutine does not return */
      FUN_00465fb2();
    }
    _Memory = local_40[0];
    if (0xfff < uVar6 * 2) {
      if (((uint)local_40[0] & 0x1f) != 0) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      _Memory = *(void **)((int)local_40[0] + -4);
      if (local_40[0] <= _Memory) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      if ((uint)((int)local_40[0] - (int)_Memory) < 4) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      if (0x23 < (uint)((int)local_40[0] - (int)_Memory)) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
    }
    FID_conflict__free(_Memory);
  }
  ExceptionList = local_10;
  return;
}


