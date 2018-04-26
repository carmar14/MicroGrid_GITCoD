
%clear 
close all
clc
load('simulink2tf2.mat')
H = tf(linsys1);
%%Funcion de transferencia de DG1 
n11=cell2mat(H.Numerator(4,1));
n12=cell2mat(H.Numerator(4,2));
n13=cell2mat(H.Numerator(4,3));
d11=cell2mat(H.Denominator(4,1));
d12=cell2mat(H.Denominator(4,2));
d13=cell2mat(H.Denominator(4,3));
H1=tf(n11,d11)+tf(n12,d12)+tf(n13,d13); %ya no la voy a usar porque no sirvio XD
H1=tf(n11,d11)
step(H1)
Ts=0.012/50 %0.012/10
H1d=c2d(H1,Ts);
hold on
step(H1d)

%%Funcion de transferencia de DG2 
n11=cell2mat(H.Numerator(5,1));
n12=cell2mat(H.Numerator(5,2));
n13=cell2mat(H.Numerator(5,3));
d11=cell2mat(H.Denominator(5,1));
d12=cell2mat(H.Denominator(5,2));
d13=cell2mat(H.Denominator(5,3));
H2=tf(n11,d11)+tf(n12,d12)+tf(n13,d13);
H2=tf(n12,d12)
figure
step(H2)
H2d=c2d(H2,Ts);
hold on
step(H2d)

%%Funcion de transferencia de funete de voltaje 
n11=cell2mat(H.Numerator(2,1));
n12=cell2mat(H.Numerator(2,2));
n13=cell2mat(H.Numerator(2,3));
d11=cell2mat(H.Denominator(2,1));
d12=cell2mat(H.Denominator(2,2));
d13=cell2mat(H.Denominator(2,3));
H3=tf(n11,d11)+tf(n12,d12)+tf(n13,d13);
H3=tf(n13,d13)
figure
step(H3)
H3d=c2d(H3,Ts);
hold on
step(H3d)

%%Funcion de transferencia de funete de la carga
% n11=cell2mat(H.Numerator(1,1));
% n12=cell2mat(H.Numerator(1,2));
% n13=cell2mat(H.Numerator(1,3));
% d11=cell2mat(H.Denominator(1,1));
% d12=cell2mat(H.Denominator(1,2));
% d13=cell2mat(H.Denominator(1,3));
% H4=tf(n11,d11)+tf(n12,d12)+tf(n13,d13);
% H4=tf(n13,d13)
n11=cell2mat(H.Numerator(3,1));
n12=cell2mat(H.Numerator(3,2));
n13=cell2mat(H.Numerator(3,3));
n14=cell2mat(H.Numerator(3,4));
d11=cell2mat(H.Denominator(3,1));
d12=cell2mat(H.Denominator(3,2));
d13=cell2mat(H.Denominator(3,3));
d14=cell2mat(H.Denominator(3,4));
H4=tf(n11,d11)+tf(n12,d12)+tf(n13,d13)+tf(n14,d14);
H4=tf(n14,d14)
figure
step(H4)
H4d=c2d(H4,Ts);
hold on
step(H4d)

Numz=H1d.Numerator{1};
Denz=H1d.Denominator{1};


U = zeros(length(Numz), 1);
Y = zeros(length(Denz), 1);

t  =0:Ts:.2;
nn = 1;

ym = zeros(length(t), 1);


for n=0:Ts:.2

    U(1) = 1;
    
    Ycu = 0;
    Ycy = 0;
    
    for i=1:1:length(Numz)
        Ycu = (U(i)*Numz(i)) + Ycu;
    end

    for i=2:1:length(Denz)
        Ycy = ( Y(i)*-Denz(i) ) + Ycy;
    end

    Y(1) = Ycu + Ycy;



    for i=length(Numz):-1:2
        U(i)=U(i-1);
    end


    for i=length(Denz):-1:2
        Y(i)=Y(i-1);
    end
    ym(nn) = Y(1);
    nn = nn+1;
end

plot(t, ym);

roots(Denz)


%Prueba de ecuacion en diferencia
% n=0:Ts:0.2;
% x=10*sin(2*pi*60*n);
% figure
% plot(n,x)
% x1=0;
% x2=0;
% x3=0;
% x4=0;
% x5=0;
% x6=0;
% x7=0;
% x8=0;
% x9=0;
% x10=0;
% x11=0;
% y1=x1;
% y2=x2;
% y3=x3;
% y4=x4;
% y5=x5;
% y6=x6;
% y7=x7;
% y8=x8;
% y9=x9;
% y10=x10;
% y11=x11;
% %x=zeros(1,length(n));
% %x=ones(1,length(n));
% y=zeros(1,length(n));
% for o=1:length(n)
%     y(o)=0.8400*x1-3.8959*x2+7.9326*x3-10.2384*x4+10.2817*x5-8.0190*x6+4.0593*x7-1.0404*x8+0.0800*x9+0.0001*x10+4.8572*y1-10.4780*y2+14.3354*y3-15.0480*y4+12.3601*y5-7.0022*y6+2.3284*y7-0.3745*y8+0.0216*y9;
%     
%     if o>1
%         x1=x(o-1);
%         y1=y(o-1);
%     elseif o>2
%         x2=x(o-2);
%         y2=y(o-2);
%     elseif o>3
%         x3=x(o-3);
%         y3=y(o-3);
%     elseif o>4
%         x4=x(o-4);
%         y4=y(o-4);
%     elseif o>5
%         x5=x(o-5);
%         y5=y(o-5);
%     elseif o>6
%         x6=x(o-6);
%         y6=y(o-6);
%     elseif o>7
%         x7=x(o-7);
%         y7=y(o-7);
%     elseif o>8
%         x8=x(o-8);
%         y8=y(o-8);
%     elseif o>9
%         x9=x(o-9);
%         y9=y(o-9);
%     elseif o>10
%         x10=x(o-10);
%         y10=y(o-10);
%     elseif o>11
%         x11=x(o-11);
%         y11=y(o-11);
%     end
% %     y(o)=x(o)+0.5*y1;
% %     if o>1
% %         y1=y(o-1);
% %     end
% end
% 
% figure
% 
% plot(n,y)


