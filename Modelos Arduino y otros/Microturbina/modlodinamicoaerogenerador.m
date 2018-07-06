clear all
clc
close all

td=0.005;  %Tiempo de retraso en segundos
A=207; % constante proporcional al valor eficaz de la tension
L=0.006;  %Inductancia del circuito  inducido H
r=0.6;   %Resistencia del inducido ohm
b=12;   % Pendiente de la dependencia entre los parametros N*m*s
Jg=32*10*exp(-4);  %Momento de inercia del motor kg*m^2
Je=210;  %Momento de inercia de la turbina kg*m^2
m=15;    %Relacion de transmision wg/we
f=1.2*10*exp(-3);  %Coeficiente de friccion viscoso N*m*S
k=1;


Jt=Jg+Je/m;

ft=f+b/(m*m);

%Funciones de tranferencias
num=-A*[1 -2/td];
den=[L r];
den2=[1 2/td];
G=tf(num,den);
G1=G*tf(1,den2);
G2=tf(k,[Jt ft]);
G1la=tf([-166.667 166.667*400],[1 500 400*100]);
G2la=tf(1,[0.94 0.0545]);

figure
step(G1la);
figure
step(G2la);
figure
step(G1);