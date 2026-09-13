// FUN_004023d0 @ 004023d0 size=94 callers=16

uint __fastcall FUN_004023d0(byte *param_1,byte *param_2,uint param_3)

{
  uint uVar1;
  bool bVar2;
  
  if (param_3 != 0) {
    while (uVar1 = param_3 - 4, 3 < param_3) {
      if (*(int *)param_1 != *(int *)param_2) goto LAB_004023f6;
      param_1 = param_1 + 4;
      param_2 = param_2 + 4;
      param_3 = uVar1;
    }
    if (uVar1 != 0xfffffffc) {
LAB_004023f6:
      bVar2 = *param_1 < *param_2;
      if ((*param_1 != *param_2) ||
         ((uVar1 != 0xfffffffd &&
          ((bVar2 = param_1[1] < param_2[1], param_1[1] != param_2[1] ||
           ((uVar1 != 0xfffffffe &&
            ((bVar2 = param_1[2] < param_2[2], param_1[2] != param_2[2] ||
             ((uVar1 != 0xffffffff && (bVar2 = param_1[3] < param_2[3], param_1[3] != param_2[3]))))
            )))))))) {
        return -(uint)bVar2 | 1;
      }
    }
  }
  return 0;
}


