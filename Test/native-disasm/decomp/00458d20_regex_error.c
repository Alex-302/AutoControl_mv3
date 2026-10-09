// regex_error @ 00458d20 size=48 callers=1

/* Library Function - Single Match
    public: __thiscall std::regex_error::regex_error(enum std::regex_constants::error_type)
   
   Library: Visual Studio 2015 Release */

regex_error * __thiscall std::regex_error::regex_error(regex_error *this,error_type param_1)

{
  char *pcVar1;
  
  pcVar1 = _Stringify(param_1);
  FUN_004022b0(this,pcVar1);
  *(error_type *)(this + 0xc) = param_1;
  *(undefined ***)this = vftable;
  return this;
}


