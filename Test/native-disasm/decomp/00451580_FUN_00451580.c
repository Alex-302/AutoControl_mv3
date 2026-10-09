// FUN_00451580 @ 00451580 size=88 callers=6

void __thiscall FUN_00451580(void *this,int param_1,error_type param_2)

{
  char *pcVar1;
  
  if (*(int *)((int)this + 0x4c) != param_1) {
                    /* WARNING: Subroutine does not return */
    FUN_00458f04(param_2);
  }
  pcVar1 = *(char **)this;
  if (pcVar1 != *(char **)((int)this + 8)) {
    if (((*pcVar1 == '\\') && (pcVar1 = pcVar1 + 1, pcVar1 != *(char **)((int)this + 8))) &&
       ((((*(uint *)((int)this + 0x50) & 8) == 0 && ((*pcVar1 == '(' || (*pcVar1 == ')')))) ||
        (((*(uint *)((int)this + 0x50) & 0x10) == 0 && ((*pcVar1 == '{' || (*pcVar1 == '}')))))))) {
      *(char **)this = pcVar1;
    }
    *(int *)this = *(int *)this + 1;
  }
  FUN_00449160(this);
  return;
}


