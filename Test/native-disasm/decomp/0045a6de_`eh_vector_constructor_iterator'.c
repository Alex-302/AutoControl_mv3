// `eh_vector_constructor_iterator' @ 0045a6de size=79 callers=5

/* WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4 */
/* WARNING: Function: __SEH_epilog4 replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    void __stdcall `eh vector constructor iterator'(void *,unsigned int,unsigned int,void
   (__thiscall*)(void *),void (__thiscall*)(void *))
   
   Library: Visual Studio 2015 Release */

void _eh_vector_constructor_iterator_
               (void *param_1,uint param_2,uint param_3,_func_void_void_ptr *param_4,
               _func_void_void_ptr *param_5)

{
  uint uVar1;
  void *in_stack_ffffffcc;
  
  for (uVar1 = 0; uVar1 != param_3; uVar1 = uVar1 + 1) {
    guard_check_icall();
    (*param_4)(in_stack_ffffffcc);
  }
  FUN_0045a733();
  return;
}


