// FUN_004531c0 @ 004531c0 size=131 callers=1

void * __thiscall
FUN_004531c0(void *this,undefined4 param_1,uint *param_2,uint param_3,uint *param_4,uint param_5,
            uint *param_6,uint param_7)

{
  uint uVar1;
  
  while ((param_2 != param_4 || (param_3 != param_5))) {
    if ((*param_2 & 1 << ((byte)param_3 & 0x1f)) == 0) {
      uVar1 = *param_6 & ~(1 << (param_7 & 0x1f));
    }
    else {
      uVar1 = *param_6 | 1 << (param_7 & 0x1f);
    }
    *param_6 = uVar1;
    if (param_7 < 0x1f) {
      param_7 = param_7 + 1;
    }
    else {
      param_7 = 0;
      param_6 = param_6 + 1;
    }
    if (param_3 < 0x1f) {
      param_3 = param_3 + 1;
    }
    else {
      param_2 = param_2 + 1;
      param_3 = 0;
    }
  }
  *(uint **)this = param_6;
  *(uint *)((int)this + 4) = param_7;
  return this;
}


