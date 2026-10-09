// assemble_floating_point_value_t<double> @ 0045ff11 size=95 callers=1

/* Library Function - Single Match
    enum SLD_STATUS __cdecl __crt_strtox::assemble_floating_point_value_t<double>(bool,int,unsigned
   __int64,double &)
   
   Library: Visual Studio 2015 Release */

SLD_STATUS __cdecl
__crt_strtox::assemble_floating_point_value_t<double>
          (bool param_1,int param_2,__uint64 param_3,double *param_4)

{
  uint uVar1;
  uint uVar2;
  
  *(undefined4 *)param_4 = *(undefined4 *)param_4;
  *(uint *)((int)param_4 + 4) = (uint)param_1 << 0x1f | *(uint *)((int)param_4 + 4) & 0x7fffffff;
  uVar1 = *(uint *)param_4;
  uVar2 = (param_2 + 0x3ffU & 0x7ff) << 0x14 | *(uint *)((int)param_4 + 4) & 0x800fffff;
  *(uint *)((int)param_4 + 4) = uVar2;
  *(uint *)((int)param_4 + 4) = *(uint *)((int)param_4 + 4) ^ (uVar2 ^ param_3._4_4_) & 0xfffff;
  *(uint *)param_4 = uVar1;
  *(uint *)param_4 = *(uint *)param_4 ^ uVar1 ^ (uint)param_3;
  return 0;
}


