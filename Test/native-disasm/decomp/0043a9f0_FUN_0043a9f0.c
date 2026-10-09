// FUN_0043a9f0 @ 0043a9f0 size=104 callers=1

int __thiscall FUN_0043a9f0(void *this,void *param_1,undefined4 param_2,size_t param_3)

{
  void *pvVar1;
  char *pcVar2;
  char *pcVar3;
  
  if (*(int *)((int)this + 0x10) != 0) {
    pvVar1 = this;
    if (0xf < *(uint *)((int)this + 0x14)) {
      pvVar1 = *(void **)this;
    }
    pcVar3 = (char *)((int)pvVar1 + *(int *)((int)this + 0x10) + -1);
    while( true ) {
      if ((param_3 == 0) || (pvVar1 = _memchr(param_1,(int)*pcVar3,param_3), pvVar1 == (void *)0x0))
      {
        if (0xf < *(uint *)((int)this + 0x14)) {
          this = *(void **)this;
        }
        return (int)pcVar3 - (int)this;
      }
      pcVar2 = (char *)FUN_00435400(this);
      if (pcVar3 == pcVar2) break;
      pcVar3 = pcVar3 + -1;
    }
  }
  return -1;
}


