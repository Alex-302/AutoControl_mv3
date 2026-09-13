// scoped_fp_state_reset @ 00474000 size=42 callers=1

/* Library Function - Multiple Matches With Same Base Name
    public: __thiscall `anonymous namespace'::scoped_fp_state_reset::scoped_fp_state_reset(void)
    public: __thiscall `anonymous namespace'::scoped_fp_state_reset::scoped_fp_state_reset(void)
   
   Library: Visual Studio 2015 Release */

uint * __fastcall scoped_fp_state_reset(uint *param_1)

{
  fegetenv(param_1);
  if (((byte)*param_1 & 0x1f) == 0x1f) {
    *(undefined1 *)(param_1 + 2) = 0;
  }
  else {
    feholdexcept(param_1);
    *(undefined1 *)(param_1 + 2) = 1;
  }
  return param_1;
}


