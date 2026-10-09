// convert_hexadecimal_string_to_floating_type_common @ 00462ba7 size=172 callers=1

/* WARNING: Removing unreachable block (ram,0x00462bf2) */
/* Library Function - Single Match
    enum SLD_STATUS __cdecl __crt_strtox::convert_hexadecimal_string_to_floating_type_common(struct
   __crt_strtox::floating_point_string const &,class __crt_strtox::floating_point_value const &)
   
   Library: Visual Studio 2015 Release */

SLD_STATUS __cdecl
__crt_strtox::convert_hexadecimal_string_to_floating_type_common
          (floating_point_string *param_1,floating_point_value *param_2)

{
  floating_point_string fVar1;
  int iVar2;
  uint uVar3;
  bool bVar4;
  int iVar5;
  SLD_STATUS SVar6;
  int iVar7;
  floating_point_string *pfVar8;
  uint uVar9;
  uint uVar10;
  __uint64 _Var11;
  
  uVar9 = 0;
  pfVar8 = param_1 + 8;
  iVar5 = *(int *)param_1 + ((param_2[4] == (floating_point_value)0x0) - 1 & 0x1d) + 0x17;
  iVar2 = *(int *)(param_1 + 4);
  for (iVar7 = 0;
      (pfVar8 != param_1 + iVar2 + 8 &&
      (_Var11 = floating_point_value::normal_mantissa_mask(param_2), CONCAT44(iVar7,uVar9) <= _Var11
      )); iVar7 = (iVar7 << 4 | uVar3) + (uint)CARRY4(uVar10,(uint)(byte)fVar1)) {
    fVar1 = *pfVar8;
    uVar3 = uVar9 >> 0x1c;
    uVar10 = uVar9 * 0x10;
    uVar9 = uVar10 + (byte)fVar1;
    iVar5 = iVar5 + -4;
    pfVar8 = pfVar8 + 1;
  }
  do {
    bVar4 = true;
    while( true ) {
      if ((pfVar8 == param_1 + iVar2 + 8) || (bVar4 == false)) {
        SVar6 = assemble_floating_point_value
                          (CONCAT44(iVar7,uVar9),iVar5,(bool)param_1[0x308],bVar4,param_2);
        return SVar6;
      }
      fVar1 = *pfVar8;
      pfVar8 = pfVar8 + 1;
      if (fVar1 == (floating_point_string)0x0) break;
      bVar4 = false;
    }
  } while( true );
}


