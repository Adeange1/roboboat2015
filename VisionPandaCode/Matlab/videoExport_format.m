function [Rout, Gout, Bout] = videoExport_format(Rin,Gin,Bin)

Rout = zeros(1,307200);
Bout = zeros(1,307200);
Gout = zeros(1,307200);

for i = 1:640
    for j = 1:480
        Rout(j+480*(i-1)) = Rin(j,i);
        Gout(j+480*(i-1)) = Gin(j,i);
        Bout(j+480*(i-1)) = Bin(j,i);
    end
    
end