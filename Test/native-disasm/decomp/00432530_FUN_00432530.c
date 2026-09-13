// FUN_00432530 @ 00432530 size=112 callers=1

void FUN_00432530(void)

{
  int *piVar1;
  int *_Memory;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 uStack_8;
  
  uStack_8 = 0xffffffff;
  puStack_c = &LAB_004790f0;
  local_10 = ExceptionList;
  _Memory = (int *)*DAT_004a24b4;
  ExceptionList = &local_10;
  *DAT_004a24b4 = (int)DAT_004a24b4;
  DAT_004a24b4[1] = (int)DAT_004a24b4;
  DAT_004a24b8 = 0;
  if (_Memory != DAT_004a24b4) {
    do {
      piVar1 = (int *)*_Memory;
      FID_conflict__free(_Memory);
      _Memory = piVar1;
    } while (piVar1 != DAT_004a24b4);
  }
  FUN_00435e50(&DAT_004a24b0,8);
  ExceptionList = local_10;
  return;
}


