rows = 480;
columns = 640;
rgb = load('1.frm');

Rmat = zeros(480,640);
Gmat = zeros(480,640);
Bmat = zeros(480,640);


for j = 1:1:columns
    for i = 1:1:rows
        Rmat(i,j) = rgb((j-1)*480+i,1);
        Gmat(i,j) = rgb((j-1)*480+i,2);
        Bmat(i,j) = rgb((j-1)*480+i,3);

    end
end
figure
imshow(uint8(Rmat));
figure
imshow(uint8(Gmat));
figure
imshow(uint8(Bmat));