% para implementar el controlador mpc es necesario dispone de un modelo
% del sistema que se desea controlar. En este caso el sistema recive un set
% point de potencia para biogenerador y para diesel. ambos casos un vector
% de dos componentes [P,Q]. la salida es la potencia real medida que
% aportan los convertidores. es decir que la entrada es [Pb, Qb, Pd, Qd]
% y la salida es [Pob, Qob, Pod, Qod].
% 
% debido a la naturaleza de los bloques empleados para el calculo de
% potencia instantanea no fue posible obtener una linealizacion de la
% planta usando Linear analysis de simulink.
% 
% para construir un modelo lineal del sistema en variables de estado se usa
% este script, el cual  ejecuta de manera automatica la simulacion de
% simulink de esta carpeta, la cual envia las curvas al work space. una vez
% con las curvas en el workspace se hace un ajuste parametrico.

disp('iniciando parametros...')

slx = 'pqFitting'; % nombre del modelo de simulink para construir las curvas

% bloques de step functions de simulink. (las entradas de potencia).
Pib_blk = [slx '/Pi_bio'];
Qib_blk = [slx '/Qi_bio'];
Pid_blk = [slx '/Pi_diesel'];
Qid_blk = [slx '/Qi_diesel'];

% celda con los nombres de los bloques step para poner los setpoints de
% potencia. se agrupan en celda para que sea mas compacto el manejo.
BLK_IN = {Pib_blk, Qib_blk, Pid_blk, Qid_blk};

% PQ set point para obtener los datos para el ajuste.
Pv_fitting = [100, 1000, 300, 1500];

% set points de potencia para obtener los datos de validacion
Pv_val1 = [500, 500, 100, 2500];
Pv_val2 = [300, 3000, 700, 500];
Pv_val3 = [500, 4000, 500, 4000];

SET_INPUTS(BLK_IN, Pv_fitting);
disp('iniciando simulacion para datos de ajuste...')
sim(slx);

Do = [Po_bio.Data, Qo_bio.Data, Po_diesel.Data, Qo_diesel.Data];
Di = [Pi_bio.Data, Qi_bio.Data, Pi_diesel.Data, Qi_diesel.Data];
fit_set = build_set(Do, Di);

disp('Estimando modelo en variables de estado...')
SSpq = ssest(fit_set, 12);


disp('ejecutando simulacines para datos de validacion...')


disp('graficando curvas para comparar calidad del modelo...')


% funcion local para establecer los steps de potencia activa y reactiva de
% disel y biomasa.
function SET_INPUTS(BLK_IN, Pv)
    set_param(BLK_IN{1}, 'After', num2str(Pv(1)));
    set_param(BLK_IN{2}, 'After', num2str(Pv(2)));
    set_param(BLK_IN{3}, 'After', num2str(Pv(3)));
    set_param(BLK_IN{4}, 'After', num2str(Pv(4)));
end

% funcion local para agrupar los datos de simulacion de una forma compacta
% y conveniente para la obtencion de modelos lineales.
% ver docs: https://la.mathworks.com/help/ident/gs/identify-linear-models-using-the-command-line.html
function y = build_set(Do, Di)
    r = iddata(Do, Di, 1e-4);
    r.InputUnit = {'W', 'VAR', 'W', 'VAR'};
    r.OutputUnit = {'W', 'VAR', 'W', 'VAR'};
    r.InputName = {'Pi_bio', 'Qi_bio', 'Pi_diesel', 'Qi_diesel'};
    r.OutputName = {'Po_bio', 'Qo_bio', 'Po_diesel', 'Qo_diesel'};
    y = r;
end
