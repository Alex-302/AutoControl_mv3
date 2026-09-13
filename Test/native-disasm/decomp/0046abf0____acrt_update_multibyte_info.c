// ___acrt_update_multibyte_info @ 0046abf0 size=45 callers=1

/* Library Function - Single Match
    ___acrt_update_multibyte_info
   
   Library: Visual Studio 2015 Release */

void __cdecl ___acrt_update_multibyte_info(int param_1,int *param_2)

{
  int *piVar1;
  
  if (((undefined *)*param_2 != PTR_DAT_0049d9a8) &&
     ((*(uint *)(param_1 + 0x350) & DAT_0049d3f8) == 0)) {
    piVar1 = ___acrt_update_thread_multibyte_data();
    *param_2 = (int)piVar1;
  }
  return;
}


