// fp_format_g @ 0046c379 size=200 callers=1

/* Library Function - Single Match
    int __cdecl fp_format_g(double const * const,char * const,unsigned int,char * const,unsigned
   int,int,bool,unsigned int,struct __crt_locale_pointers * const)
   
   Library: Visual Studio 2015 Release */

int __cdecl
fp_format_g(double *param_1,char *param_2,uint param_3,char *param_4,uint param_5,int param_6,
           bool param_7,uint param_8,__crt_locale_pointers *param_9)

{
  uint *puVar1;
  uint uVar2;
  int iVar3;
  uint *puVar4;
  bool bVar5;
  int local_14;
  int local_10;
  undefined4 uStack_c;
  int local_8;
  
  local_14 = 0;
  local_10 = 0;
  uStack_c = 0;
  FUN_0047402a(*(int *)param_1,*(uint *)((int)param_1 + 4),param_6,&local_14,param_4,param_5);
  bVar5 = local_14 == 0x2d;
  local_8 = local_10 + -1;
  uVar2 = 0xffffffff;
  if (param_3 != 0xffffffff) {
    uVar2 = param_3 - bVar5;
  }
  iVar3 = ___acrt_fp_strflt_to_string((uint *)(param_2 + bVar5),uVar2,param_6,(int)&local_14);
  if (iVar3 == 0) {
    iVar3 = local_10 + -1;
    if ((iVar3 < -4) || (param_6 <= iVar3)) {
      iVar3 = FUN_0046c0ca(param_2,param_3,param_6,param_7,param_8,&local_14,'\x01',param_9);
    }
    else {
      puVar1 = (uint *)(param_2 + bVar5);
      if (local_8 < iVar3) {
        do {
          puVar4 = puVar1;
          puVar1 = (uint *)((int)puVar4 + 1);
        } while ((char)*puVar4 != '\0');
        *(undefined1 *)((int)puVar4 + -1) = 0;
      }
      iVar3 = fp_format_f_internal(param_2,param_3,param_6,(_strflt *)&local_14,true,param_9);
    }
  }
  else {
    *param_2 = '\0';
  }
  return iVar3;
}


