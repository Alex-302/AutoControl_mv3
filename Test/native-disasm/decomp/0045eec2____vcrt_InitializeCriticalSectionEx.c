// ___vcrt_InitializeCriticalSectionEx @ 0045eec2 size=70 callers=2

/* Library Function - Single Match
    ___vcrt_InitializeCriticalSectionEx
   
   Library: Visual Studio 2015 Release */

void __cdecl
___vcrt_InitializeCriticalSectionEx(LPCRITICAL_SECTION param_1,DWORD param_2,undefined4 param_3)

{
  code *pcVar1;
  
  pcVar1 = try_get_function(8,"InitializeCriticalSectionEx",(module_id *)&DAT_00483ed0,
                            (module_id *)&PTR_s___based__00483ed8);
  if (pcVar1 == (code *)0x0) {
    InitializeCriticalSectionAndSpinCount(param_1,param_2);
  }
  else {
    guard_check_icall();
    (*pcVar1)(param_1,param_2,param_3);
  }
  return;
}


