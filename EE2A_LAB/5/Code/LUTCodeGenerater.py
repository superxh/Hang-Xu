local1_real=[64,63,59,53,45,36,24,12,0,-12,-24,-36,-45,-53,-59,-63,-64,-63,-59,-53,-45,-36,-24,-12,0,12,24,36,45,53,59,63];
local1_imag=[0,-12,-24,-36,-45,-53,-59,-63,-64,-63,-59,-53,-45,-36,-24,-12,0,12,24,36,45,53,59,63,64,63,59,53,45,36,24,12,0,-12,-24,-36,-45,-53,-59,-63,-64,-63,-59,-53,-45,-36,-24,-12,0,12,24,36,45,53,59,63,64,63,59,53,45,36,24,12,0,-12,-24,-36,-45,-53,-59,-63,-64,-63,-59,-53,-45,-36,-24,-12,0,12,24,36,45,53,59,63,64,63,59,53,45,36,24,12,0,-12,-24,-36,-45,-53,-59,-63,-64,-63,-59,-53,-45,-36,-24,-12,0,12,24,36,45,53,59,63,64,63,59,53,45,36,24,12];
local2_real=[64,59,45,24,0,-24,-45,-59,-64,-59,-45,-24,0,24,45,59,64,59,45,24,0,-24,-45,-59,-64,-59,-45,-24,0,24,45,59,64,59,45,24,0,-24,-45,-59,-64,-59,-45,-24,0,24,45,59,64,59,45,24,0,-24,-45,-59,-64,-59,-45,-24,0,24,45,59,64,59,45,24,0,-24,-45,-59,-64,-59,-45,-24,0,24,45,59,64,59,45,24,0,-24,-45,-59,-64,-59,-45,-24,0,24,45,59,64,59,45,24,0,-24,-45,-59,-64,-59,-45,-24,0,24,45,59,64,59,45,24,0,-24,-45,-59,-64,-59,-45,-24,0,24,45,59];
local2_imag=[0,-24,-45,-59,-64,-59,-45,-24,0,24,45,59,64,59,45,24,0,-24,-45,-59,-64,-59,-45,-24,0,24,45,59,64,59,45,24,0,-24,-45,-59,-64,-59,-45,-24,0,24,45,59,64,59,45,24,0,-24,-45,-59,-64,-59,-45,-24,0,24,45,59,64,59,45,24,0,-24,-45,-59,-64,-59,-45,-24,0,24,45,59,64,59,45,24,0,-24,-45,-59,-64,-59,-45,-24,0,24,45,59,64,59,45,24,0,-24,-45,-59,-64,-59,-45,-24,0,24,45,59,64,59,45,24,0,-24,-45,-59,-64,-59,-45,-24,0,24,45,59,64,59,45,24];

i=0;
while i<128:
    print('if(count==%d) {ARG1=%d;ARG2=%d;ARG3=%d;ARG4=%d;}'%(i,local1_real[i%32],local1_imag[i],local2_real[i],local2_imag[i]));
    i=i+1;

