// FUN_00425a50 @ 00425a50 size=69 callers=1

void * __cdecl FUN_00425a50(void *param_1)

{
  DAT_004a2b60 = GetDesktopWindow();
  FUN_00434a40(param_1,(char *)0x0,(char *)0x0);
  EnumChildWindows(DAT_004a2b60,thunk_FUN_00425aa0,(LPARAM)param_1);
  return param_1;
}


