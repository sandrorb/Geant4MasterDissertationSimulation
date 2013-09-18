 #!/bin/bash          
source /usr/local/bin/geant4.sh

mkdir /home/geant4/Desktop/mySimBuild
cd /home/geant4/Desktop/mySimBuild
cmake -DGeant4_DIR=/usr/local/share/Geant4.9.6 /home/geant4/Desktop/Geant4MasterDissertationSimulation

make
