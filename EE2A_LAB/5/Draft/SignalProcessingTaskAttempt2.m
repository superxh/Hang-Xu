clk = 1;
 SamplingFrequency = 16e3; %Microprocessor A/D sampling frequency%
 DataBlockSize = 2^14; %We will process the data in blocks%
 TX_Frequency_1 = 1000; %First Transmission Frequency%
 TX_Frequency_2 = 2000; %Second Transmission Frequency%
 Osc_Frequency = 1010;
 DisplayTime = (0:(DataBlockSize-1))/SamplingFrequency; %Make an Array of samples correspondsing to the sampling time%

 
for clk = 1:5
    
    TransmissionSignal = cos(2*pi*TX_Frequency_1*(DisplayTime)) + cos(2*pi*TX_Frequency_2*(DisplayTime));
    TransmissionSignal2 = cos(2*pi*Osc_Frequency*DisplayTime);
    TransmissionSignal = -TransmissionSignal;
    Signal3 = TransmissionSignal + TransmissionSignal2;

    Figure1Handle = figure(1);
    Figure1Handle.Color = 'w';
    plot(DisplayTime,TransmissionSignal, 'k',DisplayTime,TransmissionSignal2, 'b');
    set(gca, 'FontSize',11,'linewidth',1.5);
    xlabel('Time (S)','FontSize',11,'FontWeight','demi')
    ylabel('Voltage (V)','FontSize',11,'FontWeight','demi')
    title('Transmission Signal','FontSize',11,'FontWeight','demi');
    ylim([-2.05,2.05]);
    xlim([0,5e-3]);
    pause(1);
    Figure2 = figure(2);
    Figure2.Color = 'w';
    plot(DisplayTime,Signal3);
    
end