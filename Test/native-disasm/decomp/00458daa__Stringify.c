// _Stringify @ 00458daa size=130 callers=1

/* Library Function - Single Match
    private: static char const * __cdecl std::regex_error::_Stringify(enum
   std::regex_constants::error_type)
   
   Library: Visual Studio 2015 Release */

char * __cdecl std::regex_error::_Stringify(error_type param_1)

{
  switch(param_1) {
  case 0:
    return "regex_error(error_collate): The expression contained an invalid collating element name."
    ;
  case 1:
    return "regex_error(error_ctype): The expression contained an invalid character class name.";
  case 2:
    return 
    "regex_error(error_escape): The expression contained an invalid escaped character, or a trailing escape."
    ;
  case 3:
    return "regex_error(error_backref): The expression contained an invalid back reference.";
  case 4:
    return "regex_error(error_brack): The expression contained mismatched [ and ].";
  case 5:
    return "regex_error(error_paren): The expression contained mismatched ( and ).";
  case 6:
    return "regex_error(error_brace): The expression contained mismatched { and }.";
  case 7:
    return 
    "regex_error(error_badbrace): The expression contained an invalid range in a { expression }.";
  case 8:
    return 
    "regex_error(error_range): The expression contained an invalid character range, such as [b-a] in most encodings."
    ;
  case 9:
    return 
    "regex_error(error_space): There was insufficient memory to convert the expression into a finite state machine."
    ;
  case 10:
    return 
    "regex_error(error_badrepeat): One of *?+{ was not preceded by a valid regular expression.";
  case 0xb:
    return 
    "regex_error(error_complexity): The complexity of an attempted match against a regular expression exceeded a pre-set level."
    ;
  case 0xc:
    return 
    "regex_error(error_stack): There was insufficient memory to determine whether the regular expression could match the specified character sequence."
    ;
  case 0xd:
    return "regex_error(error_parse)";
  case 0xe:
    return "regex_error(error_syntax)";
  default:
    return "regex_error";
  }
}


