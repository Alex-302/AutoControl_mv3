// FUN_00430710 @ 00430710 size=625 callers=1

void __fastcall FUN_00430710(undefined4 *param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  char *pcVar5;
  undefined4 *this;
  char *pcVar6;
  char *extraout_ECX;
  uint uVar7;
  uint uVar8;
  char local_4c [8];
  undefined8 local_44;
  char local_3c [4];
  char *local_38;
  undefined8 local_34;
  undefined1 *local_2c;
  undefined4 *local_28;
  undefined4 *local_24;
  undefined4 *local_20;
  undefined4 *local_1c;
  uint local_15;
  undefined1 local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047d701;
  local_10 = ExceptionList;
  local_3c[0] = '\0';
  local_34 = 0;
  ExceptionList = &local_10;
  local_1c = param_1;
  FUN_0044dd50(local_3c,&DAT_004a2514);
  local_8 = 0;
  pcVar5 = (char *)FUN_00440e70((void *)*param_1,(uint *)"myWins");
  local_8 = 0xffffffff;
  cVar1 = *pcVar5;
  *pcVar5 = local_3c[0];
  uVar2 = *(undefined4 *)(pcVar5 + 8);
  uVar3 = *(undefined4 *)(pcVar5 + 0xc);
  *(char **)(pcVar5 + 8) = (char *)local_34;
  *(int *)(pcVar5 + 0xc) = local_34._4_4_;
  local_3c[0] = cVar1;
  local_34._0_4_ = (char *)uVar2;
  local_34._4_4_ = uVar3;
  FUN_00434820(local_3c);
  FUN_00434b00(local_3c,(char *)0x0,(char *)0x0);
  local_8 = 1;
  pcVar5 = (char *)FUN_00440e70((void *)*param_1,(uint *)"downKeys");
  local_8 = 0xffffffff;
  cVar1 = *pcVar5;
  *pcVar5 = local_3c[0];
  uVar4 = *(undefined8 *)(pcVar5 + 8);
  *(char **)(pcVar5 + 8) = (char *)local_34;
  *(int *)(pcVar5 + 0xc) = local_34._4_4_;
  local_3c[0] = cVar1;
  local_34 = uVar4;
  FUN_00434820(local_3c);
  uVar7 = 0;
  uVar8 = DAT_004a28bc;
  if (DAT_004a28bc != 0) {
    do {
      if ((*(uint *)(DAT_004a28b0 + (uVar7 >> 5) * 4) & 1 << ((byte)uVar7 & 0x1f)) != 0) {
        local_4c[0] = '\0';
        local_44 = 0;
        FUN_00451040(local_4c,uVar7);
        local_8 = 2;
        FUN_00433e10(pcVar5,extraout_ECX);
        local_8 = 0xffffffff;
        FUN_00434820(local_4c);
        uVar8 = DAT_004a28bc;
      }
      uVar7 = uVar7 + 1;
    } while (uVar7 < uVar8);
  }
  local_15 = local_15 & 0xffffff00;
  local_38 = (char *)0x0;
  local_34 = 0;
  FUN_00447980(&local_38,(uint *)&DAT_004a26b8,0x4a26c2);
  local_8 = 3;
  local_44 = 0;
  local_4c[0] = '\x02';
  this = operator_new(0xc);
  pcVar5 = local_38;
  local_2c = &local_11;
  local_8._0_1_ = 5;
  local_28 = this;
  local_24 = this;
  local_20 = this;
  if (this != (undefined4 *)0x0) {
    local_15 = local_15 & 0xffffff00;
    *this = 0;
    this[1] = 0;
    this[2] = 0;
    FUN_00457c20(this,local_38,(char *)local_34);
  }
  local_8 = CONCAT31(local_8._1_3_,6);
  local_44._0_4_ = this;
  pcVar6 = (char *)FUN_00440e70((void *)*local_1c,(uint *)&DAT_0048d7ac);
  local_4c[0] = *pcVar6;
  *pcVar6 = '\x02';
  uVar4 = *(undefined8 *)(pcVar6 + 8);
  *(undefined4 **)(pcVar6 + 8) = this;
  *(undefined4 *)(pcVar6 + 0xc) = local_44._4_4_;
  local_44 = uVar4;
  FUN_00434820(local_4c);
  if (pcVar5 != (char *)0x0) {
    pcVar6 = pcVar5;
    if (0xfff < (uint)(local_34._4_4_ - (int)pcVar5)) {
      if (((uint)pcVar5 & 0x1f) != 0) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      pcVar6 = *(char **)(pcVar5 + -4);
      if (pcVar5 <= pcVar6) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      if ((uint)((int)pcVar5 - (int)pcVar6) < 4) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
      if (0x23 < (uint)((int)pcVar5 - (int)pcVar6)) {
                    /* WARNING: Subroutine does not return */
        FUN_00465fb2();
      }
    }
    FID_conflict__free(pcVar6);
  }
  ExceptionList = local_10;
  return;
}


