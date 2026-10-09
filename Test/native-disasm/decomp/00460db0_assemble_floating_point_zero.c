// assemble_floating_point_zero @ 00460db0 size=52 callers=2

/* Library Function - Single Match
    void __cdecl __crt_strtox::assemble_floating_point_zero(bool,class
   __crt_strtox::floating_point_value const &)
   
   Library: Visual Studio 2015 Release */

void __cdecl __crt_strtox::assemble_floating_point_zero(bool param_1,floating_point_value *param_2)

{
  double *pdVar1;
  int *piVar2;
  
  if (param_2[4] != (floating_point_value)0x0) {
    pdVar1 = (double *)FUN_00460852((undefined4 *)param_2);
    assemble_floating_point_zero<double>(param_1,pdVar1);
    return;
  }
  piVar2 = (int *)FUN_00460877((undefined4 *)param_2);
  *piVar2 = (uint)param_1 << 0x1f;
  return;
}


