// FUN_00455290 @ 00455290 size=107 callers=2

int __fastcall FUN_00455290(int param_1,int param_2,int param_3)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined1 local_8;
  undefined3 uStack_7;
  
  puStack_c = &LAB_0047ea91;
  local_10 = ExceptionList;
  uStack_7 = 0;
  ExceptionList = &local_10;
  for (; param_1 != param_2; param_1 = param_1 + 0x10) {
    local_8 = 1;
    if ((void *)param_3 != (void *)0x0) {
      FUN_00434940((void *)param_3,(undefined1 *)param_1);
    }
    param_3 = param_3 + 0x10;
  }
  ExceptionList = local_10;
  return (int)(void *)param_3;
}


