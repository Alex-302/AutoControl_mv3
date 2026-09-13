// ___vcrt_FlsFree @ 0045ee11 size=58 callers=1

/* Library Function - Single Match
    ___vcrt_FlsFree
   
   Library: Visual Studio 2015 Release */

void __cdecl ___vcrt_FlsFree(DWORD param_1)

{
  code *pcVar1;
  
  pcVar1 = try_get_function(5,"FlsFree",(module_id *)&DAT_00483eb8,(module_id *)&DAT_00483ec0);
  if (pcVar1 == (code *)0x0) {
    TlsFree(param_1);
  }
  else {
    guard_check_icall();
    (*pcVar1)();
  }
  return;
}


