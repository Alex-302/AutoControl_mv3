// append @ 00470421 size=53 callers=1

/* Library Function - Multiple Matches With Same Base Name
    public: int __thiscall `anonymous namespace'::argument_list<char>::append(char * const)
    public: int __thiscall `anonymous namespace'::argument_list<char>::append(char * const)
    public: int __thiscall `anonymous namespace'::argument_list<wchar_t>::append(wchar_t * const)
    public: int __thiscall `anonymous namespace'::argument_list<wchar_t>::append(wchar_t * const)
   
   Library: Visual Studio 2015 Release */

int __thiscall append(void *this,void *param_1)

{
  int iVar1;
  
  iVar1 = expand_if_necessary(this);
  if (iVar1 == 0) {
    **(undefined4 **)((int)this + 4) = param_1;
    *(int *)((int)this + 4) = *(int *)((int)this + 4) + 4;
    iVar1 = 0;
  }
  else {
    FID_conflict__free(param_1);
  }
  return iVar1;
}


