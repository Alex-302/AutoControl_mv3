// ___vcrt_FlsGetValue @ 0045ee4b size=58 callers=1

/* Library Function - Single Match
    ___vcrt_FlsGetValue
   
   Library: Visual Studio 2015 Release */

void __cdecl ___vcrt_FlsGetValue(DWORD param_1)

{
  code *pcVar1;
  
  pcVar1 = try_get_function(6,"FlsGetValue",(module_id *)&DAT_00483ec0,(module_id *)&DAT_00483ec8);
  if (pcVar1 == (code *)0x0) {
    TlsGetValue(param_1);
  }
  else {
    guard_check_icall();
    (*pcVar1)();
  }
  return;
}


