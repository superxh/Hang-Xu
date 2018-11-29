v1 = ['sw(7)','sw(6)','sw(5)','sw(4)','sw(3)','sw(2)','sw(1)','sw(0)','btn(2)','btn(0)','btn(3)','btn(1)']

print('--**Test fraudulent state A transitions**--');
i=0;
while i<12:
    if v1[i] !='sw(5)': # if not the correct key(k2) is pressed
        print('write(TextLine,"Test fraudulent state A*I0I transitions");'+'\n'+
            'writeline(output,TextLine);'+'\n'+
            'sw(7) <= '+"'0'"+';--0'+'\n'+
            'sw(6) <= '+"'0'"+';--1'+'\n'+
            'sw(5) <= '+"'0'"+';--2'+'\n'+
            'sw(4) <= '+"'0'"+';--3'+'\n'+
            'sw(3) <= '+"'0'"+';--4'+'\n'+
            'sw(2) <= '+"'0'"+';--5'+'\n'+
            'sw(1) <= '+"'0'"+';--6'+'\n'+
            'sw(0) <= '+"'0'"+';--7'+'\n'+
            'btn(2) <= '+"'0'"+';--8'+'\n'+
            'btn(0) <= '+"'0'"+';--9'+'\n'+
            'btn(3) <= '+"'0'"+';--R'+'\n'+
            'btn(1) <= '+"'0'"+';--Dr'+'\n'+
            'wait for 20ns;'+'\n'+
            'btn(3) <= '+"'1'"+';'+'\n'+
            'wait for 20ns;'+'\n'+
            'btn(1) <= '+"'1'"+';'+'\n'+
            'write(TextLine,"Forced to State A*I0I, LEDs = ");'+'\n'+
            'write(TextLine,Led(0));'+'\n'+
            'write(TextLine,Led(1));'+'\n'+
            'write(TextLine,Led(2));'+'\n'+
            'write(TextLine," Z = ");'+'\n'+
            'write(TextLine,Led(4));'+'\n'+
            'writeline(output,TextLine);'+'\n'+
            'wait for 20ns;'+'\n'+
            v1[i]+' <= '+"'1'"+';'+'\n'+
            'write(TextLine,"Input fault'+' '+v1[i]+', LEDs = ");'+'\n'+
            'write(TextLine,Led(0));'+'\n'+
            'write(TextLine,Led(1));'+'\n'+
            'write(TextLine,Led(2));'+'\n'+
            'write(TextLine," Z = ");'+'\n'+
            'write(TextLine,Led(4));'+'\n'+
            'writeline(output,TextLine);'+'\n'+
            'wait for 20ns;'+'\n');
    i=i+1;

print('--**Test fraudulent state B transitions**--');
i=0;
while i<12:
    if v1[i] !='sw(3)': # if not the correct key(k4) is pressed
        print('write(TextLine,"Test fraudulent state B*I0I transitions");'+'\n'+
            'writeline(output,TextLine);'+'\n'+
            'sw(7) <= '+"'0'"+';--0'+'\n'+
            'sw(6) <= '+"'0'"+';--1'+'\n'+
            'sw(5) <= '+"'0'"+';--2'+'\n'+
            'sw(4) <= '+"'0'"+';--3'+'\n'+
            'sw(3) <= '+"'0'"+';--4'+'\n'+
            'sw(2) <= '+"'0'"+';--5'+'\n'+
            'sw(1) <= '+"'0'"+';--6'+'\n'+
            'sw(0) <= '+"'0'"+';--7'+'\n'+
            'btn(2) <= '+"'0'"+';--8'+'\n'+
            'btn(0) <= '+"'0'"+';--9'+'\n'+
            'btn(3) <= '+"'0'"+';--R'+'\n'+
            'btn(1) <= '+"'0'"+';--Dr'+'\n'+
            'wait for 20ns;'+'\n'+
            'sw(5) <= '+"'1'"+';'+'\n'+
            'write(TextLine,"Forced to State B*I0I, LEDs = ");'+'\n'+
            'write(TextLine,Led(0));'+'\n'+
            'write(TextLine,Led(1));'+'\n'+
            'write(TextLine,Led(2));'+'\n'+
            'write(TextLine," Z = ");'+'\n'+
            'write(TextLine,Led(4));'+'\n'+
            'writeline(output,TextLine);'+'\n'+
            'wait for 20ns;'+'\n'+
            v1[i]+' <= '+"'1'"+';'+'\n'+
            'write(TextLine,"Input fault'+' '+v1[i]+', LEDs = ");'+'\n'+
            'write(TextLine,Led(0));'+'\n'+
            'write(TextLine,Led(1));'+'\n'+
            'write(TextLine,Led(2));'+'\n'+
            'write(TextLine," Z = ");'+'\n'+
            'write(TextLine,Led(4));'+'\n'+
            'writeline(output,TextLine);'+'\n'+
            'wait for 20ns;'+'\n');
    i=i+1;

