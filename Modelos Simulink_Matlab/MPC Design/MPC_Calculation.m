
% calculo del controlador MPC

%se carga el state space model desde linear analysis simulink
%load('statespaceModel_2Inverters_prver.mat');

A = sis.A;%linsys1.A;
B = sis.B;%linsys1.B;
C = sis.C;%linsys1.C;
D = sis.D;%linsys1.D;

CSTR = ss(A,B,C,D);
CSTR.InputName = {'Pr1','Qr1','Pr2','Qr2'};
CSTR.OutputName = {'P1','Q1','P2','Q2'};
CSTR.StateName = {'X1', 'X2', 'X3', 'X4'};


% Create the controller object with sampling period, prediction and control horizons:
plant=CSTR;
Ts = 30e-3;
p = 100;
m = 80;
mpcobj = mpc(plant, Ts, p, m);


% Specify actuator saturation limits as MV constraints.
%mpcobj.MV = struct('Min',{-20;-20},'Max',{20;20},'RateMin',{-100;-100});
% Simulate Using Simulink®


% en caso de que hayan estdos no observables este comando
% transforma el modelo para evitar este problema
mpcobj.Model.Plant = minreal(mpcobj.Model.Plant);
