#!/bin/bash
#
# Author: Balázs Demeter (balazsdemeter92@gmail.com)
# Version: 1.1
#
# Script for build and make Geant4 simulation of Ecal

mkdir ecal_build
cd ecal_build
cmake ../
make
echo Setup complete.
