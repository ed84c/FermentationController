//Define how you want to control the temperature profile, based on Probe1.
//Give it a temperature in degC and how long you want it to hold at temp in seconds
const int nSteps = 1;
const float temp_1[nSteps] = {19};
const int holdTime_1[nSteps] = {432000};
const int drivingProbe = 1; //I can only switch one relay at hte moment, which probe decides on/off?