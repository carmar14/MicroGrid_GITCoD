function [ output_args ] = tttest( input_args )

%Funcion de inicializacion del controlador BIO con true time kernel.

ttInitKernel('prioFP') % comando necesesario y debe ser llamado primero
% para la inicializacion del true time kernel block
% prioFP significa fixed-Priority scheduling.

data.exectime = 1e-6;   % control task execution time
starttime = 0.0;       % control task start time
period = .1;          % control task period

ttCreatePeriodicTask('ctrl_task', starttime, period, 'BIO_c', data)
end
