// FUN_00402370 @ 00402370 size=50 callers=1

int __fastcall FUN_00402370(char *param_1,uint param_2,char *param_3,char *param_4)

{
  uint *puVar1;
  int iVar2;
  __crt_locale_pointers *p_Var3;
  
  p_Var3 = (__crt_locale_pointers *)0x0;
  puVar1 = (uint *)FUN_004022a0();
  iVar2 = ___stdio_common_vsprintf(*puVar1 | 2,puVar1[1],param_1,param_2,param_3,p_Var3,param_4);
  if (iVar2 < 0) {
    iVar2 = -1;
  }
  return iVar2;
}


