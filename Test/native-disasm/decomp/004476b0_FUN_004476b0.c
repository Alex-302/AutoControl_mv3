// FUN_004476b0 @ 004476b0 size=68 callers=3

undefined4 __fastcall FUN_004476b0(char *param_1,char *param_2)

{
  int *in_EAX;
  
  while( true ) {
    if (param_1 == param_2) {
      return CONCAT31((int3)((uint)in_EAX >> 8),1);
    }
    if (((*param_1 != '\x02') || (in_EAX = *(int **)(param_1 + 8), in_EAX[1] - *in_EAX >> 4 != 2))
       || (in_EAX = (int *)FUN_00434550(param_1,0), (char)*in_EAX != '\x03')) break;
    param_1 = param_1 + 0x10;
  }
  return (uint)in_EAX & 0xffffff00;
}


