// FUN_0044a210 @ 0044a210 size=82 callers=4

void __thiscall
FUN_0044a210(void *this,undefined4 param_1,uint *param_2,uint param_3,uint *param_4,uint param_5)

{
  uint uVar1;
  
  while ((param_2 != param_4 || (param_3 != param_5))) {
    if (*(char *)this == '\0') {
      uVar1 = *param_2 & ~(1 << (param_3 & 0x1f));
    }
    else {
      uVar1 = *param_2 | 1 << (param_3 & 0x1f);
    }
    *param_2 = uVar1;
    if (param_3 < 0x1f) {
      param_3 = param_3 + 1;
    }
    else {
      param_2 = param_2 + 1;
      param_3 = 0;
    }
  }
  return;
}


