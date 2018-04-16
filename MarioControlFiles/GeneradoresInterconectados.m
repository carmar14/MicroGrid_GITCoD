%  Define Plant Model
clear 
close all
clc

R1=100
L1=1
C1=50e-6
R2=100
L2=1
C2=50e-6

R=1000
RL=100
L=1
C=50e-6

Vabc=160
I2=18
F=60


Ap= [-1/(R*C)   1/C        0    -1/C      1/C        0
       -1/L1      -R1/L1   1/L1    0          0         0
          0          -1/C1      0       0          0         0
          1/L          0          0    -RL/L      0         0
       -1/L2          0          0       0     -R2/L2   1/L2
           0            0          0       0     -1/C2       0]
Bp = [    0      0
           0      0
         1/C1   0
            0     0
            0     0
            0    1/C2]
Cp = [    1      0
            0     0
            0     0
            0     0
            0     1
            0     0]'

Dp = zeros(2,2)
CSTR = ss(Ap,Bp,Cp,Dp);
CSTR.InputName = {'Iu1', 'Iu2'};
CSTR.OutputName = {'Vabc','I2'};
CSTR.StateName = {'Vabc', 'I1', 'V1', 'ILabc', 'I2','V2'};
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
plant=CSTR
Ts = 0.1;
p = 3;
m = 1;
mpcobj = mpc(plant, Ts, p, m);

% Specify actuator saturation limits as MV constraints.
mpcobj.MV = struct('Min',{-20;-20},'Max',{20;20},'RateMin',{-100;-100});
% Simulate Using Simulink®

% To run this example, Simulink® is required.
if ~mpcchecktoolboxinstalled('simulink')
    disp('Simulink(R) is required to run this example.')
    return
end

% Simulate closed-loop control of the linear plant model in Simulink. Controller "mpcobj" is specified in the block dialog.
mdl = 'mpc_prueba';
open_system(mdl);
sim(mdl);






