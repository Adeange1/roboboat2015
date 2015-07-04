clc

def = legacy_code('initialize');
def.SourceFiles = {'rgbtohsv_int.c'};
def.HeaderFiles = {'rgbtohsv_int.h'};
def.SFunctionName = 'rgbtohsv_int_sfun';
def.OutputFcnSpec = 'void rgbtohsv_wrapper_int(uint8 y1[480][640][3], uint8 u1[][][])';
def.SampleTime = [-1,0];
legacy_code('sfcn_cmex_generate', def);
legacy_code('compile', def);
legacy_code('sfcn_tlc_generate', def);
