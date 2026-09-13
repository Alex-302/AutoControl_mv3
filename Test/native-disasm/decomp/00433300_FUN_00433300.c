// FUN_00433300 @ 00433300 size=127 callers=1

undefined4 * FUN_00433300(undefined4 *param_1)

{
  if ((void **)param_1 != &DAT_004a2514) {
    if (DAT_004a2514 != (void *)0x0) {
      FUN_00402430(DAT_004a2514,DAT_004a251c - (int)DAT_004a2514 >> 2,4);
    }
    DAT_004a2514 = (void *)*param_1;
    DAT_004a2518 = param_1[1];
    DAT_004a251c = param_1[2];
    *param_1 = 0;
    param_1[1] = 0;
    param_1[2] = 0;
  }
  return &DAT_004a2514;
}


