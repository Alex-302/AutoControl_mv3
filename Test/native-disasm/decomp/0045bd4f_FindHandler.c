// FindHandler @ 0045bd4f size=871 callers=1

/* Library Function - Single Match
    void __cdecl FindHandler(struct EHExceptionRecord *,struct EHRegistrationNode *,struct _CONTEXT
   *,void *,struct _s_FuncInfo const *,unsigned char,int,struct EHRegistrationNode *)
   
   Library: Visual Studio 2015 Release */

void __cdecl
FindHandler(EHExceptionRecord *param_1,EHRegistrationNode *param_2,_CONTEXT *param_3,void *param_4,
           _s_FuncInfo *param_5,uchar param_6,int param_7,EHRegistrationNode *param_8)

{
  int *piVar1;
  int iVar2;
  uchar uVar3;
  int iVar4;
  undefined4 uVar5;
  bad_exception local_48 [12];
  _s_TryBlockMapEntry *local_3c;
  int local_38;
  int *local_34;
  uint local_30;
  uint local_2c;
  int local_28;
  _s_ESTypeList *local_24;
  int local_20;
  uint local_1c;
  _s_HandlerType *local_18;
  int *local_14;
  _CONTEXT *local_10;
  int local_c;
  char local_5;
  
  local_2c = local_2c & 0xffffff00;
  local_5 = '\0';
  if (param_5->maxState < 0x81) {
    local_c = (int)(char)param_2[8];
  }
  else {
    local_c = *(int *)(param_2 + 8);
  }
  if ((local_c < -1) || (param_5->maxState <= local_c)) goto LAB_0045c072;
  if (*(int *)param_1 == -0x1f928c9d) {
    if ((*(int *)(param_1 + 0x10) == 3) &&
       ((((*(int *)(param_1 + 0x14) == 0x19930520 || (*(int *)(param_1 + 0x14) == 0x19930521)) ||
         (*(int *)(param_1 + 0x14) == 0x19930522)) && (*(int *)(param_1 + 0x1c) == 0)))) {
      iVar4 = ___vcrt_getptd();
      if (*(int *)(iVar4 + 0x10) == 0) {
        return;
      }
      iVar4 = ___vcrt_getptd();
      param_1 = *(EHExceptionRecord **)(iVar4 + 0x10);
      iVar4 = ___vcrt_getptd();
      local_2c = CONCAT31(local_2c._1_3_,1);
      local_10 = *(_CONTEXT **)(iVar4 + 0x14);
      if ((param_1 == (EHExceptionRecord *)0x0) ||
         ((((*(int *)param_1 == -0x1f928c9d && (*(int *)(param_1 + 0x10) == 3)) &&
           ((*(int *)(param_1 + 0x14) == 0x19930520 ||
            ((*(int *)(param_1 + 0x14) == 0x19930521 || (*(int *)(param_1 + 0x14) == 0x19930522)))))
           ) && (*(int *)(param_1 + 0x1c) == 0)))) goto LAB_0045c072;
      iVar4 = ___vcrt_getptd();
      if (*(int *)(iVar4 + 0x1c) != 0) {
        iVar4 = ___vcrt_getptd();
        local_24 = *(_s_ESTypeList **)(iVar4 + 0x1c);
        iVar4 = ___vcrt_getptd();
        *(undefined4 *)(iVar4 + 0x1c) = 0;
        uVar5 = FUN_0045c1d2((int)param_1,&local_24->nCount);
        if ((char)uVar5 == '\0') {
          uVar3 = Is_bad_exception_allowed(local_24);
          if (uVar3 != '\0') {
            ___DestructExceptionObject((int *)param_1);
            std::bad_exception::bad_exception(local_48);
                    /* WARNING: Subroutine does not return */
            __CxxThrowException_8((int *)local_48,&DAT_00499a14);
          }
          goto LAB_0045c072;
        }
      }
    }
    else {
      local_10 = param_3;
    }
    param_3 = local_10;
    if (((*(int *)param_1 != -0x1f928c9d) || (*(int *)(param_1 + 0x10) != 3)) ||
       ((*(int *)(param_1 + 0x14) != 0x19930520 &&
        ((*(int *)(param_1 + 0x14) != 0x19930521 && (*(int *)(param_1 + 0x14) != 0x19930522))))))
    goto LAB_0045c03e;
    if ((param_5->nTryBlocks != 0) &&
       (iVar4 = FUN_0045cf21((int)param_5,param_7,local_c,&local_1c,&local_30), local_1c < local_30)
       ) {
      local_24 = (_s_ESTypeList *)(iVar4 + 0x10);
      iVar4 = local_c;
      do {
        local_3c = (_s_TryBlockMapEntry *)((int)local_24 + -0x10);
        if ((*(int *)((int)local_24 + -0x10) <= iVar4) &&
           (iVar4 <= (int)*(undefined4 *)((int)local_24 + -0xc))) {
          local_18 = *(_s_HandlerType **)local_24;
          local_20 = *(undefined4 *)((int)local_24 + -4);
          if (0 < local_20) {
            local_38 = **(int **)(*(int *)(param_1 + 0x1c) + 0xc);
            local_34 = *(int **)(*(int *)(param_1 + 0x1c) + 0xc) + 1;
            piVar1 = local_34;
            iVar2 = local_38;
            do {
              while (local_28 = iVar2, local_14 = piVar1, 0 < local_28) {
                iVar4 = ___TypeMatch((byte *)local_18,(byte *)*local_14,*(byte **)(param_1 + 0x1c));
                if (iVar4 != 0) {
                  local_5 = '\x01';
                  CatchIt(param_1,param_2,local_10,param_4,param_5,local_18,
                          (_s_CatchableType *)*local_14,local_3c,param_7,param_8,(uchar)local_2c);
                  iVar4 = local_c;
                  goto LAB_0045bfb2;
                }
                piVar1 = local_14 + 1;
                iVar2 = local_28 + -1;
              }
              local_20 = local_20 + -1;
              local_18 = local_18 + 1;
              iVar4 = local_c;
              piVar1 = local_34;
              iVar2 = local_38;
            } while (0 < local_20);
          }
        }
LAB_0045bfb2:
        local_1c = local_1c + 1;
        local_24 = (_s_ESTypeList *)((int)local_24 + 0x14);
      } while (local_1c < local_30);
    }
    if (param_6 != '\0') {
      ___DestructExceptionObject((int *)param_1);
    }
    if (((local_5 == '\0') && (0x19930520 < (param_5->magicNumber_and_bbtFlags & 0x1fffffff))) &&
       ((param_5->pESTypeList != (ESTypeList *)0x0 ||
        (((param_5->EHFlags & 4) != 0 && (param_7 == 0)))))) {
      if ((param_5->EHFlags & 4) != 0) goto LAB_0045c072;
      uVar5 = FUN_0045c1d2((int)param_1,&param_5->pESTypeList->nCount);
      if ((char)uVar5 == '\0') {
        ___vcrt_getptd();
        ___vcrt_getptd();
        iVar4 = ___vcrt_getptd();
        *(EHExceptionRecord **)(iVar4 + 0x10) = param_1;
        iVar4 = ___vcrt_getptd();
        *(_CONTEXT **)(iVar4 + 0x14) = local_10;
        if (param_8 == (EHRegistrationNode *)0x0) {
          param_8 = param_2;
        }
        _UnwindNestedFrames(param_8,param_1);
        ___FrameUnwindToState((int)param_2,param_4,(int)param_5,-1);
                    /* WARNING: Subroutine does not return */
        FUN_0045bc50();
      }
    }
  }
  else {
LAB_0045c03e:
    if (param_5->nTryBlocks != 0) {
      if (param_6 != '\0') goto LAB_0045c072;
      FUN_0045c0b7(param_1,param_2,param_3,param_4,param_5,local_c,param_7,param_8);
    }
  }
  iVar4 = ___vcrt_getptd();
  if (*(int *)(iVar4 + 0x1c) == 0) {
    return;
  }
LAB_0045c072:
                    /* WARNING: Subroutine does not return */
  FUN_00464131();
}


