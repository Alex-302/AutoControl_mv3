// Is_bad_exception_allowed @ 0045c26e size=63 callers=1

/* Library Function - Single Match
    unsigned char __cdecl Is_bad_exception_allowed(struct _s_ESTypeList const *)
   
   Library: Visual Studio 2015 Release */

uchar __cdecl Is_bad_exception_allowed(_s_ESTypeList *param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 0;
  if (0 < param_1->nCount) {
    iVar2 = 0;
    do {
      uVar1 = ___std_type_info_compare
                        (*(int *)((int)&param_1->pTypeArray->pType + iVar2) + 4,0x49dc38);
      if (uVar1 == 0) {
        return '\x01';
      }
      iVar3 = iVar3 + 1;
      iVar2 = iVar2 + 0x10;
    } while (iVar3 < param_1->nCount);
  }
  return '\0';
}


