// FUN_00408600 @ 00408600 size=348 callers=17

void __fastcall FUN_00408600(int param_1,undefined1 *param_2)

{
  void *this;
  FILE *pFVar1;
  undefined4 ***_Str;
  char local_5c [8];
  undefined8 local_54;
  undefined1 local_4c [16];
  undefined4 **local_3c [4];
  size_t local_2c;
  uint local_28;
  char local_24 [16];
  size_t local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004798bb;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if (*(int *)(*(int *)ThreadLocalStoragePointer + 8) < DAT_004a337c) {
    ExceptionList = &local_10;
    FUN_0045a219(&DAT_004a337c);
    if (DAT_004a337c == -1) {
      InitializeCriticalSection((LPCRITICAL_SECTION)&DAT_004a2f30);
      DAT_004a2fc0 = 0;
      FUN_0045a1da(&DAT_004a337c);
    }
  }
  local_5c[0] = '\0';
  local_54 = 0;
  FUN_00450f50(local_5c,param_1);
  local_8 = 0;
  FUN_00434940(local_4c,param_2);
  local_8 = 1;
  this = FUN_00434b50(local_24,local_5c,(char *)local_3c,'\x01','\x02');
  local_8._0_1_ = 2;
  FUN_00434740(this,(undefined1 *)local_3c);
  FUN_00434820(local_24);
  local_8 = CONCAT31(local_8._1_3_,5);
  _eh_vector_destructor_iterator_(local_5c,0x10,2,FUN_00434820);
  local_14 = local_2c;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_004a2f30);
  pFVar1 = (FILE *)___acrt_iob_func(1);
  _fwrite(&local_14,1,4,pFVar1);
  _Str = local_3c;
  if (0xf < local_28) {
    _Str = (undefined4 ***)local_3c[0];
  }
  pFVar1 = (FILE *)___acrt_iob_func(1);
  _fwrite(_Str,1,local_2c,pFVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_004a2f30);
  if (0xf < local_28) {
    FUN_00402430(local_3c[0],local_28 + 1,1);
  }
  ExceptionList = local_10;
  return;
}


