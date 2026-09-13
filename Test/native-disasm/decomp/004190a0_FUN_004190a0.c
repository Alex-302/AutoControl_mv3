// FUN_004190a0 @ 004190a0 size=113 callers=4

undefined2 __fastcall FUN_004190a0(byte *param_1)

{
  int local_4;
  
  param_1[0x36] = 1;
  param_1[0x37] = 0x53;
  FUN_004195f0(param_1,'\0',0);
  if (*(int *)(param_1 + 0x10) == 0) {
    if (*(int *)(param_1 + 0x28) != 0) {
      FUN_0040fb40((UINT_PTR *)(*(int *)(param_1 + 0x28) + 0x10),'\x01');
    }
    param_1[0x28] = 0;
    param_1[0x29] = 0;
    param_1[0x2a] = 0;
    param_1[0x2b] = 0;
  }
  else {
    FUN_00436020(&DAT_004a2a10,&local_4,param_1);
    param_1[0x10] = 0;
    param_1[0x11] = 0;
    param_1[0x12] = 0;
    param_1[0x13] = 0;
    if (0xf < *(uint *)(param_1 + 0x14)) {
      param_1 = *(byte **)param_1;
    }
    *param_1 = 0;
    if (local_4 != DAT_004a2a14) {
      return *(undefined2 *)(local_4 + 0x20);
    }
  }
  return 0;
}


