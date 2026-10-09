// FUN_0043aa60 @ 0043aa60 size=108 callers=1

int __thiscall FUN_0043aa60(void *this,void *param_1,undefined4 param_2,size_t param_3)

{
  int iVar1;
  char *pcVar2;
  void *pvVar3;
  void *pvVar4;
  
  iVar1 = *(int *)((int)this + 0x10);
  if (iVar1 != 0) {
    pvVar4 = this;
    if (0xf < *(uint *)((int)this + 0x14)) {
      pvVar4 = *(void **)this;
    }
    pcVar2 = this;
    if (0xf < *(uint *)((int)this + 0x14)) {
      pcVar2 = *(char **)this;
    }
    for (; pcVar2 < (char *)(iVar1 + (int)pvVar4); pcVar2 = pcVar2 + 1) {
      if ((param_3 == 0) || (pvVar3 = _memchr(param_1,(int)*pcVar2,param_3), pvVar3 == (void *)0x0))
      {
        if (0xf < *(uint *)((int)this + 0x14)) {
          this = *(void **)this;
        }
        return (int)pcVar2 - (int)this;
      }
    }
  }
  return -1;
}