print('--**Test fraudulent state C transitions**--');
i=0;
while i<12:
    if v1[i] !='sw(1)': # if not the correct key(k6) is pressed
        print('write(TextLine,"Test fraudulent state C*I0I transitions");'+'\n'+
            'writeline(output,TextLine);'+'\n'+
            'sw(7) <= '+"'0'"+';--0'+'\n'+
            'sw(6) <= '+"'0'"+';--1'+'\n'+
            'sw(5) <= '+"'0'"+';--2'+'\n'+
            'sw(4) <= '+"'0'"+';--3'+'\n'+
            'sw(3) <= '+"'0'"+';--4'+'\n'+
            'sw(2) <= '+"'0'"+';--5'+'\n'+
            'sw(1) <= '+"'0'"+';--6'+'\n'+
            'sw(0) <= '+"'0'"+';--7'+'\n'+
            'btn(2) <= '+"'0'"+';--8'+'\n'+
            'btn(0) <= '+"'0'"+';--9'+'\n'+
            'btn(3) <= '+"'0'"+';--R'+'\n'+
            'btn(1) <= '+"'0'"+';--Dr'+'\n'+
            'wait for 20ns;'+'\n'+
            'sw(5) <= '+"'1'"+';'+'\n'+
            'wait for 20ns;'+'\n'+
            'sw(3) <= '+"'1'"+';'+'\n'+
            'write(TextLine,"Forced to State C*I0I, LEDs = ");'+'\n'+
            'write(TextLine,Led(0));'+'\n'+
            'write(TextLine,Led(1));'+'\n'+
            'write(TextLine,Led(2));'+'\n'+
            'write(TextLine," Z = ");'+'\n'+
            'write(TextLine,Led(4));'+'\n'+
            'writeline(output,TextLine);'+'\n'+
            'wait for 20ns;'+'\n'+
            v1[i]+' <= '+"'1'"+';'+'\n'+
            'write(TextLine,"Input fault'+' '+v1[i]+', LEDs = ");'+'\n'+
            'write(TextLine,Led(0));'+'\n'+
            'write(TextLine,Led(1));'+'\n'+
            'write(TextLine,Led(2));'+'\n'+
            'write(TextLine," Z = ");'+'\n'+
            'write(TextLine,Led(4));'+'\n'+
            'writeline(output,TextLine);'+'\n'+
            'wait for 20ns;'+'\n');
    i=i+1;

print('--**Test fraudulent state D transitions**--');
i=0;
while i<12:
    if v1[i] !='sw(0)': # if not the correct key(k7) is pressed
        print('write(TextLine,"Test fraudulent state D*I0I transitions");'+'\n'+
            'writeline(output,TextLine);'+'\n'+
            'sw(7) <= '+"'0'"+';--0'+'\n'+
            'sw(6) <= '+"'0'"+';--1'+'\n'+
            'sw(5) <= '+"'0'"+';--2'+'\n'+
            'sw(4) <= '+"'0'"+';--3'+'\n'+
            'sw(3) <= '+"'0'"+';--4'+'\n'+
            'sw(2) <= '+"'0'"+';--5'+'\n'+
            'sw(1) <= '+"'0'"+';--6'+'\n'+
            'sw(0) <= '+"'0'"+';--7'+'\n'+
            'btn(2) <= '+"'0'"+';--8'+'\n'+
            'btn(0) <= '+"'0'"+';--9'+'\n'+
            'btn(3) <= '+"'0'"+';--R'+'\n'+
            'btn(1) <= '+"'0'"+';--Dr'+'\n'+
            'wait for 20ns;'+'\n'+
            'sw(5) <= '+"'1'"+';'+'\n'+
            'wait for 20ns;'+'\n'+
            'sw(3) <= '+"'1'"+';'+'\n'+
            'wait for 20ns;'+'\n'+
            'sw(1) <= '+"'1'"+';'+'\n'+
            'write(TextLine,"Forced to State D*I0I, LEDs = ");'+'\n'+
            'write(TextLine,Led(0));'+'\n'+
            'write(TextLine,Led(1));'+'\n'+
            'write(TextLine,Led(2));'+'\n'+
            'write(TextLine," Z = ");'+'\n'+
            'write(TextLine,Led(4));'+'\n'+
            'writeline(output,TextLine);'+'\n'+
            'wait for 20ns;'+'\n'+
            v1[i]+' <= '+"'1'"+';'+'\n'+
            'write(TextLine,"Input fault'+' '+v1[i]+', LEDs = ");'+'\n'+
            'write(TextLine,Led(0));'+'\n'+
            'write(TextLine,Led(1));'+'\n'+
            'write(TextLine,Led(2));'+'\n'+
            'write(TextLine," Z = ");'+'\n'+
            'write(TextLine,Led(4));'+'\n'+
            'writeline(output,TextLine);'+'\n'+
            'wait for 20ns;'+'\n');
    i=i+1;

