// __handle_exc @ 0046cadf size=480 callers=3

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __handle_exc
   
   Library: Visual Studio 2015 Release */

bool __cdecl __handle_exc(uint param_1,double *param_2,uint param_3)

{
  double dVar1;
  double dVar2;
  double dVar3;
  int iVar4;
  uint uVar5;
  bool bVar6;
  float10 fVar7;
  float10 fVar8;
  uint local_14;
  byte bStack_10;
  undefined1 uStack_f;
  ushort uStack_e;
  int local_8;
  
  uVar5 = param_1 & 0x1f;
  if (((param_1 & 8) != 0) && ((param_3 & 1) != 0)) {
    FUN_0046d166();
    uVar5 = param_1 & 0x17;
    goto LAB_0046cc9c;
  }
  if ((param_1 & param_3 & 4) != 0) {
    FUN_0046d166();
    uVar5 = param_1 & 0x1b;
    goto LAB_0046cc9c;
  }
  if (((param_1 & 1) == 0) || ((param_3 & 8) == 0)) {
    if (((param_1 & 2) != 0) && ((param_3 & 0x10) != 0)) {
      bVar6 = (param_1 & 0x10) != 0;
      if (*param_2 == 0.0) {
        bVar6 = true;
      }
      else {
        fVar7 = (float10)FUN_0046c79a(SUB84(*param_2,0),(uint)((ulonglong)*param_2 >> 0x20),&local_8
                                     );
        local_8 = local_8 + -0x600;
        dVar2 = (double)fVar7;
        local_14 = SUB84(dVar2,0);
        bStack_10 = (byte)((ulonglong)dVar2 >> 0x20);
        uStack_f = (undefined1)((ulonglong)dVar2 >> 0x28);
        uStack_e = (ushort)((ulonglong)dVar2 >> 0x30);
        if (local_8 < -0x432) {
          fVar8 = (float10)0 * fVar7;
          bVar6 = true;
        }
        else {
          uStack_e = uStack_e & 0xf | 0x10;
          if (local_8 < -0x3fd) {
            iVar4 = -0x3fd - local_8;
            do {
              if (((local_14 & 1) != 0) && (!bVar6)) {
                bVar6 = true;
              }
              local_14 = local_14 >> 1;
              if ((bStack_10 & 1) != 0) {
                local_14 = local_14 | 0x80000000;
              }
              uVar5 = CONCAT22(uStack_e,CONCAT11(uStack_f,bStack_10)) >> 1;
              bStack_10 = (byte)uVar5;
              uStack_f = (undefined1)(uVar5 >> 8);
              uStack_e = uStack_e >> 1;
              iVar4 = iVar4 + -1;
            } while (iVar4 != 0);
          }
          fVar8 = (float10)(double)CONCAT26(uStack_e,CONCAT15(uStack_f,CONCAT14(bStack_10,local_14))
                                           );
          if (fVar7 < (float10)0) {
            fVar8 = -fVar8;
          }
        }
        *param_2 = (double)fVar8;
      }
      if (bVar6) {
        FUN_0046d166();
      }
      uVar5 = param_1 & 0x1d;
    }
    goto LAB_0046cc9c;
  }
  FUN_0046d166();
  uVar5 = param_3 & 0xc00;
  dVar2 = _DAT_004868d8;
  dVar3 = _DAT_004868d8;
  if (uVar5 == 0) {
    dVar1 = *param_2;
joined_r0x0046cb80:
    if (dVar1 <= 0.0) {
      dVar2 = -dVar3;
    }
    *param_2 = dVar2;
  }
  else {
    if (uVar5 == 0x400) {
      dVar1 = *param_2;
      dVar2 = _DAT_004868e0;
      goto joined_r0x0046cb80;
    }
    dVar3 = _DAT_004868e0;
    if (uVar5 == 0x800) {
      dVar1 = *param_2;
      goto joined_r0x0046cb80;
    }
    if (uVar5 == 0xc00) {
      dVar1 = *param_2;
      dVar2 = _DAT_004868e0;
      goto joined_r0x0046cb80;
    }
  }
  uVar5 = param_1 & 0x1e;
LAB_0046cc9c:
  if (((param_1 & 0x10) != 0) && ((param_3 & 0x20) != 0)) {
    FUN_0046d166();
    uVar5 = uVar5 & 0xffffffef;
  }
  return uVar5 == 0;
}


