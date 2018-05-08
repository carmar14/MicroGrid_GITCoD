% Este script hace la discretizacion de los controladores en z 
% y asigna los valores a los bloques en simulink para automatizar.


% proporcional y resonante en un mismo cociente
% % % % % % % % % % % % % % % % % % % % % % % % % % % %
%            Kp s^2 + s (Kp wa + Ki ) + Kp w0         %
%  H(s) =  -------------------------------------      % 
%                  s^2  +  s wa  +  w0^2              %
% % % % % % % % % % % % % % % % % % % % % % % % % % % %

% primero se construyen los controladores respectivos en dominio
% continuo.

w0 = 2*pi*60; % frecuencia de la red, que es comun para todos.
Ts=1e-5; % tiempo de muestreo de los controladores discretos.

%%%%%%%%%%%%%%%%%%%%%%%
% PR del BIO
%%%%%%%%
Kb = 2/100; % parte proporcional del control resonante
wab = 20; % ancho de campana para el convertidor bio
Kib = 2; % ganancia integral bio.
Hb_s = tf([ Kb (Kb*wab + Kib) Kb*w0^2], [1 wab w0^2]); % control continuo bio
Hb_z = c2d(Hb_s, Ts,'foh'); % control bio en z.

% se escribe la informacion en el controlador de corriente del biomasa.
set_param('PH1_uGrid_Z/CSI_Control_BIO', 'T', num2str(Ts));
set_param('PH1_uGrid_Z/CSI_Control_BIO', 'A', [ '[' num2str(Hb_z.Numerator{1}) ']' ]);
set_param('PH1_uGrid_Z/CSI_Control_BIO', 'B', [ '[' num2str(Hb_z.Denominator{1}) ']' ]);

%%%%%%%%%%%%%%%%%%%%%%%
% PR diesel
%%%%%%%%
Kd = 2/100; % parte proporcional del control resonante
wad = 20; % ancho de campana para el convertidor bio
Kid = 2; % ganancia integral bio.
Hd_s = tf([ Kb (Kb*wab + Kib) Kb*w0^2], [1 wab w0^2]); % control continuo diesel.
Hd_z = c2d(Hb_s, Ts,'foh'); % control diesel en z.

% se escribe la informacion en el controlador del generador diesel.
set_param('PH1_uGrid_Z/CSI_Control_DIESEL', 'T', num2str(Ts));
set_param('PH1_uGrid_Z/CSI_Control_DIESEL', 'A', [ '[' num2str(Hd_z.Numerator{1}) ']']);
set_param('PH1_uGrid_Z/CSI_Control_DIESEL', 'B', [ '[' num2str(Hd_z.Denominator{1}) ']']);


%%%%%%%%%%%%%%%%%%%%%%%
% PhaseShift D(z)
%%%%%%%%
% funcion de transferencia dentro del bloque de control que realiza un
% desfase de 90 grados. este desfase genera un equivalente a beta
% de la transformacion abc to alpha beta 0 para el caso trifasico y
% asi poder implementar la teoria de potencia instantanea para el caso
% monofasico.
% esta funcion de transferencia es comun al controlador del diesel y
% biomasa.
D_s = tf([2.7e-3 -1], [2.7e-3 1]);
D_z = c2d(D_s, Ts);

set_param('PH1_uGrid_Z/CSI_Control_BIO', 'Dn', [ '[' num2str(D_z.Numerator{1}) ']']);
set_param('PH1_uGrid_Z/CSI_Control_BIO', 'Dd', [ '[' num2str(D_z.Denominator{1}) ']']);

set_param('PH1_uGrid_Z/CSI_Control_DIESEL', 'Dn', [ '[' num2str(D_z.Numerator{1}) ']']);
set_param('PH1_uGrid_Z/CSI_Control_DIESEL', 'Dd', [ '[' num2str(D_z.Denominator{1}) ']']);

% funcion local para escribir una H(z) en un archivo de simulink
function set_z_tf(block_path, param_num, param_den, Hz)
    Num_z = Hz.Numerator{1};
    Den_z = Hz.Denominator{1};
    
    % reset de los valores para evitar error cuando el numerador tiene
    % mayor orden que el denominador.
    set_param(block_path, param_num, '[]');
    set_param(block_path, param_den, '[]');
    
    set_param(block_path, param_den, ['[' num2str(Den_z) ']' ]);
    set_param(block_path, param_num, ['[' num2str(Num_z) ']' ]);
end

