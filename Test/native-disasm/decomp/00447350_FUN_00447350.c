// FUN_00447350 @ 00447350 size=50 callers=1

void __fastcall FUN_00447350(void *param_1,int param_2)

{
  for (; param_2 != 0; param_2 = param_2 + -1) {
    if (param_1 != (void *)0x0) {
      _memset(param_1,0,0x104);
    }
    param_1 = (void *)((int)param_1 + 0x104);
  }
  return;
}


