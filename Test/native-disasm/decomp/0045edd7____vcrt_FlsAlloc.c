// ___vcrt_FlsAlloc @ 0045edd7 size=58 callers=1

/* Library Function - Single Match
    ___vcrt_FlsAlloc
   
   Library: Visual Studio 2015 Release */

void __cdecl ___vcrt_FlsAlloc(undefined4 param_1)

{
  code *pcVar1;
  
  pcVar1 = try_get_function(4,"FlsAlloc",(module_id *)&DAT_00483eb0,(module_id *)&DAT_00483eb8);
  if (pcVar1 != (code *)0x0) {
    guard_check_icall();
    (*pcVar1)(param_1);
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x0045ee0b. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  TlsAlloc();
  return;
}


