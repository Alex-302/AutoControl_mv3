// _CallSETranslator @ 0045ce44 size=221 callers=2

/* Library Function - Single Match
    int __cdecl _CallSETranslator(struct EHExceptionRecord *,struct EHRegistrationNode *,void *,void
   *,struct _s_FuncInfo const *,int,struct EHRegistrationNode *)
   
   Library: Visual Studio 2015 Release */

int __cdecl
_CallSETranslator(EHExceptionRecord *param_1,EHRegistrationNode *param_2,void *param_3,void *param_4
                 ,_s_FuncInfo *param_5,int param_6,EHRegistrationNode *param_7)

{
  int iVar1;
  undefined4 *local_3c;
  code *local_38;
  uint local_34;
  _s_FuncInfo *local_30;
  EHRegistrationNode *local_2c;
  int local_28;
  EHRegistrationNode *local_24;
  undefined1 *local_20;
  undefined1 *local_1c;
  int local_18;
  EHExceptionRecord *local_14;
  void *local_10;
  int local_c;
  code *local_8;
  
  local_1c = &stack0xfffffffc;
  local_20 = &stack0xffffffc0;
  if (param_1 == (EHExceptionRecord *)0x123) {
    *(undefined4 *)param_2 = 0x45cef3;
    local_c = 1;
  }
  else {
    local_38 = __TranslatorGuardHandler;
    local_34 = DAT_0049d070 ^ (uint)&local_3c;
    local_30 = param_5;
    local_2c = param_2;
    local_28 = param_6;
    local_24 = param_7;
    local_18 = 0;
    local_3c = ExceptionList;
    ExceptionList = &local_3c;
    local_c = 1;
    local_14 = param_1;
    local_10 = param_3;
    iVar1 = ___vcrt_getptd();
    local_8 = *(code **)(iVar1 + 8);
    (*(code *)PTR_guard_check_icall_004805b0)();
    (*local_8)(*(undefined4 *)param_1,&local_14);
    local_c = 0;
    if (local_18 != 0) {
      *local_3c = *(undefined4 *)ExceptionList;
    }
    ExceptionList = local_3c;
  }
  return local_c;
}


