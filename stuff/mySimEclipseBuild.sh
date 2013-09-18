 #!/bin/bash          
source /usr/local/bin/geant4.sh

DIR=/home/geant4/Desktop/mySimBuild

if [ ! -d "$DIR" ]; 
  then
    mkdir $DIR
  else
    echo "O diretorio $DIR ja existe"
fi

cd /home/geant4/Desktop/mySimBuild
cmake -DGeant4_DIR=/usr/local/share/Geant4.9.6 /home/geant4/Desktop/Geant4MasterDissertationSimulation

make
