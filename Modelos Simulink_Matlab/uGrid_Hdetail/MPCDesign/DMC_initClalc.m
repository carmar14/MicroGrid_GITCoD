% la implementacion del control MPC con DMC (dynamic matrix control)
% requiere del calculo de unas matrices dinamicas paera la respuesta
% forzada y la respuesta libre. Estas matrices se pueden calcular offline
% previo al inicio de funcionamiento del MPC. las matrices dinamicas se
% contruyen con el modelo de convolucion del sistema que se desea controlar
% (el DMC emplea la respuesta al impulso)



























%Nota:
% esto no tiene que ver con el algoritmo DMC, simplemente deseo anotar el
% resultado de un proceso algebraico de otra cosa en este script antes de
% que se me olvide.
% 
% resultado de adaptar el modelo de prediccion sin perturbaciones
% proveniente del state space model discreto generico al problema de
% de programacion cuadratica estandar: min: x' Q x +f' x .
% U'H'H U + (-2 r' H + 2 G' x H ) U
% Q = H'H 
% f' =  (-2 r' H + 2 G' x H )'
