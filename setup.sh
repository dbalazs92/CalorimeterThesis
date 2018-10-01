#!/bin/bash
#
# Author: Balázs Demeter (balazsdemeter92@gmail.com)
# Version: 1.1
#
# Script for build and make Geant4 simulation of EMcal

mkdir emcal_build
cd emcal_build
cmake ../
make
echo Setup complete.
