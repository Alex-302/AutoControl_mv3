// FUN_0040dac0 @ 0040dac0 size=43 callers=1

void FUN_0040dac0(undefined4 param_1,undefined4 param_2,HWND param_3,ULONG_PTR param_4)

{
  if ((param_4 == 1) && (param_3 != (HWND)0x0)) {
    SendMessageTimeoutA(param_3,0x3d,0,1,0x22,1000,&param_4);
  }
  return;
}


