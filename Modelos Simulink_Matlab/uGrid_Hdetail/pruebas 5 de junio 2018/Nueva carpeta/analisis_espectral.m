clear 
close all
clc
Ts=1e-4;
Fs=1/Ts;
load('caso1.mat');
load('caso2.mat');
load('caso4.mat');
t=caso1I.Time;

%Analisis de Fourier caso 1
subplot(4,3,1)
c1I=caso1I.Data;
c1V=caso1V.Data;
L=length(c1I);
plot(t,c1I,t,c1V)
legend('Corriente en la carga', 'Voltaje en la carga')
title('Comportamiento en la carga')
xlabel('Tiempo(s)')
fc1I=abs(fft(c1I));
fc1I=fc1I/max(fc1I);
Fc1I=fc1I(1:L/2+1);
Fc1I(2:end-1) = Fc1I(2:end-1);
fc1V=abs(fft(c1V));
fc1V=fc1V/max(fc1V);
Fc1V=fc1V(1:L/2+1);
Fc1V(2:end-1) = Fc1V(2:end-1);
f=Fs*(0:(L/2))/L;
f1=f;
subplot(4,3,2)
plot(f,Fc1I)
title('Análisis de la corriente en frecuencia')
subplot(4,3,3)
plot(f,Fc1V)
title('Análisis de la tensión en frecuencia')

%Analisis de Fourier caso 2
subplot(4,3,4)
c2I=case2I.Data;
c2V=case2V.Data;
L=length(c2I);
plot(t,c1I,t,c2V)
legend('Corriente en la carga', 'Voltaje en la carga')
title('Comportamiento en la carga')
xlabel('Tiempo(s)')
fc2I=abs(fft(c2I));
fc2I=fc2I/max(fc2I);
Fc2I=fc2I(1:L/2+1);
Fc2I(2:end-1) = Fc2I(2:end-1);
fc2V=abs(fft(c2V));
fc2V=fc2V/max(fc2V);
Fc2V=fc2V(1:L/2+1);
Fc2V(2:end-1) = Fc2V(2:end-1);
f=Fs*(0:(L/2))/L;
f2=f;
subplot(4,3,5)
plot(f,Fc2I)
title('Análisis de la corriente en frecuencia')
subplot(4,3,6)
plot(f,Fc2V)
title('Análisis de la tensión en frecuencia')

% %Analisis de Fourier caso 3
% subplot(4,3,7)
% c3I=case3I.Data;
% c3V=case3V.Data;
% L=length(c3I);
% plot(t,c3I,t,c3V)
% legend('Corriente en la carga', 'Voltaje en la carga')
% title('Comportamiento en la carga')
% xlabel('Tiempo(s)')
% fc3I=abs(fft(c3I));
% fc3I=fc3I/max(fc3I);
% Fc3I=fc3I(1:L/2+1);
% Fc3I(2:end-1) = Fc3I(2:end-1);
% fc3V=abs(fft(c3V));
% fc3V=fc3V/max(fc3V);
% Fc3V=fc3V(1:L/2+1);
% Fc3V(2:end-1) = Fc3V(2:end-1);
% f=Fs*(0:(L/2))/L;
% subplot(4,3,8)
% plot(f,Fc3I)
% title('Análisis de la corriente en frecuencia')
% subplot(4,3,9)
% plot(f,Fc3V)
% title('Análisis de la tensión en frecuencia')

%Analisis de Fourier caso 4
subplot(4,3,10)
c4I=Case4I.Data;
c4V=Case4V.Data;
L=length(c4I);
plot(t(1:L),c4I,t(1:L),c4V)
legend('Corriente en la carga', 'Voltaje en la carga')
title('Comportamiento en la carga')
xlabel('Tiempo(s)')
fc4I=abs(fft(c4I));
fc4I=fc4I/max(fc4I);
Fc4I=fc4I(1:L/2+1);
Fc4I(2:end-1) = Fc4I(2:end-1);
fc4V=abs(fft(c4V));
fc4V=fc4V/max(fc4V);
Fc4V=fc4V(1:L/2+1);
Fc4V(2:end-1) = Fc4V(2:end-1);
f=Fs*(0:(L/2))/L;
f4=f;
subplot(4,3,11)
plot(f,Fc4I)
title('Análisis de la corriente en frecuencia')
subplot(4,3,12)
plot(f,Fc4V)
title('Análisis de la tensión en frecuencia')

close all

figure
plot(caso1I)
hold on
plot(case2I)
% plot(case3I)
plot(Case4I)
% legend('Caso 1','Caso 2','Caso 3','Caso 4')
legend('Normal','Caso 1','Caso 2')
title('Corriente en la Carga')
xlabel('t(s)')
ylabel('Corriente(A)')
axes('position',[.65 .175 .25 .25])
box on
zonaInte=(t<4.2)&(t>=4);
hold on
plot(t(zonaInte),c1I(zonaInte),t(zonaInte),c2I(zonaInte),t(zonaInte),c4I(zonaInte));
ylim([-210 210])

figure
plot(caso1V)
hold on
plot(case2V)
% plot(case3V)
plot(Case4V)
% legend('Caso 1','Caso 2','Caso 3','Caso 4')
legend('Normal','Caso 1','Caso 2')
title('Tensión en la Carga')
xlabel('t(s)')
ylabel('Tensión(V)')
axes('position',[.65 .175 .25 .25])
box on
zonaInte=(t<4.2)&(t>=4);
hold on
plot(t(zonaInte),c1V(zonaInte),t(zonaInte),c2V(zonaInte),t(zonaInte),c4V(zonaInte));
ylim([-210 210])

figure
plot(caso1V)
% legend('Caso 1','Caso 2','Caso 3','Caso 4')

title('Tensión en la Carga')
xlabel('t(s)')
ylabel('Tensión(V)')
axes('position',[.65 .175 .25 .25])
box on
zonaInte=(t<4.2)&(t>=4);
hold on
plot(t(zonaInte),c1V(zonaInte));
ylim([-210 210])

figure
plot(caso1I)
% legend('Caso 1','Caso 2','Caso 3','Caso 4')

title('Corriente en la Carga')
xlabel('t(s)')
ylabel('Corriente(A)')
axes('position',[.65 .175 .25 .25])
box on
zonaInte=(t<4.2)&(t>=4);
hold on
plot(t(zonaInte),c1I(zonaInte));
ylim([-210 210])


figure
plot(f1,Fc1I,f2,Fc2I,f4,Fc4I)
title('Análisis en Frecuencia de la Corriente en la Carga')
xlabel('f(Hz)')
ylabel('|I(f)|')
axes('position',[.65 .175 .25 .25])
box on
zonaInte=(f1<300)&(f1>0);
hold on
plot(f1(zonaInte),Fc1I(zonaInte),f2(zonaInte),Fc2I(zonaInte),f4(zonaInte),Fc4I(zonaInte));
ylim([0 0.02])
legend('Normal','Caso 1','Caso 2')

figure
plot(f1,Fc1V,f2,Fc2V,f4,Fc4V)
title('Análisis en Frecuencia de la Tensión en la Carga')
xlabel('f(Hz)')
ylabel('|V(f)|')
axes('position',[.65 .175 .25 .25])
box on
zonaInte=(f1<300)&(f1>0);
hold on
plot(f1(zonaInte),Fc1V(zonaInte),f2(zonaInte),Fc2V(zonaInte),f4(zonaInte),Fc4V(zonaInte));
ylim([0 0.1])
legend('Normal','Caso 1','Caso 2')


