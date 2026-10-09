// assemble_floating_point_snan<double> @ 0045fe9d size=68 callers=1

/* Library Function - Single Match
    void __cdecl __crt_strtox::assemble_floating_point_snan<double>(bool,double &)
   
   Library: Visual Studio 2015 Release */

void __cdecl __crt_strtox::assemble_floating_point_snan<double>(bool param_1,double *param_2)

{
  *(uint *)((int)param_2 + 4) = (uint)param_1 << 0x1f | *(uint *)((int)param_2 + 4) & 0x7fffffff;
  *(uint *)((int)param_2 + 4) = *(uint *)((int)param_2 + 4) | 0x7ff00000;
  *(uint *)((int)param_2 + 4) = *(uint *)((int)param_2 + 4) & 0xfff00000;
  *(undefined4 *)param_2 = 1;
  return;
}


