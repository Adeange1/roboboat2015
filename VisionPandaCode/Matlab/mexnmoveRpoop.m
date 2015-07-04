function mexnmoveR(Filename)

mex(Filename)

comstr = sprintf('!copy %s C:\\RTtools\\VU-RLNX\\RLNX\\matlab_includes\\rtw\\c\\rlnx\\rlnx_source\\',Filename);
eval(comstr)

comstr = sprintf('cd C:\\RTtools\\VU-RLNX\\RLNX\\matlab_includes\\rtw\\c\\rlnx\\rlnx_source && C:\\RTtools\\VU-RLNX\\Comms_Tools\\PuTTY\\pscp -pw password -q %s root@192.168.7.15:/matlab_includes/rtw/c/rlnx/rlnx_source',Filename);
[status,result]=system(comstr)