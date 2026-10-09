// fp_format_e @ 0046c02f size=155 callers=2

/* Library Function - Single Match
    int __cdecl fp_format_e(double const * const,char * const,unsigned int,char * const,unsigned
   int,int,bool,unsigned int,struct __crt_locale_pointers * const)
   
   Library: Visual Studio 2015 Release */

int __cdecl
fp_format_e(double *param_1,char *param_2,uint param_3,char *param_4,uint param_5,int param_6,
           bool param_7,uint param_8,__crt_locale_pointers *param_9)

{
  int iVar1;
  uint uVar2;
  int local_10 [3];
  
  FUN_0047402a(*(int *)param_1,*(uint *)((int)param_1 + 4),param_6 + 1,local_10,param_4,param_5);
  uVar2 = 0xffffffff;
  if (param_3 != 0xffffffff) {
    uVar2 = (param_3 - (local_10[0] == 0x2d)) - (uint)(0 < param_6);
  }
  iVar1 = ___acrt_fp_strflt_to_string
                    ((uint *)(param_2 + (uint)(0 < param_6) + (uint)(local_10[0] == 0x2d)),uVar2,
                     param_6 + 1,(int)local_10);
  if (iVar1 == 0) {
    iVar1 = FUN_0046c0ca(param_2,param_3,param_6,param_7,param_8,local_10,'\0',param_9);
  }
  else {
    *param_2 = '\0';
  }
  return iVar1;
}


