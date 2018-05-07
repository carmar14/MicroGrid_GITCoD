
k1=1.023;
tao1=0.02;

k2=0.996;
tao2=0.025;

k3=1.0265;
tao3=0.022;

k4=0.997;
tao4=0.02;

ft1=tf(k1,[tao1 1]);
ft2=tf(k2,[tao2 1]);
ft3=tf(k3,[tao3 1]);
ft4=tf(k4,[tao4 1]);

fT=[ft1 zeros(1,3); 0 ft2 zeros(1,2);zeros(1,2) ft3 0;zeros(1,3) ft4];


sis=ss(fT);


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
p = 10;
m = 8;
mpcobj = mpc(plant, Ts, p, m);


% Specify actuator saturation limits as MV constraints.
mpcobj.MV = struct('Min',{0;0;0;0},'Max',{700;5000;700;5000},'RateMin',{ones(4, 1)*-2000}, 'RateMax',{ones(4, 1)*2000});
% Simulate Using Simulink®


% en caso de que hayan estdos no observables este comando
% transforma el modelo para evitar este problema
mpcobj.Model.Plant = minreal(mpcobj.Model.Plant);

clearvars -except mpcobj;