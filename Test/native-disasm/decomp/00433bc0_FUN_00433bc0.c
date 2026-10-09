// FUN_00433bc0 @ 00433bc0 size=190 callers=43

char * __fastcall FUN_00433bc0(undefined4 *param_1)

{
  char cVar1;
  char *pcVar2;
  char *local_14;
  undefined1 local_10;
  undefined **local_c;
  undefined8 local_8;
  
  pcVar2 = (char *)*param_1;
  cVar1 = *pcVar2;
  if (cVar1 == '\0') {
    local_c = std::exception::vftable;
    local_14 = "cannot get value";
    local_10 = 1;
    local_8 = 0;
    ___std_exception_copy(&local_14,(undefined4 *)&local_8);
    local_c = std::out_of_range::vftable;
                    /* WARNING: Subroutine does not return */
    __CxxThrowException_8((int *)&local_c,&DAT_00499ebc);
  }
  if (cVar1 != '\x01') {
    if (cVar1 == '\x02') {
      pcVar2 = (char *)param_1[2];
    }
    else if (param_1[3] != 0) {
      local_c = std::exception::vftable;
      local_14 = "cannot get value";
      local_10 = 1;
      local_8 = 0;
      ___std_exception_copy(&local_14,(undefined4 *)&local_8);
      local_c = std::out_of_range::vftable;
                    /* WARNING: Subroutine does not return */
      __CxxThrowException_8((int *)&local_c,&DAT_00499ebc);
    }
    return pcVar2;
  }
  return (char *)(param_1[1] + 0x28);
}


