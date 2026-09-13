// FUN_004059a0 @ 004059a0 size=145 callers=2

void __thiscall FUN_004059a0(void *this,byte param_1)

{
  void *pvVar1;
  uint *puVar2;
  void *pvVar3;
  void *pvVar4;
  uint *puVar5;
  
  pvVar1 = *(void **)this;
  if (param_1 == 0) {
    *(void **)((int)this + 4) = pvVar1;
    param_1 = 0;
    FUN_00434cd0(this,&param_1);
  }
  else {
    puVar5 = *(uint **)((int)this + 4);
    puVar2 = _memchr(pvVar1,(uint)param_1,(int)puVar5 - (int)pvVar1);
    if (puVar2 != (uint *)0x0) {
      puVar5 = puVar2;
    }
    if (puVar5 != *(uint **)((int)this + 4)) {
      FUN_0045b0e0(puVar5,(uint *)((int)puVar5 + 1),
                   (int)*(uint **)((int)this + 4) - ((int)puVar5 + 1));
      *(int *)((int)this + 4) = *(int *)((int)this + 4) + -1;
    }
    pvVar1 = *(void **)((int)this + 4);
    param_1 = 0;
    pvVar3 = _memchr(*(void **)this,0,(int)pvVar1 - (int)*(void **)this);
    pvVar4 = pvVar1;
    if (pvVar3 != (void *)0x0) {
      pvVar4 = pvVar3;
    }
    if (pvVar4 == pvVar1) {
      FUN_00434cd0(this,&param_1);
      return;
    }
  }
  return;
}


