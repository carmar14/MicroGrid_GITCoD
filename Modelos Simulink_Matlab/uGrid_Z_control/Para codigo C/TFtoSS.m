clear
close all
clc
A=[1 2; 3 4];
B=[1 0; 2 3];
C=[1 0; 0 1];
D=zeros(2);
[num1 den1]=ss2tf(A,B,C,D,1)
[num2 den2]=ss2tf(A,B,C,D,2)

%Paso contrario

[a1 b1 c1 d1]=tf2ss(num1,den1)
[a1 b1 c1 d1]=tf2ss(num2,den1)
% [a2 b2 c2 d2]=tf2ss(num1(2,:),den1)
% [a3 b3 c3 d3]=tf2ss(num2(1,:),den2)
% [a4 b4 c4 d4]=tf2ss(num2(2,:),den2)