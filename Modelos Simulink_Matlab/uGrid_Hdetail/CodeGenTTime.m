% Este script hace la inicializacion del modelo de la microred
% con el mas alto nivel de detalle.
% 
% primero se parte de los parametros de los controladores en su version
% continua. Estos se pasan Z deacuerdo al tiempo de muestreo deseado por
% el usuario. Luego se transforman las funciones de transferencia en Z
% a sus correspondientes ecuaciones de diferencias ya implementadas como
% matalab function (se trata de code generation).
% cuando las funciones se generan no es necesario modificar elementos del
% modelo mediante la funcion de matlab set_param, ya que toda la configura
% cion necesria para los bloques true time kernel queda definida por un
% par de archivos, los que son generados en este script para cada bloque.




% proporcional y resonante en un mismo cociente
% % % % % % % % % % % % % % % % % % % % % % % % % % % %
%            Kp s^2 + s (Kp wa + Ki ) + Kp w0         %
%  H(s) =  -------------------------------------      % 
%                  s^2  +  s wa  +  w0^2              %
% % % % % % % % % % % % % % % % % % % % % % % % % % % %

% primero se construyen los controladores respectivos en dominio
% continuo.

w0 = 2*pi*60; % frecuencia de la red, que es comun para todos.
Ts=1e-4; % tiempo de muestreo de los controladores discretos.

%
% %
% % % % % %              % % % % % % %  
%   Generacion funciones en Z        %
% % % % % %              % % % % % % % 
% %
%

%%%%%%%%%%%%%%%%%%%%%%%
% PR BIO, TF en Z
%%%%%%%%
Kb = 2/100; % parte proporcional del control resonante
wab = 20; % ancho de campana para el convertidor bio
Kib = 2; % ganancia integral bio.
Hb_s = tf([ Kb (Kb*wab + Kib) Kb*w0^2], [1 wab w0^2]); % control continuo bio
Hb_z = c2d(Hb_s, Ts,'foh'); % control bio en z.


%%%%%%%%%%%%%%%%%%%%%%%
% PR DIESEL, TF en Z
%%%%%%%%
Kd = 2/100; % parte proporcional del control resonante
wad = 20; % ancho de campana para el convertidor bio
Kid = 2; % ganancia integral bio.
Hd_s = tf([ Kb (Kb*wab + Kib) Kb*w0^2], [1 wab w0^2]); % control continuo diesel.
Hd_z = c2d(Hb_s, Ts,'foh'); % control diesel en z.


%%%%%%%%%%%%%%%%%%%%%%%
% DESFASE 90 GRADOS TF en Z
%%%%%%%%


%
% %
% % % % % % % %                     % % % % % % % % % % 
%    GENERACION CODIGO - ECUACIONES EN DIFERENCIAS    % 
% % % % % % % %                     % % % % % % % % % %
% %
%

% se abre o se crea el archivo out.m y se descarta lo que tenga (si es que existe)
% file = fopen('out.m', 'w+');

% declaracion de variables
token_fname = '$Fn'; % token para reemplazar nombre de la funcion.
token_ftarget = '$Fnt';
Bio_fname = 'BIO_c'; % nombre de la funcion de control del bio.
Diesel_fname = 'DIESEL_c'; % nombre de la funcion de control del diesel.

token_st_time = '$STT'; % para reemplazar el tiempo de arranque del control
token_Ts = '$Ts'; % para reemplazar el tiempo de muestreo del controlador.

% primero se generan las funciones de init de los true time kernel.
F_init_base = ...
    ['function [ output_args ] = $Fn( input_args )\n\n'...
    '%Funcion de inicializacion del controlador BIO con true time kernel.' ...
    'ttInitKernel(''prioFP'') % comando necesesario y debe ser llamado primero' ...
    '% para la inicializacion del true time kernel block' ...
    '% prioFP significa fixed-Priority scheduling.' ...
    'data.exectime = 1e-6;   % control task execution time' ...
    'starttime = $STT;       % control task start time' ...
    'period = $Ts;          % control task period' ...
    'ttCreatePeriodicTask(''ctrl_task'', starttime, period, ''$Fnt'', data)' ...
    'end'];


% cabecera comun a las funciones de control del 
F_header = ...
['function [ output_args ] = $Fn( input_args )\n' ...
'% funcion que ejecuta la logica del bloque True Time Kernel.' ... 
'\nex = 0; % variable auxiliar para poner el tiempo de ejecucion.' ...
'\nswitch segment \n' ...
    '\tcase 1 % primer segemento. \n' ...
        '\t\t% se hacen las lecturas de las entradas del ttkernel \n' ...
        '\t\tI = ttAnalogIn(1); % corriente medida del convertidor \n'
        '\t\tV = ttAnalogIn(2); % Tension medida del convertidor \n' ...
        '\t\t p = ttAnalogIn(3); % set point de potencia actica del mpc \n' ... 
        '\t\t q = ttAnalogIn(4); % set point de potencia reactiva del mpc \n'];
        


% funcion local a la cual se le ingresa una transfer function en z
% y entrega en string el codigo en matlab que la implementa.
% 
% Hz es la funcion de transferencia en z que se convertira en ecuacion
% de diferencias.
% tag es un string que se agrega a las variables del codigo generado
% para distinguir cada variable de manera unica en caso de que 
% se use multiples veces esta funcion para un mismo m-file
function y = write_Equation(Hz, tag)
    % nombres de las variables en el codigo a generar.
    U_name = ['U_' tag];
    Y_name = ['Y_' tag];
    y1_name = ['y1_' tag];
    
    Num = Hz.Numerator{1};
    Den = Hz.Denominator{1};
    
    nn = length(Num);
    nd = length(Den);
    
    % se obtinene la ecuacion en diferencias.
    syms Y(x) U(x) x;
    y = getFVector(Y, x+1, nd);
    u = getFVector(U, x, nn);
    eqy = (sum(u.*Num)-sum(y(2:end).*Den(2:end)))/Den(1);
    eqy_char = strrep(char(eqy), 'x - ', '');
    
    r = ['\n\n %code generation ->' tag '\n'];
    
    % variable persistente vector U (entradas).
    r = [r 'persistent ' U_name ';\n'];
    r = [r 'if isempty(' U_name ')\n'];
    r = [r '\t' U_name ' = zeros(1, ' num2str(nn) ');\n'];
    r = [r 'end\n'];
    % variable persistente vector de salidas Y.
    r = [r 'persistent ' Y_name ';\n'];
    r = [r 'if isempty(' Y_name ')\n'];
    r = [r '\t' Y_name ' = zeros(1, ' num2str(nd-1) ');\n'];
    r = [r 'end\n'];
    
    r = [r 'U = [u ' U_name '(1:end-1)];\n']; % desplazamiento entradas
    r = [r y1_name ' = ' eqy_char ';\n']; % calcula salida actual.
    % desplazamiento vector de salidas.
    r = [r Y_name ' = [' y1_name ' ' Y_name '(1:end-1)];\n'];
    y=r;
end


%funcion local que crea un vector simbolico de una funcion dada
function y = getFVector(v, x, n)
    r = sym(zeros(1, n));
    r(1) = v(x-1);
    for i=2:1:n
        r(i) = v(x-i);
    end
    y = r;
end
