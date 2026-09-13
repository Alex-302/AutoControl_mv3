// ___vcrt_FlsSetValue @ 0045ee85 size=61 callers=4

/* Library Function - Single Match
    ___vcrt_FlsSetValue
   
   Library: Visual Studio 2015 Release */

void __cdecl ___vcrt_FlsSetValue(DWORD param_1,LPVOID param_2)

{
  code *pcVar1;
  
  pcVar1 = try_get_function(7,"FlsSetValue",(module_id *)&DAT_00483ec8,(module_id *)&DAT_00483ed0);
  if (pcVar1 == (code *)0x0) {
    TlsSetValue(param_1,param_2);
  }
  else {
    guard_check_icall();
    (*pcVar1)();
  }
  return;
}


