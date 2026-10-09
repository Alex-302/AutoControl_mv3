// operator= @ 00458990 size=84 callers=4

/* Library Function - Single Match
    public: class std::_Yarn<char> & __thiscall std::_Yarn<char>::operator=(char const *)
   
   Library: Visual Studio 2015 Release */

_Yarn<char> * __thiscall std::_Yarn<char>::operator=(_Yarn<char> *this,char *param_1)

{
  char cVar1;
  uint *puVar2;
  char *pcVar3;
  
  if (*(char **)this != param_1) {
    if (*(int *)this != 0) {
      FID_conflict__free(*(void **)this);
    }
    *(undefined4 *)this = 0;
    if (param_1 != (char *)0x0) {
      cVar1 = *param_1;
      pcVar3 = param_1;
      while (cVar1 != '\0') {
        pcVar3 = pcVar3 + 1;
        cVar1 = *pcVar3;
      }
      puVar2 = (uint *)FUN_004665ab((size_t)(pcVar3 + (1 - (int)param_1)));
      *(uint **)this = puVar2;
      if (puVar2 != (uint *)0x0) {
        FUN_0045c870(puVar2,(uint *)param_1,(uint)(pcVar3 + (1 - (int)param_1)));
      }
    }
  }
  return this;
}


