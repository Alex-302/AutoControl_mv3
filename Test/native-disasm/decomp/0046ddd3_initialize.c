// initialize @ 0046ddd3 size=49 callers=12

/* Library Function - Single Match
    public: void __thiscall __crt_state_management::dual_state_global<char * *>::initialize(char * *
   const)
   
   Library: Visual Studio 2015 Release */

void __thiscall
__crt_state_management::dual_state_global<char**>::initialize
          (dual_state_global<char**> *this,char **param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar2 = 0;
  uVar1 = ~-(uint)(this + 4 < this) & (uint)(this + 4 + (3 - (int)this)) >> 2;
  if (uVar1 != 0) {
    do {
      uVar2 = uVar2 + 1;
      *(char ***)this = param_1;
      this = this + 4;
    } while (uVar2 != uVar1);
  }
  return;
}


