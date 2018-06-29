#!/bin/bash
#
# Author: Balázs Demeter (balazsdemeter92@gmail.com)
# Version: 1.1
#
# Script for build and make Geant4 simulation of EMcal

mkdir emcal_build
cd emcal_build
cmake ../
make -j4
git clone https://github.com/dbalazs92/EMCal_scripts.git
./electron_Measurements.sh
./gamma_Measurements.sh
./pion0_Measurements.sh
./pion3_Measurements.sh
echo Setup complete.
