
% calculo del controlador MPC

%se carga el state space model desde linear analysis simulink
load('statespaceModel_2Inverters_prver.mat');

A = linsys1.A;
B = linsys1.B;
C = linsys1.C;
D = linsys1.D;

CSTR = ss(A,B,C,D);
CSTR.InputName = {'G1', 'G2'};
CSTR.OutputName = {'VL','I_G2'};
CSTR.StateName = {'X1', 'X2', 'X3', 'X4', 'X5','X6','X7','X8'};


% Create the controller object with sampling period, prediction and control horizons:
plant=CSTR;
Ts = 1e-3;
p = 3;
m = 1;
mpcobj = mpc(plant, Ts, p, m);


% Specify actuator saturation limits as MV constraints.
%mpcobj.MV = struct('Min',{-20;-20},'Max',{20;20},'RateMin',{-100;-100});
% Simulate Using Simulink®


% en caso de que hayan estdos no observables este comando
% transforma el modelo para evitar este problema
mpcobj.Model.Plant = minreal(mpcobj.Model.Plant);
