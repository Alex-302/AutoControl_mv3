// FUN_00418180 @ 00418180 size=143 callers=1

/* WARNING: Restarted to delay deadcode elimination for space: ram */

void ** FUN_00418180(void **param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 uStack_8;
  
  uStack_8 = 0xffffffff;
  puStack_c = &LAB_004791b6;
  local_10 = ExceptionList;
  if (param_1 != &DAT_004a26d8) {
    ExceptionList = &local_10;
    if (0xf < DAT_004a26ec) {
      ExceptionList = &local_10;
      FUN_00402430(DAT_004a26d8,DAT_004a26ec + 1,1);
    }
    DAT_004a26ec = 0xf;
    DAT_004a26e8 = 0;
    DAT_004a26d8 = (void *)((uint)DAT_004a26d8 & 0xffffff00);
    FUN_0043b1c0(&DAT_004a26d8,(uint *)param_1);
    DAT_004a26f0 = param_1[6];
  }
  ExceptionList = local_10;
  return &DAT_004a26d8;
}


