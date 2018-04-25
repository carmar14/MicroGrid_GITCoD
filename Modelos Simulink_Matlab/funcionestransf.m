
clear 
close all
clc
load('simulink2tf.mat')
H = tf(linsys1);
n11=cell2mat(H.Numerator(3,1));
n12=cell2mat(H.Numerator(3,2));
n13=cell2mat(H.Numerator(3,3));
d11=cell2mat(H.Denominator(3,1));
d12=cell2mat(H.Denominator(3,2));
d13=cell2mat(H.Denominator(3,3));
H1=tf(n11,d11)+tf(n12,d12)+tf(n13,d13);
step(H1)





