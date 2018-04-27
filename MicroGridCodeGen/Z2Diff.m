Numz=H1d.Numerator{1};
Denz=H1d.Denominator{1};


U = zeros(length(Numz), 1);
Y = zeros(length(Denz), 1);



t  =0:Ts:.2;
nn = 1;

u = 10*sin(2*pi*60*t);

ym = zeros(length(t), 1);


for n=0:Ts:.2

    U(1) = u(nn);
    
    Ycu = 0;
    Ycy = 0;
    
    for i=1:1:length(Numz)
        Ycu = (U(i)*Numz(i)) + Ycu;
    end

    for i=2:1:length(Denz)
        Ycy = ( Y(i)*-Denz(i) ) + Ycy;
    end

    Y(1) = Ycu + Ycy;



    for i=length(Numz):-1:2
        U(i)=U(i-1);
    end


    for i=length(Denz):-1:2
        Y(i)=Y(i-1);
    end
    ym(nn) = Y(1);
    nn = nn+1;
end

