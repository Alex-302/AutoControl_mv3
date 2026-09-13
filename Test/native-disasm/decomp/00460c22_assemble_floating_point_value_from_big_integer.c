// assemble_floating_point_value_from_big_integer @ 00460c22 size=398 callers=1

/* Library Function - Single Match
    enum SLD_STATUS __cdecl __crt_strtox::assemble_floating_point_value_from_big_integer(struct
   __crt_strtox::big_integer const &,unsigned int,bool,bool,class __crt_strtox::floating_point_value
   const &)
   
   Library: Visual Studio 2015 Release */

SLD_STATUS __cdecl
__crt_strtox::assemble_floating_point_value_from_big_integer
          (big_integer *param_1,uint param_2,bool param_3,bool param_4,floating_point_value *param_5
          )

{
  __uint64 _Var1;
  uint uVar2;
  SLD_STATUS SVar3;
  byte bVar4;
  undefined4 uVar5;
  int iVar6;
  undefined4 uVar7;
  int iVar8;
  bool bVar9;
  longlong lVar10;
  longlong lVar11;
  ulonglong uVar12;
  
  iVar6 = ((param_5[4] == (floating_point_value)0x0) - 1 & 0x1d) + 0x17;
  if (param_2 < 0x41) {
    if (*(int *)param_1 == 0) {
      uVar7 = 0;
    }
    else {
      uVar7 = *(undefined4 *)(param_1 + 4);
    }
    if (*(uint *)param_1 < 2) {
      uVar5 = 0;
    }
    else {
      uVar5 = *(undefined4 *)(param_1 + 8);
    }
    bVar9 = !param_4;
  }
  else {
    uVar2 = param_2 & 0x1f;
    iVar8 = (param_2 >> 5) - 2;
    if (uVar2 != 0) {
      bVar9 = true;
      iVar6 = iVar8 * 0x20 + uVar2 + iVar6;
      bVar4 = (byte)uVar2;
      uVar2 = *(uint *)(param_1 + iVar8 * 4 + 4);
      lVar10 = __allshl(-bVar4 + 0x20,0);
      lVar11 = __allshl(-bVar4 + 0x40,0);
      uVar12 = __aullshr(bVar4,0);
      _Var1 = lVar10 + lVar11 + uVar12;
      if ((param_4) || ((uVar2 & (1 << bVar4) - 1U) != 0)) {
        bVar9 = false;
      }
      for (; iVar8 != 0; iVar8 = iVar8 + -1) {
        param_1 = param_1 + 4;
        bVar9 = (bool)(bVar9 & *(int *)param_1 == 0);
      }
      goto LAB_00460da1;
    }
    iVar6 = iVar8 * 0x20 + iVar6;
    uVar5 = *(undefined4 *)(param_1 + (param_2 >> 5) * 4);
    uVar7 = *(undefined4 *)(param_1 + iVar8 * 4 + 4);
    bVar9 = !param_4;
    for (; iVar8 != 0; iVar8 = iVar8 + -1) {
      param_1 = param_1 + 4;
      bVar9 = (bool)(bVar9 & *(int *)param_1 == 0);
    }
  }
  _Var1 = CONCAT44(uVar5,uVar7);
LAB_00460da1:
  SVar3 = assemble_floating_point_value(_Var1,iVar6,param_3,bVar9,param_5);
  return SVar3;
}


