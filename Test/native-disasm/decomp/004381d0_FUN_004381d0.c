// FUN_004381d0 @ 004381d0 size=203 callers=68

void * __thiscall FUN_004381d0(void *this,char param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  char *local_1c;
  undefined1 local_18;
  undefined **local_14;
  undefined8 local_10;
  
  switch(param_1) {
  case '\0':
    break;
  case '\x01':
    puVar1 = FUN_00442940();
    *(undefined4 **)this = puVar1;
    break;
  case '\x02':
    uVar2 = FUN_004429b0();
    *(undefined4 *)this = uVar2;
    return this;
  case '\x03':
    puVar3 = FUN_00442d30();
    *(undefined1 **)this = puVar3;
    return this;
  case '\x04':
    *(undefined1 *)this = 0;
    return this;
  case '\x05':
  case '\x06':
    *(undefined4 *)this = 0;
    *(undefined4 *)((int)this + 4) = 0;
    return this;
  case '\a':
    *(undefined8 *)this = 0;
    return this;
  default:
    if (param_1 == '\0') {
      local_14 = std::exception::vftable;
      local_1c = "961c151d2e87f2686a955a9be24d316f1362bf21 2.1.1";
      local_18 = 1;
      local_10 = 0;
      ___std_exception_copy(&local_1c,(undefined4 *)&local_10);
      local_14 = &PTR_FUN_0048eee8;
                    /* WARNING: Subroutine does not return */
      __CxxThrowException_8((int *)&local_14,&DAT_0049a03c);
    }
  }
  return this;
}


