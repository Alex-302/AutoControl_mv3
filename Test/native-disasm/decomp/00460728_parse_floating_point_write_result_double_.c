// parse_floating_point_write_result<double> @ 00460728 size=218 callers=1

/* Library Function - Single Match
    enum SLD_STATUS __cdecl __crt_strtox::parse_floating_point_write_result<double>(enum
   __crt_strtox::floating_point_parse_result,struct __crt_strtox::floating_point_string const
   &,double * const)
   
   Library: Visual Studio 2015 Release */

SLD_STATUS __cdecl
__crt_strtox::parse_floating_point_write_result<double>
          (floating_point_parse_result param_1,floating_point_string *param_2,double *param_3)

{
  SLD_STATUS SVar1;
  
  switch(param_1) {
  case 0:
    SVar1 = convert_decimal_string_to_floating_type<double>(param_2,param_3);
    return SVar1;
  case 1:
    SVar1 = convert_hexadecimal_string_to_floating_type<double>(param_2,param_3);
    return SVar1;
  case 2:
    assemble_floating_point_zero<double>((bool)param_2[0x308],param_3);
    break;
  case 3:
    assemble_floating_point_infinity<double>((bool)param_2[0x308],param_3);
    break;
  case 4:
    assemble_floating_point_qnan<double>((bool)param_2[0x308],param_3);
    break;
  case 5:
    assemble_floating_point_snan<double>((bool)param_2[0x308],param_3);
    break;
  case 6:
    assemble_floating_point_ind<double>(param_3);
    break;
  case 7:
    assemble_floating_point_zero<double>(false,param_3);
    return 1;
  case 8:
    assemble_floating_point_zero<double>((bool)param_2[0x308],param_3);
    return 2;
  case 9:
    assemble_floating_point_infinity<double>((bool)param_2[0x308],param_3);
    return 3;
  default:
    return 1;
  }
  return 0;
}


