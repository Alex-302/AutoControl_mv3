// assemble_floating_point_ind<double> @ 0045fdf0 size=47 callers=1

/* Library Function - Single Match
    void __cdecl __crt_strtox::assemble_floating_point_ind<double>(double &)
   
   Library: Visual Studio 2015 Release */

void __cdecl __crt_strtox::assemble_floating_point_ind<double>(double *param_1)

{
  *(uint *)((int)param_1 + 4) = *(uint *)((int)param_1 + 4) | 0x80000000;
  *(uint *)((int)param_1 + 4) = *(uint *)((int)param_1 + 4) | 0x7ff00000;
  *(undefined4 *)param_1 = *(undefined4 *)param_1;
  *(undefined4 *)param_1 = 0;
  *(uint *)((int)param_1 + 4) = *(uint *)((int)param_1 + 4) & 0xfff80000 | 0x80000;
  return;
}


