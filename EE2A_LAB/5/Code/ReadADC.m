clear;

ADC_Sampling_Rate = 32e3;
ADC_Sampling_Points = 128;

DisplayTime_ms = 1000*(0:(ADC_Sampling_Points-1))./ADC_Sampling_Rate;
DisplayFrequency_kHz = ADC_Sampling_Rate.*(0:(ADC_Sampling_Points-1))./ADC_Sampling_Points ./ 1000;

COM_Port = 'COM3';
COM_Baud = 9600;

RS232_Object = serial(COM_Port,'BaudRate',COM_Baud,'DataBits',8,'Parity','none','StopBits',1,'FlowControl','none','InputBufferSize',1024,'OutputBufferSize',1024,'Terminator',char(93));

fopen(RS232_Object);

Command = ['collect data' char(13)];
fwrite(RS232_Object,Command,'int8');

ReturnedString = fscanf(RS232_Object);

fclose(RS232_Object);

ReturnedTableString = ReturnedString(20:end);
ReturnedTable = str2num(ReturnedTableString);

t = (0:ADC_Sampling_Points-1)/ADC_Sampling_Rate;

X = ReturnedTable;

Local1_real=round(64*cos(2*pi*1000*t));
Local1_imag=round(-64*sin(2*pi*1000*t));
Local2_real=round(64*cos(2*pi*2000*t));
Local2_imag=round(-64*sin(2*pi*2000*t));

plot(t,X)
title('Signal')
xlabel('t (milliseconds)')
ylabel('X(t)')

Multi_1coscos=Local1_real.*X;
Multi_1cossin=Local1_imag.*X;
Multi_2coscos=Local2_real.*X;
Multi_2cossin=Local2_imag.*X;

Filter_Multi_1coscos=0;
Filter_Multi_1cossin=0;
Filter_Multi_2coscos=0;
Filter_Multi_2cossin=0;

for a=1:1:96
    Filter_Multi_1coscos(a)= (sum(Multi_1coscos(a:a+31)));
    Filter_Multi_1cossin(a)= (sum(Multi_1cossin(a:a+31)));
    Filter_Multi_2coscos(a)= (sum(Multi_2coscos(a:a+31)));
    Filter_Multi_2cossin(a)= (sum(Multi_2cossin(a:a+31)));  
end
a = sum(Filter_Multi_1coscos(1:96))/96/65536/2;
b = sum(Filter_Multi_1cossin(1:96))/96/65536/2;
c = sum(Filter_Multi_2coscos(1:96))/96/65536/2;
d = sum(Filter_Multi_2cossin(1:96))/96/65536/2;

a
b
c
d
