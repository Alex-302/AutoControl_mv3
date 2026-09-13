// FUN_00418f00 @ 00418f00 size=192 callers=1

void FUN_00418f00(char param_1,char param_2)

{
  undefined **local_44;
  ulonglong local_40;
  undefined4 local_38;
  undefined ***local_20;
  uint local_1c;
  undefined4 uStack_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0047b2e8;
  local_10 = ExceptionList;
  if ((DAT_004a25dc == '\0') && ((DAT_004a25d4 != 0 || (param_2 != '\0')))) {
    DAT_004a25dc = 'F';
    if (param_1 != '\0') {
      DAT_004a25dc = 'S';
    }
    ExceptionList = &local_10;
    FUN_00418cc0();
    local_1c = DAT_004a25d4;
    uStack_18 = 0;
    local_40 = (ulonglong)DAT_004a25d4;
    local_38 = 0x1ff0000;
    local_20 = &local_44;
    local_44 = &PTR_LAB_0048e7f0;
    local_8 = 0;
    FUN_0040fca0(0x28,(int *)local_20);
    if (local_20 != (undefined ***)0x0) {
      (*(code *)(*local_20)[4])(local_20 != &local_44);
    }
  }
  ExceptionList = local_10;
  return;
}


