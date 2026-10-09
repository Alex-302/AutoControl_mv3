// assemble_floating_point_value @ 004608d6 size=844 callers=3

/* WARNING: Removing unreachable block (ram,0x00460a7f) */
/* WARNING: Removing unreachable block (ram,0x00460b9c) */
/* Library Function - Single Match
    enum SLD_STATUS __cdecl __crt_strtox::assemble_floating_point_value(unsigned
   __int64,int,bool,bool,class __crt_strtox::floating_point_value const &)
   
   Library: Visual Studio 2015 Release */

SLD_STATUS __cdecl
__crt_strtox::assemble_floating_point_value
          (__uint64 param_1,int param_2,bool param_3,bool param_4,floating_point_value *param_5)

{
  floating_point_value fVar1;
  bool bVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  double *pdVar6;
  SLD_STATUS SVar7;
  float *pfVar8;
  byte bVar9;
  int iVar10;
  uint uVar11;
  ulonglong uVar12;
  ulonglong uVar13;
  __uint64 _Var14;
  int local_c;
  
  uVar11 = 0;
  if (param_1._4_4_ == 0) {
    iVar10 = 0x1f;
    if ((uint)param_1 != 0) {
      for (; (uint)param_1 >> iVar10 == 0; iVar10 = iVar10 + -1) {
      }
    }
    if ((uint)param_1 == 0) {
      iVar10 = 0;
    }
    else {
      iVar10 = iVar10 + 1;
    }
  }
  else {
    iVar10 = 0x1f;
    if (param_1._4_4_ != 0) {
      for (; param_1._4_4_ >> iVar10 == 0; iVar10 = iVar10 + -1) {
      }
    }
    iVar10 = iVar10 + 1;
    if (param_1._4_4_ == 0) {
      iVar10 = 0;
    }
    iVar10 = iVar10 + 0x20;
  }
  fVar1 = param_5[4];
  iVar10 = (((fVar1 == (floating_point_value)0x0) - 1 & 0x1d) + 0x18) - iVar10;
  local_c = param_2 - iVar10;
  uVar3 = (fVar1 == (floating_point_value)0x0) - 1 & 0x380;
  iVar4 = uVar3 + 0x7f;
  if (iVar4 < local_c) {
LAB_00460952:
    assemble_floating_point_infinity(param_3,param_5);
    return 3;
  }
  if (local_c < (int)(((fVar1 == (floating_point_value)0x0) - 1 & 0xfffffc80) - 0x7e)) {
    iVar5 = uVar3 + 0x7e + local_c + iVar10;
    local_c = -iVar4;
    if (iVar5 < 0) {
      if ((uint)-iVar5 < 0x40) {
        bVar9 = (byte)-iVar5;
        uVar12 = __allshl(bVar9 - 1,0);
        uVar13 = __allshl(bVar9,0);
        bVar2 = false;
        if ((!param_4) || ((uVar12 - 1 & param_1) != 0)) {
          bVar2 = true;
        }
        if (((param_1 & uVar12) != 0) || (bVar2)) {
          uVar3 = FUN_0046aee8();
          if (uVar3 == 0) {
            if (((param_1 & uVar12) != 0) && ((bVar2 || ((param_1 & uVar13) != 0)))) {
              uVar11 = 1;
            }
          }
          else if (uVar3 == 0x100) {
            uVar11 = (uint)!param_3;
          }
          else if (uVar3 == 0x200) {
            uVar11 = (uint)param_3;
          }
        }
        uVar12 = __aullshr(bVar9,param_1._4_4_);
        param_1 = uVar12 + uVar11;
        if (param_1 != 0) {
          _Var14 = floating_point_value::denormal_mantissa_mask(param_5);
          if (_Var14 < param_1) {
            local_c = ((param_2 - iVar5) - iVar10) + -1;
          }
          goto LAB_00460bdd;
        }
      }
      assemble_floating_point_zero(param_3,param_5);
      return 2;
    }
    bVar9 = (byte)iVar5;
  }
  else {
    if (iVar10 < 0) {
      if ((uint)-iVar10 < 0x40) {
        bVar9 = (byte)-iVar10;
        uVar12 = __allshl(bVar9 - 1,0);
        uVar13 = __allshl(bVar9,0);
        if ((!param_4) || (bVar2 = false, (uVar12 - 1 & param_1) != 0)) {
          bVar2 = true;
        }
        if (((uVar12 & param_1) != 0) || (bVar2)) {
          uVar3 = FUN_0046aee8();
          if (uVar3 == 0) {
            if (((uVar12 & param_1) != 0) && ((bVar2 || ((uVar13 & param_1) != 0)))) {
              uVar11 = 1;
            }
          }
          else if (uVar3 == 0x100) {
            uVar11 = (uint)!param_3;
          }
          else if (uVar3 == 0x200) {
            uVar11 = (uint)param_3;
          }
        }
        uVar12 = __aullshr(bVar9,param_1._4_4_);
        param_1 = uVar12 + uVar11;
      }
      else {
        param_1 = 0;
      }
      _Var14 = floating_point_value::normal_mantissa_mask(param_5);
      if (_Var14 < param_1) {
        param_1 = param_1 >> 1;
        local_c = local_c + 1;
        if ((int)(((param_5[4] == (floating_point_value)0x0) - 1 & 0x380) + 0x7f) < local_c)
        goto LAB_00460952;
      }
      goto LAB_00460bdd;
    }
    if (iVar10 < 1) goto LAB_00460bdd;
    bVar9 = (byte)iVar10;
  }
  param_1 = __allshl(bVar9,param_1._4_4_);
LAB_00460bdd:
  _Var14 = floating_point_value::denormal_mantissa_mask(param_5);
  if (param_5[4] == (floating_point_value)0x0) {
    pfVar8 = (float *)FUN_00460877((undefined4 *)param_5);
    SVar7 = assemble_floating_point_value_t<float>(param_3,local_c,param_1 & _Var14,pfVar8);
  }
  else {
    pdVar6 = (double *)FUN_00460852((undefined4 *)param_5);
    SVar7 = assemble_floating_point_value_t<double>(param_3,local_c,param_1 & _Var14,pdVar6);
  }
  return SVar7;
}


