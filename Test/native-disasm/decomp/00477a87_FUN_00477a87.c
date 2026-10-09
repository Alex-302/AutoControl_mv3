// FUN_00477a87 @ 00477a87 size=174 callers=2

ushort * __cdecl FUN_00477a87(ushort *param_1,ushort param_2)

{
  int iVar1;
  undefined1 auVar2 [16];
  undefined1 auVar3 [16];
  undefined1 auVar5 [14];
  undefined1 auVar4 [16];
  ushort uVar6;
  ushort uVar7;
  int iStack_34;
  
  if (0 < DAT_0049f178) {
    auVar2 = pshuflw(ZEXT216(param_2),ZEXT216(param_2),0);
    do {
      if (((uint)param_1 & 0xfff) < 0xff1) {
        auVar5 = SUB1614((undefined1  [16])0x0,2);
        auVar4._0_2_ = -(ushort)(*param_1 == 0);
        auVar4._2_2_ = -(ushort)(param_1[1] == 0);
        auVar4._4_2_ = -(ushort)(param_1[2] == 0);
        auVar4._6_2_ = -(ushort)(param_1[3] == 0);
        auVar4._8_2_ = -(ushort)(param_1[4] == 0);
        auVar4._10_2_ = -(ushort)(auVar5._8_2_ == param_1[5]);
        auVar4._12_2_ = -(ushort)(auVar5._10_2_ == param_1[6]);
        auVar4._14_2_ = -(ushort)(auVar5._12_2_ == param_1[7]);
        uVar6 = auVar2._0_2_;
        auVar3._0_2_ = -(ushort)(*param_1 == uVar6);
        uVar7 = auVar2._2_2_;
        auVar3._2_2_ = -(ushort)(param_1[1] == uVar7);
        auVar3._4_2_ = -(ushort)(param_1[2] == uVar6);
        auVar3._6_2_ = -(ushort)(param_1[3] == uVar7);
        auVar3._8_2_ = -(ushort)(param_1[4] == uVar6);
        auVar3._10_2_ = -(ushort)(param_1[5] == uVar7);
        auVar3._12_2_ = -(ushort)(param_1[6] == uVar6);
        auVar3._14_2_ = -(ushort)(param_1[7] == uVar7);
        auVar4 = auVar4 | auVar3;
        uVar6 = (ushort)(SUB161(auVar4 >> 7,0) & 1) | (ushort)(SUB161(auVar4 >> 0xf,0) & 1) << 1 |
                (ushort)(SUB161(auVar4 >> 0x17,0) & 1) << 2 |
                (ushort)(SUB161(auVar4 >> 0x1f,0) & 1) << 3 |
                (ushort)(SUB161(auVar4 >> 0x27,0) & 1) << 4 |
                (ushort)(SUB161(auVar4 >> 0x2f,0) & 1) << 5 |
                (ushort)(SUB161(auVar4 >> 0x37,0) & 1) << 6 |
                (ushort)(SUB161(auVar4 >> 0x3f,0) & 1) << 7 |
                (ushort)(SUB161(auVar4 >> 0x47,0) & 1) << 8 |
                (ushort)(SUB161(auVar4 >> 0x4f,0) & 1) << 9 |
                (ushort)(SUB161(auVar4 >> 0x57,0) & 1) << 10 |
                (ushort)(SUB161(auVar4 >> 0x5f,0) & 1) << 0xb |
                (ushort)(SUB161(auVar4 >> 0x67,0) & 1) << 0xc |
                (ushort)(SUB161(auVar4 >> 0x6f,0) & 1) << 0xd |
                (ushort)(SUB161(auVar4 >> 0x77,0) & 1) << 0xe |
                (ushort)(byte)(auVar4[0xf] >> 7) << 0xf;
        if (uVar6 != 0) goto LAB_00477b1e;
        iStack_34 = 0x10;
      }
      else {
        if (*param_1 == param_2) {
          return param_1;
        }
        if (*param_1 == 0) {
          return (ushort *)0x0;
        }
        iStack_34 = 2;
      }
      param_1 = (ushort *)((int)param_1 + iStack_34);
    } while( true );
  }
  for (; (*param_1 != 0 && (*param_1 != param_2)); param_1 = param_1 + 1) {
  }
LAB_00477afd:
  return (ushort *)((*param_1 != param_2) - 1 & (uint)param_1);
LAB_00477b1e:
  iVar1 = 0;
  if (uVar6 != 0) {
    for (; (uVar6 >> iVar1 & 1) == 0; iVar1 = iVar1 + 1) {
    }
  }
  param_1 = (ushort *)((int)param_1 + iVar1);
  goto LAB_00477afd;
}


