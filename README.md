# CalorimeterThesis

GEANT simulation of sPHENIX's Electromagnetic calorimeter. C++ program of my Master thesis work.

## Author

* **Balázs Demeter** - *University of Debrecen* - [E-mail](mailto:balazsdemeter92@gmail.com)

## Summary

This Geant4 simulation demonstrates how the hadronshower generates optical photons in scintillating fibers in the layout of sPHENIX's Electromagnetic Calorimeter. 
sPHENIX is a new detector planned for the Relativistic Heavy Ion Collider at Brookhaven National Laboratory and will provide state-of-art capabilities for studies of the strongly interacting quark-gluon plasma using jet and heavy-flavor observables. 
The calorimeter will be divided into individual towers with about ~2500 fibers. 
A calorimeter 18 radiation lengths thick occupies 12.6 cm in radius, and with light collection, sensors, preamps, and cables, the calorimeter is expected to occupy radial space of about 25 cm. 
The fibers are single-cladded Kuraray SCSF-78 with 0.47 mm diameter fibers on 1 mm centers. 
For starting program in batch mode (no UI), 4 parameters are needed: Number of events, energy of bullet particle (in GeV), Hadronic physics list and type of particles. 
The first two parameters and the last are numbers while others are strings for the program. MultiThreading is enabled.

## Download and build

### Requirements

* Linux (Tested on Ubuntu 16.04 LTS)

* Qt4 (Tested on version 5.9.1) 

* GEANT 4.10.02 or newer

* CLHEP 2.3.4.4 or newer

### Download Link

Via Git:

```
git clone https://github.com/dbalazs92/CalorimeterThesis.git
```

Direct link:

```
https://github.com/dbalazs92/CalorimeterThesis/archive/master.zip
```

### Build

In the directory of program (CalorimeterThesis), open a terminal window and enter:

```
chmod 744 setup.sh
```

After giving the necessary permissions for setup script, run:

```
./setup.sh
``` 

### Running the simulation
 
#### Run in batch mode

After build, in the directory of build (emcal_build), open a terminal window and enter:

```
./EMCal_MT <numberofevents> <energyofparticleingev> <physicslist> <typeofparticle> <fiberparameter> <typeofcut> <noofthreads>
```

#### Run in interactive mode

After build, in the directory of program (EMCal_MT), open a terminal window and enter:

```
./interactive.sh
```

## Updates

* 2018/11/17 - 'v2.5' - Major upgrade of every parts 

* 2018/03/13 - 'v2.1' - Implementation of Box–Muller transform in PGA

* 2018/02/19 - 'v2.0' - Major improvements in geometry

* 2017/11/16 - 'v1.8' - Added fiber argument

* 2017/11/09 - 'v1.6' - Fixed PhysicsList and Multi-fiber geometry

* 2017/10/26 - 'v1.4' - Analysis modifications and Multi-Threaded is enabled

* 2017/10/18 - 'v1.2' - Minimal modifications in SteppingAction

* 2017/09/30 - 'v1.0' - One fiber with tungsten cover and detector plate

* 2017/09/29 - 'v0.6' - Added summary and parameterisation

* 2017/09/21 - 'v0.4' - Added detector to end of fiber and improved PhysicsList (added hadronic progresses)

* 2017/09/17 - 'v0.2' - Added scripts for build and interactive run

* 2017/09/15 - 'v0.1' - Creation of program and it's repository
