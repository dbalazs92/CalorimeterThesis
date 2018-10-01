#!/bin/bash
# Creator: Balazs Demeter
./EMCal_MT 10000 2 emstandard_opt0 e- 40 0 16 | grep CalDat >data.txt
wait
root -l 'Macro.cc(40,"e_2_0_40.root","e_2_0_40_edep.png","e_2_0_40_lat.png","e_2_0_40_Hit.png")' 
wait
./EMCal_MT 10000 2 emstandard_opt0 gamma 40 0 16 | grep CalDat >data.txt
wait
root -l 'Macro.cc(40,"gamma_2_0_40.root","gamma_2_0_40_edep.png","gamma_2_0_40_lat.png","gamma_2_0_40_Hit.png")' 
wait
./EMCal_MT 10000 5 emstandard_opt0 gamma 80 0 16 | grep CalDat >data.txt
wait
root -l 'Macro.cc(80,"gamma_5_0_80.root","gamma_5_0_80_edep.png","gamma_5_0_80_lat.png","gamma_5_0_80_Hit.png")' 
wait
./EMCal_MT 10000 5 emstandard_opt0 e- 80 0 16 | grep CalDat >data.txt
wait
root -l 'Macro.cc(80,"e_5_0_80.root","e_5_0_80_edep.png","e_5_0_80_lat.png","e_5_0_80_Hit.png")' 
wait
./EMCal_MT 10000 10 emstandard_opt0 e- 160 0 16 | grep CalDat >data.txt
wait
root -l 'Macro.cc(160,"e_10_0_160.root","e_10_0_160_edep.png","e_10_0_160_lat.png","e_10_0_160_Hit.png")' 
wait
./EMCal_MT 10000 10 emstandard_opt0 gamma 160 0 16 | grep CalDat >data.txt
wait
root -l 'Macro.cc(160,"gamma_10_0_160.root","gamma_10_0_160_edep.png","gamma_10_0_160_lat.png","gamma_10_0_160_Hit.png")' 
wait
