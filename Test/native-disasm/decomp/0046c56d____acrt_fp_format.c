// ___acrt_fp_format @ 0046c56d size=330 callers=1

/* Library Function - Single Match
    ___acrt_fp_format
   
   Library: Visual Studio 2015 Release */

int __cdecl
___acrt_fp_format(double *param_1,char *param_2,uint param_3,char *param_4,uint param_5,int param_6,
                 int param_7,uint param_8,undefined4 param_9,__crt_locale_pointers *param_10)

{
  bool bVar1;
  int *piVar2;
  __acrt_fp_class _Var3;
  int iVar4;
  uint uVar5;
  bool local_8;
  
  if (param_2 == (char *)0x0) {
    piVar2 = __errno();
    iVar4 = 0x16;
    *piVar2 = 0x16;
    FUN_00465fa2();
  }
  else if (((param_3 == 0) || (param_4 == (char *)0x0)) || (param_5 == 0)) {
    piVar2 = __errno();
    iVar4 = 0x16;
    *piVar2 = 0x16;
    FUN_00465fa2();
  }
  else {
    if (((param_6 == 0x41) || (param_6 == 0x45)) ||
       ((param_6 == 0x46 || (local_8 = false, param_6 == 0x47)))) {
      local_8 = true;
    }
    if (((param_8 & 8) == 0) && (_Var3 = __acrt_fp_classify(param_1), _Var3 != 0)) {
      bVar1 = __acrt_fp_is_negative(param_1);
      iVar4 = FUN_0046c441(_Var3,bVar1,param_2,param_3,local_8);
    }
    else {
      if ((param_8 & 0x10) == 0) {
        uVar5 = 2;
      }
      else {
        uVar5 = 3;
      }
      if (param_6 < 0x62) {
        if ((param_6 == 0x61) || (param_6 == 0x41)) {
          iVar4 = fp_format_a(param_1,param_2,param_3,param_4,param_5,param_7,local_8,uVar5,param_10
                             );
          return iVar4;
        }
        iVar4 = param_6 + -0x45;
      }
      else {
        iVar4 = param_6 + -0x65;
      }
      if (iVar4 == 0) {
        iVar4 = fp_format_e(param_1,param_2,param_3,param_4,param_5,param_7,local_8,uVar5,param_10);
      }
      else if (iVar4 == 1) {
        iVar4 = fp_format_f(param_1,param_2,param_3,param_4,param_5,param_7,param_10);
      }
      else {
        iVar4 = fp_format_g(param_1,param_2,param_3,param_4,param_5,param_7,local_8,uVar5,param_10);
      }
    }
  }
  return iVar4;
}


