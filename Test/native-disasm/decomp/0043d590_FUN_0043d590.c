// FUN_0043d590 @ 0043d590 size=213 callers=5

void __fastcall FUN_0043d590(uint param_1,uint param_2,uint param_3)

{
  char *local_14;
  undefined1 local_10;
  undefined **local_c;
  undefined8 local_8;
  
  if ((param_1 < param_2) || (param_1 < param_3)) {
    local_c = std::exception::vftable;
    local_14 = "len out of range";
    local_10 = 1;
    local_8 = 0;
    ___std_exception_copy(&local_14,(undefined4 *)&local_8);
    local_c = std::out_of_range::vftable;
                    /* WARNING: Subroutine does not return */
    __CxxThrowException_8((int *)&local_c,&DAT_00499ebc);
  }
  if (~param_3 < param_1) {
    local_c = std::exception::vftable;
    local_14 = "len+offset out of range";
    local_10 = 1;
    local_8 = 0;
    ___std_exception_copy(&local_14,(undefined4 *)&local_8);
    local_c = std::out_of_range::vftable;
                    /* WARNING: Subroutine does not return */
    __CxxThrowException_8((int *)&local_c,&DAT_00499ebc);
  }
  if (param_1 < param_2 + param_3) {
    FUN_00402590(&local_c,"len+offset out of range");
                    /* WARNING: Subroutine does not return */
    __CxxThrowException_8((int *)&local_c,&DAT_00499ebc);
  }
  return;
}


