// shortsort @ 00475910 size=147 callers=1

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    void __cdecl shortsort(char *,char *,unsigned int,int (__cdecl*)(void const *,void const *))
   
   Library: Visual Studio 2015 Release */

void __cdecl
shortsort(char *param_1,char *param_2,uint param_3,_func_int_void_ptr_void_ptr *param_4)

{
  char *pcVar1;
  char cVar2;
  char *pcVar3;
  char *pcVar4;
  uint uVar5;
  int iVar6;
  void *in_stack_ffffffdc;
  void *pvVar7;
  
  for (; pcVar3 = param_1, pcVar4 = param_1, param_1 < param_2; param_2 = param_2 + -param_3) {
    while (pcVar4 = pcVar4 + param_3, pcVar4 <= param_2) {
      pvVar7 = (void *)0x47594b;
      (*(code *)PTR_guard_check_icall_004805b0)(pcVar4,pcVar3);
      iVar6 = (*param_4)(in_stack_ffffffdc,pvVar7);
      if (0 < iVar6) {
        pcVar3 = pcVar4;
      }
    }
    uVar5 = param_3;
    pcVar4 = param_2;
    if (pcVar3 != param_2) {
      for (; uVar5 != 0; uVar5 = uVar5 - 1) {
        pcVar1 = pcVar4 + 1;
        cVar2 = pcVar1[(int)(pcVar3 + (-1 - (int)param_2))];
        pcVar1[(int)(pcVar3 + (-1 - (int)param_2))] = *pcVar4;
        *pcVar4 = cVar2;
        pcVar4 = pcVar1;
      }
    }
  }
  return;
}


