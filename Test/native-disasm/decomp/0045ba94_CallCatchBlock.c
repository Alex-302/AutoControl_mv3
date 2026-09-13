// CallCatchBlock @ 0045ba94 size=165 callers=1

/* WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4 */
/* WARNING: Function: __SEH_epilog4 replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    void * __cdecl CallCatchBlock(struct EHExceptionRecord *,struct EHRegistrationNode *,struct
   _CONTEXT *,struct _s_FuncInfo const *,void *,int,unsigned long)
   
   Library: Visual Studio 2015 Release */

void * __cdecl
CallCatchBlock(EHExceptionRecord *param_1,EHRegistrationNode *param_2,_CONTEXT *param_3,
              _s_FuncInfo *param_4,void *param_5,int param_6,ulong param_7)

{
  int iVar1;
  undefined4 local_4c [2];
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 *local_34;
  undefined4 local_30;
  void *local_20;
  undefined4 uStack_c;
  undefined *local_8;
  
  local_8 = &DAT_00499938;
  uStack_c = 0x45baa0;
  local_20 = param_5;
  local_40 = 0;
  local_30 = *(undefined4 *)(param_2 + -4);
  local_34 = __CreateFrameInfo(local_4c,*(undefined4 *)(param_1 + 0x18));
  iVar1 = ___vcrt_getptd();
  local_38 = *(undefined4 *)(iVar1 + 0x10);
  iVar1 = ___vcrt_getptd();
  local_3c = *(undefined4 *)(iVar1 + 0x14);
  iVar1 = ___vcrt_getptd();
  *(EHExceptionRecord **)(iVar1 + 0x10) = param_1;
  iVar1 = ___vcrt_getptd();
  *(_CONTEXT **)(iVar1 + 0x14) = param_3;
  local_44 = 1;
  local_8 = (undefined *)0x1;
  local_20 = _CallCatchBlock2(param_2,param_4,param_5,param_6,param_7);
  local_8 = (undefined *)0xfffffffe;
  local_44 = 0;
  FUN_0045bbcf();
  return param_2;
}


