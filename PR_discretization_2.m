%discretization script

st_time=10e-3; % variables necesarias
st_time2=20e-3; % para los contactores
st_time3=40e-3; % en la simulacion

% estos tiempos corresoponden al tiempo
% que estos contactores estaran abiertos
% una vez finalizado este tiempo los
% contactores conducen, lo que permite la 
% simulacion normalmente. ver comentarios
% en simulink para mas informacion




%------------------
% el proceso de discretizacion es muy similar
% al que se muestra en los cursos de control
% en a UAO. La unica particularidad a tener 
% en cuenta es que el metodo de discretizacion
% debe ser foh (aproximacion triangular).
% deacuerdo a un paper en la IEEE que revise,
% este tipo de discretizacion es el que menos
% desplaza la campana de resonancia del
% control resonante de continuo a discreto.

w0c = 60*2*pi;
wnc = 15;

prNum = [1 0];
prDen = [1 wnc w0c^2];

prHs = tf(prNum, prDen);

%disp('-------------------------------------------------------')
%pretty(PRss)


Ts = .25e-4; 

%%c2d(PRtf, Ts)
PRz = c2d(prHs, Ts, 'foh')
A = PRz.num{1};
B = PRz.den{1};


PQint = c2d(tf([1], [1 0]), Ts, 'foh')

Apq = PQint.num{1};
Bpq = PQint.den{1};