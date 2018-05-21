

p=100;
Nu=100;

Du = [ones(Nu,1); ones(Nu,1)];

ym = [ ones(p, 1)*100; ones(p, 1)*1000 ]; % vector de la medida de tempearatura actual.

w = [ ones(p, 1)*200; ones(p, 1)*2500 ]; % vector señal setpoint.

H = G'*G;

L = GF*Du+ym; % respuesta libre.

F = 2*(L-w)'*G; % parte lineal del problema qp.

% duv = quadprog(H, F);

duv = quadprog(H, F, zeros(200,200), zeros(200, 1), zeros(200,200), zeros(200, 1), -ones(200, 1)*100, ones(200, 1)*100 );