// FUN_00453b50 @ 00453b50 size=309 callers=1

void __fastcall FUN_00453b50(int *param_1)

{
  bool bVar1;
  char cVar2;
  byte bVar3;
  undefined3 extraout_var;
  char *pcVar5;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  undefined3 extraout_var_02;
  uint local_4;
  int iVar4;
  
  bVar1 = FUN_004554b0(param_1);
  iVar4 = CONCAT31(extraout_var,bVar1);
  if (iVar4 == 0) {
    return;
  }
  do {
    if (iVar4 != 2) {
      if ((param_1[0x11] == 0) && ((param_1[0x14] & 0x100000U) == 0)) {
                    /* WARNING: Subroutine does not return */
        FUN_00458f04(2);
      }
      if (param_1[0x13] == 0x2d) {
        pcVar5 = (char *)*param_1;
        if (pcVar5 != (char *)param_1[2]) {
          if (((*pcVar5 == '\\') && (pcVar5 = pcVar5 + 1, pcVar5 != (char *)param_1[2])) &&
             ((((param_1[0x14] & 8U) == 0 && ((*pcVar5 == '(' || (*pcVar5 == ')')))) ||
              (((param_1[0x14] & 0x10U) == 0 && ((*pcVar5 == '{' || (*pcVar5 == '}')))))))) {
            *param_1 = (int)pcVar5;
          }
          *param_1 = *param_1 + 1;
        }
        FUN_00449160(param_1);
        bVar3 = *(byte *)(param_1 + 0x11);
        bVar1 = FUN_004554b0(param_1);
        iVar4 = CONCAT31(extraout_var_00,bVar1);
        if (iVar4 == 0) {
          local_4 = CONCAT31(local_4._1_3_,(char)param_1[0x11]);
          FUN_00455950(param_1 + 9,local_4);
          FUN_00455950(param_1 + 9,0x2d);
          return;
        }
        if (iVar4 == 2) {
LAB_00453c7e:
                    /* WARNING: Subroutine does not return */
          FUN_00458f04(8);
        }
        if ((param_1[0x10] & 0x800U) != 0) {
          cVar2 = FUN_0044d7d0((void *)param_1[0xf],(char)param_1[0x11]);
          param_1[0x11] = (int)cVar2;
          bVar3 = FUN_0044d7d0((void *)param_1[0xf],bVar3);
          iVar4 = CONCAT31(extraout_var_01,bVar3);
        }
        if (*(byte *)(param_1 + 0x11) < bVar3) goto LAB_00453c7e;
        FUN_004556b0(param_1 + 9,bVar3,CONCAT31((int3)((uint)iVar4 >> 8),*(byte *)(param_1 + 0x11)))
        ;
      }
      else {
        local_4 = CONCAT31(local_4._1_3_,(char)param_1[0x11]);
        FUN_00455950(param_1 + 9,local_4);
      }
    }
    bVar1 = FUN_004554b0(param_1);
    iVar4 = CONCAT31(extraout_var_02,bVar1);
    if (iVar4 == 0) {
      return;
    }
  } while( true );
}


