%Sistema 1
k1=1.023;
tao1=0.02;

k2=0.996;
tao2=0.025;

k3=1.0265;
tao3=0.022;

k4=0.997;
tao4=0.02

ft1=tf(k1,[tao1 1])
ft2=tf(k2,[tao2 1])
ft3=tf(k3,[tao3 1])
ft4=tf(k4,[tao4 1])

fT=[ft1 zeros(1,3); 0 ft2 zeros(1,2);zeros(1,2) ft3 0;zeros(1,3) ft4];


sis=ss(fT)
