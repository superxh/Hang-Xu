% USB_Data_Display
%
% Script to display a clock of data collected from a PIC18F27K40 via a USB interface
%
% Phil Atkins

clear;
    
ADC_Sampling_Rate = 30e3;       % PIC18F27K40 was programmed to collect data at a 30 kHz rate
ADC_Sampling_Points = 1024;     % PIC18F27K40 was programmed to collect 1024 samples of data

% Generate indeces for later display purposes
DisplayTime_ms = 1000*(0:(ADC_Sampling_Points-1))./ADC_Sampling_Rate;                                   % Time value of each sample in ms
DisplayFrequency_kHz = ADC_Sampling_Rate.*(0:(ADC_Sampling_Points-1))./ADC_Sampling_Points ./ 1000;     % Frequency value of each transformed sample in kHz

% Configure port
% Check comms port on Windows control panel for com port number
COM_Port = 'COM12';     % This com port number will vary from machine-to=machine
COM_Baud = 9600;

% ***** Note: Terminator can be 'CR','LF','CR/LF','LF/CR' and must match your C code 
RS232_Object = serial(COM_Port,'BaudRate',COM_Baud,'DataBits',8,'Parity','none','StopBits',2,'FlowControl','none','Terminator','LF/CR');

fopen(RS232_Object);
% fopen will throw a Matlab error if the port is not available, a typical error message will be:
% Error using serial/fopen (line 72)
% Open failed: Port: COM12 is not available. Available ports: COM3, COM4, COM5, COM6, COM7.

%% Send commands using fwrite
for SnapShotIndex = 1:20
    % Send command to start data collection
    Command = ['ADC' char(13)];             % Send 'ADC' command string with a defined terminator character
    fwrite(RS232_Object,Command,'int8');
    
    % Wait for a message back from PIC18F27K40
    ReturnedString = fscanf(RS232_Object);
    if ReturnedString ~= char([79, 75, 10, 13])
        fprintf('Comms Error - no terminator.   ASCII codes = %d\n',double(ReturnedString))
    end
    
    % Recover the data collected by the ADC
    DataSnapShot = zeros(1,ADC_Sampling_Points);            % Reserve storage
    for SampleIndex = 1:ADC_Sampling_Points
        ReturnedString = fscanf(RS232_Object);              % This may be an empty string causing the following lines to crash
        ReturnedSampleValue = str2double(ReturnedString);   % This is done in multiple lines to ease debugging
        DataSnapShot(SampleIndex) = ReturnedSampleValue;
    end
    
    % Display the data in the time domain
    Figure1Handle = figure(1);
    Figure1Handle.Color = 'w';
    plot(DisplayTime_ms,DataSnapShot,'k','LineWidth',1.5);
    xlabel('Time (ms)');
    ylabel('Sample Value');
    title('Raw Data Time Domain');
    
    % Transform data to the frequency domain
    DataSnapShotFFT = fft(DataSnapShot);
    DataSnapShotFFTdB = 20*log10(abs(DataSnapShotFFT));
    
    % Display the data in the time domain
    Figure2Handle = figure(2);
    Figure2Handle.Color = 'w';
    plot(DisplayFrequency_kHz,DataSnapShotFFTdB,'k','LineWidth',1.5);
    xlim([0 ADC_Sampling_Rate/2000]);
    xlabel('Frequency (kHz)');
    ylabel('Spectral Value (dB re 1 bit)');
    title('Raw Data Frequecy Domain');
    
end
%% Unless the port is closed and released back to Windows, this code cannot be run again
% Should the script crash with the port open, run this section alone
% In many cases, you will have to restart Matlab
fclose(RS232_Object);