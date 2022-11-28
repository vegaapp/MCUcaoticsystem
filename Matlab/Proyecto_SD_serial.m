%Función que toma datos por un puerto serial y los grafica por medio de la

%son 228 muestras por segundo
clear all;
seg=61;
muestras=228*seg;

close all;
clc;
voltaje=0; %Declara variable en la cual se van a guardar los valores
estado='';
x=[];
y=[];
z=[];
i=0;


%Borra datos que se encuentren previos y vuelve a declarar el puerto y la
%velocidad de transmisión
delete(instrfind({'port'},{'COM4'})); 
puerto=serial('COM4');
puerto.BaudRate=115200;

fopen(puerto);%abre el puerto a utilizar
contador=0;

%configura la ventana donde se va a mostrar la grafica
% figure('Name','Grafica voltaje');
% 
% title('ECUACIONES DE LORENZ');
% xlabel('Numero de Muestras');
% ylabel('Voltaje (V)');
% grid off;
% hold on;

%Ciclo para ir realizando la grafica paso a paso

while i<=muestras
%     ylim([-200 200]); %Limites del eje y
%     xlim([0 i+50]); %Limites del eje x
    contador=contador+1;
    valorADC=fscanf(puerto,'%s'); %Toma el valor recibido por el puerto y lo guarda en la variable
%     voltaje(contador)=valorADC(1)*5/1024; %Hace la conversión a voltaje
%     plot(voltaje); %Grafica el voltaje
    if isempty(valorADC)==0

        if valorADC(1,1)=='A' && length(valorADC)==1
            estado='A';
            i=i+1;
            tic
        end
            
        if valorADC(1,1)=='B' && length(valorADC)==1
            estado='B';
        end
            
        if valorADC(1,1)=='C' && length(valorADC)==1
            estado='C';
        end
        
        if (valorADC(1,1)~='B' && estado=='A')
            x(i)=str2double(valorADC);
        end
        
        if (valorADC(1,1)~='C' && estado=='B') 
            y(i)=str2double(valorADC); 
        end
            
        if estado=='C' %&& str2double(valorADC)~=0 
            toc
            z(i)=str2double(valorADC);
%             plot(x,'r'); %Grafica x
%             plot(y,'b'); %Grafica x
%             plot(z,'g'); %Grafica x
%             drawnow
            i
            
        end
        

    end
        
   

    
end
%cierra y borra el puerto utilizado, borra todas las variables utilizadas
fclose(puerto);
delete(puerto);

%%
figure;
subplot(3,2,1)% 2 files % col, pos 1
plot(x(1:end-1))
title('x data')
subplot(3,2,2)% 2 files % col, pos 2
plot(y)
title('y data')
subplot(3,2,3)
plot(z)
title('z data')
subplot(3,2,4)
plot(x(1:end-1),y)
title('x vs y')
subplot(3,2,5)
plot(x(1:end-1),z)
title('x vs z')
subplot(326)
plot(y,z)
title('y vs z')
%% --------------- plot 3d
figure(3);
plot3(x(1:end-1),y,z, 'o')
xlabel('x data') 
ylabel('y data') 
zlabel('z data') 
title('3D Lorenz Graph')
