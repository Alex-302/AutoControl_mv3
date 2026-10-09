// assemble_floating_point_infinity<double> @ 0045fe1f size=63 callers=3

/* Library Function - Single Match
    void __cdecl __crt_strtox::assemble_floating_point_infinity<double>(bool,double &)
   
   Library: Visual Studio 2015 Release */

void __cdecl __crt_strtox::assemble_floating_point_infinity<double>(bool param_1,double *param_2)

{
  *(uint *)((int)param_2 + 4) = (uint)param_1 << 0x1f | *(uint *)((int)param_2 + 4) & 0x7fffffff;
  *(uint *)((int)param_2 + 4) = *(uint *)((int)param_2 + 4) | 0x7ff00000;
  *(undefined4 *)param_2 = *(undefined4 *)param_2;
  *(undefined4 *)param_2 = 0;
  *(uint *)((int)param_2 + 4) = *(uint *)((int)param_2 + 4) & 0xfff00000;
  return;
}


