// FUN_0045a219 @ 0045a219 size=70 callers=26

void __cdecl FUN_0045a219(int *param_1)

{
  FUN_0045a25f();
  do {
    if (*param_1 == 0) {
      *param_1 = -1;
LAB_0045a258:
      FUN_0045a2ac();
      return;
    }
    if (*param_1 != -1) {
      *(undefined4 *)(*(int *)((int)ThreadLocalStoragePointer + _tls_index * 4) + 8) = DAT_0049d064;
      goto LAB_0045a258;
    }
    __Init_thread_wait(100);
  } while( true );
}


