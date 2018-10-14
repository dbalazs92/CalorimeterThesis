#!/bin/bash
# Creator: Balazs Demeter
./EMCal_MT 3000 1 emstandard_opt0 e- 80 0 16 | grep CalDat >data.txt
wait
root -l 'Macro.cc(80,"e_data0.root","e_data0_edep.png","e_data0_lat.png")' 
wait
./EMCal_MT 3000 1 emstandard_opt1 e- 80 0 16 | grep CalDat >data.txt
wait
root -l 'Macro.cc(80,"e_data1.root","e_data1_edep.png","e_data1_lat.png")' 
wait
./EMCal_MT 3000 1 emstandard_opt2 e- 80 0 16 | grep CalDat >data.txt
wait
root -l 'Macro.cc(80,"e_data2.root","e_data2_edep.png","e_data2_lat.png")' 
wait
./EMCal_MT 3000 1 emstandard_opt3 e- 80 0 16 | grep CalDat >data.txt
wait
root -l 'Macro.cc(80,"e_data3.root","e_data3_edep.png","e_data3_lat.png")' 
wait
./EMCal_MT 3000 1 emstandard_opt4 e- 80 0 16 | grep CalDat >data.txt
wait
root -l 'Macro.cc(80,"e_data4.root","e_data4_edep.png","e_data4_lat.png")' 
wait
./EMCal_MT 3000 1 emstandardGS e- 80 0 16 | grep CalDat >data.txt
wait
root -l 'Macro.cc(80,"e_dataGS.root","e_dataGS_edep.png","e_dataGS_lat.png")' 
wait
