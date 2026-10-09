// FUN_0044d2d0 @ 0044d2d0 size=71 callers=1

void __fastcall FUN_0044d2d0(int param_1)

{
  DAT_004a26c4 = 0;
  DAT_004a26b4 = GetTickCount();
  FUN_00413390(0x850,'\x01');
  if (*(char *)(param_1 + 4) != '\0') {
    DAT_004a26c4 = 0;
    DAT_004a26b4 = GetTickCount();
    FUN_00413390(0x851,'\x01');
    return;
  }
  return;
}


