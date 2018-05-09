function [ output_args ] = c_BIO( input_args )

% funcion que ejecuta la logica del bloque True Time Kernel.
ex = 0; % variable auxiliar para poner el tiempo de ejecucion.
switch segment
    case 1 % primer segemento.
        % se hacen las lecturas de las entradas del ttkernel
        I = ttAnalogIn(1); % corriente medida del convertidor
        V = ttAnalogIn(2); % Tension medida del convertidor
        p = ttAnalogIn(3); % set point de potencia actica del mpc 
        q = ttAnalogIn(4); % set point de potencia reactiva del mpc
        
        % se hace el defase de la tension.
        
        %
        
        % se hace el desfase de la corriente
        
        %
        
        % se calcula la accion de control
        
        %
        
        % se miden las potencias p y q.
        
        
        %
        ex = data.exectime;
        data.d = sin(y*2*pi*2);
        data.Po = 0;
        data.Qo = 0;
        
    case 2
        % se ponen las salidas en el DAC.
        ttAnalogOut(1, data.d);
        ttAnalogOut(2, data.Po);
        ttAnalogOut(3, data.Qo);
        ex = -1;
end

% se pone el tiempo de ejecucion. Es un requisito indispensable
% del bloque true time.
exectime=ex;


end

