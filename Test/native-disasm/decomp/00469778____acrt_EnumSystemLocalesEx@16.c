// ___acrt_EnumSystemLocalesEx@16 @ 00469778 size=109 callers=2

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    ___acrt_EnumSystemLocalesEx@16
   
   Library: Visual Studio 2015 Release */

void ___acrt_EnumSystemLocalesEx_16
               (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  code *pcVar1;
  undefined4 *local_c;
  uint local_8;
  
  local_8 = DAT_0049d070 ^ (uint)&stack0xfffffffc;
  pcVar1 = try_get_function(2,"EnumSystemLocalesEx",(module_id *)&DAT_00486300,
                            (module_id *)"EnumSystemLocalesEx");
  if (pcVar1 == (code *)0x0) {
    local_c = &param_1;
    __acrt_lock_and_call<<lambda_a463b7b0560cfcaf9b17f27c6ef46564>_>
              (4,(<lambda_a463b7b0560cfcaf9b17f27c6ef46564> *)&local_c);
  }
  else {
    (*(code *)PTR_guard_check_icall_004805b0)(param_1,param_2,param_3,param_4);
    (*pcVar1)();
  }
  return;
}


