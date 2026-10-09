// FUN_004026a0 @ 004026a0 size=196 callers=2

void __fastcall FUN_004026a0(_Locinfo *param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 uStack_8;
  
  uStack_8 = 0xffffffff;
  puStack_c = &LAB_004790f0;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  std::_Locinfo::_Locinfo_dtor(param_1);
  if (*(void **)(param_1 + 0x2c) != (void *)0x0) {
    FID_conflict__free(*(void **)(param_1 + 0x2c));
  }
  *(undefined4 *)(param_1 + 0x2c) = 0;
  if (*(void **)(param_1 + 0x24) != (void *)0x0) {
    FID_conflict__free(*(void **)(param_1 + 0x24));
  }
  *(undefined4 *)(param_1 + 0x24) = 0;
  if (*(void **)(param_1 + 0x1c) != (void *)0x0) {
    FID_conflict__free(*(void **)(param_1 + 0x1c));
  }
  *(undefined4 *)(param_1 + 0x1c) = 0;
  if (*(void **)(param_1 + 0x14) != (void *)0x0) {
    FID_conflict__free(*(void **)(param_1 + 0x14));
  }
  *(undefined4 *)(param_1 + 0x14) = 0;
  if (*(void **)(param_1 + 0xc) != (void *)0x0) {
    FID_conflict__free(*(void **)(param_1 + 0xc));
  }
  *(undefined4 *)(param_1 + 0xc) = 0;
  if (*(void **)(param_1 + 4) != (void *)0x0) {
    FID_conflict__free(*(void **)(param_1 + 4));
  }
  *(undefined4 *)(param_1 + 4) = 0;
  FUN_0045884d((int *)param_1);
  ExceptionList = local_10;
  return;
}