print('--**Test fraudulent state E transitions**--');
i=0;
while i<12:
    if v1[i] !='btn(0)': # if not the correct key(k9) is pressed
        print('write(TextLine,"Test fraudulent state D*I0I transitions");'+'\n'+
            'writeline(output,TextLine);'+'\n'+
            'sw(7) <= '+"'0'"+';--0'+'\n'+
            'sw(6) <= '+"'0'"+';--1'+'\n'+
            'sw(5) <= '+"'0'"+';--2'+'\n'+
            'sw(4) <= '+"'0'"+';--3'+'\n'+
            'sw(3) <= '+"'0'"+';--4'+'\n'+
            'sw(2) <= '+"'0'"+';--5'+'\n'+
            'sw(1) <= '+"'0'"+';--6'+'\n'+
            'sw(0) <= '+"'0'"+';--7'+'\n'+
            'btn(2) <= '+"'0'"+';--8'+'\n'+
            'btn(0) <= '+"'0'"+';--9'+'\n'+
            'btn(3) <= '+"'0'"+';--R'+'\n'+
            'btn(1) <= '+"'0'"+';--Dr'+'\n'+
            'wait for 20ns;'+'\n'+
            'sw(5) <= '+"'1'"+';'+'\n'+
            'wait for 20ns;'+'\n'+
            'sw(3) <= '+"'1'"+';'+'\n'+
            'wait for 20ns;'+'\n'+
            'sw(1) <= '+"'1'"+';'+'\n'+
            'wait for 20ns;'+'\n'+
            'sw(0) <= '+"'1'"+';'+'\n'+
            'write(TextLine,"Forced to State E*I0I, LEDs = ");'+'\n'+
            'write(TextLine,Led(0));'+'\n'+
            'write(TextLine,Led(1));'+'\n'+
            'write(TextLine,Led(2));'+'\n'+
            'write(TextLine," Z = ");'+'\n'+
            'write(TextLine,Led(4));'+'\n'+
            'writeline(output,TextLine);'+'\n'+
            'wait for 20ns;'+'\n'+
            v1[i]+' <= '+"'1'"+';'+'\n'+
            'write(TextLine,"Input fault'+' '+v1[i]+', LEDs = ");'+'\n'+
            'write(TextLine,Led(0));'+'\n'+
            'write(TextLine,Led(1));'+'\n'+
            'write(TextLine,Led(2));'+'\n'+
            'write(TextLine," Z = ");'+'\n'+
            'write(TextLine,Led(4));'+'\n'+
            'writeline(output,TextLine);'+'\n'+
            'wait for 20ns;'+'\n');
    i=i+1;

print('--**Test fraudulent state F transitions**--');
i=0;
while i<12:
    if v1[i] !='btn(1)': # if not the correct key (Dr) is entered
        print('write(TextLine,"Test fraudulent state D*I0I transitions");'+'\n'+
            'writeline(output,TextLine);'+'\n'+
            'sw(7) <= '+"'0'"+';--0'+'\n'+
            'sw(6) <= '+"'0'"+';--1'+'\n'+
            'sw(5) <= '+"'0'"+';--2'+'\n'+
            'sw(4) <= '+"'0'"+';--3'+'\n'+
            'sw(3) <= '+"'0'"+';--4'+'\n'+
            'sw(2) <= '+"'0'"+';--5'+'\n'+
            'sw(1) <= '+"'0'"+';--6'+'\n'+
            'sw(0) <= '+"'0'"+';--7'+'\n'+
            'btn(2) <= '+"'0'"+';--8'+'\n'+
            'btn(0) <= '+"'0'"+';--9'+'\n'+
            'btn(3) <= '+"'0'"+';--R'+'\n'+
            'btn(1) <= '+"'0'"+';--Dr'+'\n'+
            'wait for 20ns;'+'\n'+
            'sw(5) <= '+"'1'"+';'+'\n'+
            'wait for 20ns;'+'\n'+
            'sw(3) <= '+"'1'"+';'+'\n'+
            'wait for 20ns;'+'\n'+
            'sw(1) <= '+"'1'"+';'+'\n'+
            'wait for 20ns;'+'\n'+
            'sw(0) <= '+"'1'"+';'+'\n'+
            'wait for 20ns;'+'\n'+
            'btn(0) <= '+"'1'"+';'+'\n'+
            'write(TextLine,"Forced to State F*I0I, LEDs = ");'+'\n'+
            'write(TextLine,Led(0));'+'\n'+
            'write(TextLine,Led(1));'+'\n'+
            'write(TextLine,Led(2));'+'\n'+
            'write(TextLine," Z = ");'+'\n'+
            'write(TextLine,Led(4));'+'\n'+
            'writeline(output,TextLine);'+'\n'+
            'wait for 20ns;'+'\n'+
            v1[i]+' <= '+"'1'"+';'+'\n'+
            'write(TextLine,"Input fault'+' '+v1[i]+', LEDs = ");'+'\n'+
            'write(TextLine,Led(0));'+'\n'+
            'write(TextLine,Led(1));'+'\n'+
            'write(TextLine,Led(2));'+'\n'+
            'write(TextLine," Z = ");'+'\n'+
            'write(TextLine,Led(4));'+'\n'+
            'writeline(output,TextLine);'+'\n'+
            'wait for 20ns;'+'\n');
    i=i+1;
