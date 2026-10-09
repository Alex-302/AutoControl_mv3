// FUN_0046c79a @ 0046c79a size=212 callers=2

void __cdecl FUN_0046c79a(int param_1,uint param_2,int *param_3)

{
  uint uVar1;
  double dVar2;
  uint uVar3;
  ushort uVar4;
  int iVar5;
  
  dVar2 = (double)CONCAT17(param_2._3_1_,
                           CONCAT16(param_2._2_1_,CONCAT24((undefined2)param_2,param_1)));
  if (dVar2 == 0.0) {
    iVar5 = 0;
  }
  else if (((param_2 & 0x7ff00000) == 0) && (((param_2 & 0xfffff) != 0 || (param_1 != 0)))) {
    iVar5 = -0x3fd;
    uVar3 = param_2;
    if ((param_2 & 0x100000) == 0) {
      do {
        uVar1 = uVar3 * 2;
        param_2._0_2_ = (undefined2)uVar1;
        uVar3 = uVar1;
        if (param_1 < 0) {
          uVar3 = uVar1 | 1;
          param_2._0_2_ = (undefined2)uVar3;
        }
        param_1 = param_1 * 2;
        iVar5 = iVar5 + -1;
      } while ((uVar1 & 0x100000) == 0);
      param_2 = CONCAT22((short)(uVar1 >> 0x10),(undefined2)param_2);
    }
    uVar4 = (ushort)(param_2 >> 0x10) & 0xffef;
    param_2._2_1_ = (undefined1)uVar4;
    param_2._3_1_ = (byte)(uVar4 >> 8);
    if (dVar2 < 0.0) {
      param_2._3_1_ = param_2._3_1_ | 0x80;
    }
    __set_exp(CONCAT17(param_2._3_1_,CONCAT16(param_2._2_1_,CONCAT24((undefined2)param_2,param_1))),
              0);
  }
  else {
    __set_exp(dVar2,0);
    iVar5 = (param_2 >> 0x14 & 0x7ff) - 0x3fe;
  }
  *param_3 = iVar5;
  return;
}


