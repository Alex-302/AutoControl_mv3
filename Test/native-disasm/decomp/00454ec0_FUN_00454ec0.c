// FUN_00454ec0 @ 00454ec0 size=95 callers=1

void * __thiscall FUN_00454ec0(void *this,char *param_1,char *param_2,char *param_3,char *param_4)

{
  char cVar1;
  char cVar2;
  char *pcVar3;
  
  pcVar3 = param_1;
  while ((pcVar3 != param_2 && (param_3 != param_4))) {
    cVar1 = *pcVar3;
    cVar2 = *param_3;
    pcVar3 = pcVar3 + 1;
    param_3 = param_3 + 1;
    if (cVar1 != cVar2) {
      *(char **)this = param_1;
      return this;
    }
  }
  if (param_3 == param_4) {
    param_1 = pcVar3;
  }
  *(char **)this = param_1;
  return this;
}


