% este script es ejecutado al momento de ejecutar el modelo de simulink de
% la microgrid de esta carpeta.
% En la seccion de configuracion de simulink, En la pestaña de callBacks se
% configuran los scripts que se desean ejectar al incio, durante o al
% final de la simulacion.
clear
close all
clc
% se cargan las matrices dinamicas del MPC DMC.
load('DMC_matrices');

% se carga la libreria de true time.
%run('truetime-2.0\init_truetime');




%  Parámetros Motor Diesel

K1=1.15; K2=1; K3=1; Tao1=0.5; Tao2=0.125; J=0.3; P=0.1;

H_AM = tf([K1*(K2*K3)],[Tao2 1],'IODelay', Tao1); % Dinámica Actuador - Motor
H_AM_d = c2d(H_AM,0.01,'tustin')

H_E = tf([J*P],[1 (J*P)]); % Dinámica Eje
H_E_d = c2d(H_E,0.01,'tustin')

%MPC BIO

C1=22e-6;
C2=C1;
C3=610e-6;
C6=2000e-6;
C=C1+C2+C3+C6;
R1=0.1;
R2=R1;
R3=1e-3;
R4=10;
R5=10;
L1=40e-3;
L2=30e-3;
L3=5e-3;
L4=5.2;
Ab= [-R1/L1 0 0 0 -1/L1
     0 -R2/L2 0 0 -1/L2
     0 0 -R3/L3 0 -1/L3
     0 0 0 -R5/L4 1/L4
     1/C 1/C 1/C -1/C -1/R4];
Bb = [1/L1 0 0 
     0 1/L2 0
     0 0 1/L3
     0 0 0
     0 0 0];
Cb = [1 0 0 0 0
      0 0 0 0 1];

Db = zeros(2,3);
CSTR = ss(Ab,Bb,Cb,Db);
CSTR.InputName = {'u1', 'u2','u3'};
CSTR.OutputName = {'Ibio','Vout'};
CSTR.StateName = {'Ibio', 'Idie', 'Ipv', 'I5', 'Vout'};
CSTR

%  Design MPC Controller

%   MPCOBJ = mpc(PLANT,TS,P,M) specifies the control horizon, M. M is
%   either an integer (<= P) or a vector of blocking factors such that
%   sum(M) <= P.
%   MODELS.Plant = plant model (LTI or IDMODEL)
%         .Disturbance = model describing the input disturbances.
%                           This model is assumed to be driven by unit
%                          variance white noise.
%            .Noise = model describing the plant output measurement noise.
%                           This model is assumed to be driven by unit
%                          variance white noise.
%            .Nominal = structure specifying the plant nominal conditions
%                             (e.g., at which the plant was linearized).

% Create the controller object with sampling period, prediction and control horizons:
plant=CSTR;
Ts = 1e-4;
p = 3;
m = 1;
mpcobj = mpc(plant, Ts, p, m);

% Specify actuator saturation limits as MV constraints.
mpcobj.MV = struct('Min',{-200;-200},'Max',{200;200},'RateMin',{-100;-100});
% Simulate Using Simulink®

% To run this example, Simulink® is required.
if ~mpcchecktoolboxinstalled('simulink')
    disp('Simulink(R) is required to run this example.')
    return
end