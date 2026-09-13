// FUN_0045a1da @ 0045a1da size=63 callers=26

void __cdecl FUN_0045a1da(int *param_1)

{
  FUN_0045a25f();
  DAT_0049d064 = DAT_0049d064 + 1;
  *param_1 = DAT_0049d064;
  *(int *)(*(int *)((int)ThreadLocalStoragePointer + _tls_index * 4) + 8) = DAT_0049d064;
  FUN_0045a2ac();
  __Init_thread_notify();
  return;
}


