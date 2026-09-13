// FUN_0045c0b7 @ 0045c0b7 size=282 callers=1

void __cdecl
FUN_0045c0b7(EHExceptionRecord *param_1,EHRegistrationNode *param_2,_CONTEXT *param_3,void *param_4,
            _s_FuncInfo *param_5,int param_6,int param_7,EHRegistrationNode *param_8)

{
  int iVar1;
  PVOID pvVar2;
  _s_HandlerType *p_Var3;
  uint uVar4;
  int *piVar5;
  uint local_c;
  uint local_8;
  
  if (*(int *)param_1 != -0x7ffffffd) {
    iVar1 = ___vcrt_getptd();
    if (*(int *)(iVar1 + 8) != 0) {
      pvVar2 = EncodePointer((PVOID)0x0);
      iVar1 = ___vcrt_getptd();
      if ((((*(PVOID *)(iVar1 + 8) != pvVar2) && (*(int *)param_1 != -0x1fbcb0b3)) &&
          (*(int *)param_1 != -0x1fbcbcae)) &&
         (iVar1 = _CallSETranslator(param_1,param_2,param_3,param_4,param_5,param_7,param_8),
         iVar1 != 0)) {
        return;
      }
    }
    if (param_5->nTryBlocks == 0) {
                    /* WARNING: Subroutine does not return */
      FUN_00464131();
    }
    iVar1 = FUN_0045cf21((int)param_5,param_7,param_6,&local_c,&local_8);
    if (local_c < local_8) {
      piVar5 = (int *)(iVar1 + 0xc);
      uVar4 = local_8;
      do {
        if ((((piVar5[-3] <= param_6) && (param_6 <= piVar5[-2])) &&
            ((iVar1 = *piVar5 * 0x10, *(int *)(piVar5[1] + -0xc + iVar1) == 0 ||
             (uVar4 = local_8, *(char *)(*(int *)(piVar5[1] + -0xc + iVar1) + 8) == '\0')))) &&
           (p_Var3 = (_s_HandlerType *)(iVar1 + piVar5[1] + -0x10), (p_Var3->adjectives & 0x40) == 0
           )) {
          CatchIt(param_1,param_2,param_3,param_4,param_5,p_Var3,(_s_CatchableType *)0x0,
                  (_s_TryBlockMapEntry *)(piVar5 + -3),param_7,param_8,'\x01');
          uVar4 = local_8;
        }
        local_c = local_c + 1;
        piVar5 = piVar5 + 5;
      } while (local_c < uVar4);
    }
  }
  return;
}


