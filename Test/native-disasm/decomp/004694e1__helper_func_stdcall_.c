// <helper_func_stdcall> @ 004694e1 size=70 callers=1

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    private: static int __stdcall
   <lambda_5a01b672d24c8480ee9d6bdb50dd3881>::<helper_func_stdcall>(wchar_t *)
   
   Library: Visual Studio 2015 Release */

int <lambda_5a01b672d24c8480ee9d6bdb50dd3881>::<helper_func_stdcall>(wchar_t *param_1)

{
  int iVar1;
  byte bVar2;
  uint uVar3;
  
  uVar3 = DAT_0049d070 ^ _DAT_0049f8f0;
  bVar2 = (byte)DAT_0049d070 & 0x1f;
  (*(code *)PTR_guard_check_icall_004805b0)(param_1,0,0);
  iVar1 = (*(code *)(uVar3 >> bVar2 | uVar3 << 0x20 - bVar2))();
  return iVar1;
}


