// ~_Init_atexit @ 00459580 size=100 callers=1

/* Library Function - Single Match
    public: __thiscall _Init_atexit::~_Init_atexit(void)
   
   Library: Visual Studio 2015 Release */

void __thiscall _Init_atexit::~_Init_atexit(_Init_atexit *this)

{
  int iVar1;
  uint uVar2;
  code *pcVar3;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 uStack_8;
  
  uStack_8 = 0xffffffff;
  puStack_c = &LAB_0047ed78;
  local_10 = ExceptionList;
  uVar2 = DAT_0049d070 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  while (DAT_0049d008 < 10) {
    iVar1 = DAT_0049d008 * 4;
    DAT_0049d008 = DAT_0049d008 + 1;
    pcVar3 = DecodePointer(*(PVOID *)(iVar1 + 0x49efb0));
    if (pcVar3 != (code *)0x0) {
      guard_check_icall();
      (*pcVar3)(uVar2);
    }
  }
  ExceptionList = local_10;
  return;
}


