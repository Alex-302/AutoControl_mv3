// fp_format_f @ 0046c215 size=141 callers=1

/* Library Function - Single Match
    int __cdecl fp_format_f(double const * const,char * const,unsigned int,char * const,unsigned
   int,int,struct __crt_locale_pointers * const)
   
   Library: Visual Studio 2015 Release */

int __cdecl
fp_format_f(double *param_1,char *param_2,uint param_3,char *param_4,uint param_5,int param_6,
           __crt_locale_pointers *param_7)

{
  int iVar1;
  uint uVar2;
  int local_10;
  int local_c;
  undefined4 uStack_8;
  
  local_10 = 0;
  local_c = 0;
  uStack_8 = 0;
  FUN_0047402a(*(int *)param_1,*(uint *)((int)param_1 + 4),param_6,&local_10,param_4,param_5);
  uVar2 = 0xffffffff;
  if (param_3 != 0xffffffff) {
    uVar2 = param_3 - (local_10 == 0x2d);
  }
  iVar1 = ___acrt_fp_strflt_to_string
                    ((uint *)(param_2 + (local_10 == 0x2d)),uVar2,local_c + param_6,(int)&local_10);
  if (iVar1 == 0) {
    iVar1 = fp_format_f_internal(param_2,param_3,param_6,(_strflt *)&local_10,false,param_7);
  }
  else {
    *param_2 = '\0';
  }
  return iVar1;
}


