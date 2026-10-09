// _JumpToContinuation @ 0045cf99 size=43 callers=1

/* Library Function - Single Match
    void __stdcall _JumpToContinuation(void *,struct EHRegistrationNode *)
   
   Library: Visual Studio 2015 Release */

void _JumpToContinuation(void *param_1,EHRegistrationNode *param_2)

{
  ExceptionList = *(void **)ExceptionList;
                    /* WARNING: Could not recover jumptable at 0x0045cfc2. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*param_1)();
  return;
}


