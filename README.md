# smart_lock
Projet de développement d'une serrure intelligente avec une raspberry pi, utilisant la reconnaissance faciale et le RFID
## Installation
### 1. Installer les packages nescessaires
    => sudo apt-get install build-essential wiringpi python3.7 python3.7-dev make libopencv-dev libopencv-contrib-dev
    
    => installation de raspicam 0.1.6 :
        tar xvzf raspicamxx.tgz
        cd raspicamxx
        mkdir build
        cd build
        cmake ..
        make
        sudo make install
### 2. Cloner ou télécharge le contenu de ce dépot
    =>cd Documents
      git clone https://github.com/EthaneEce/smart_lock.git
### 3. Build les fichiers sources
    =>cd smart_lock
      make all


## Contenu

###  1. Fichiers sources
    => train.cpp lit des images, et génère un fichier .xml d'entrainement
    => face_reco.cpp est la reconnaissance faciale qui utilise le fichier .xml d'entrainement
    => ultrasonic.c mesure une distance et démarre la reconnaissance faciale si on est en dessous d'une certaine valeur
    => read_rfid_uid.py lit les badges RFID
    => smart_lock.c est le program principal, il va démarrer les autres en utilisant des threads, et va allumer les LEDs correspondantes en fonction du résultat retourné par read_rfid_uid.py et face_reco.cpp

### 2. Organisation du répertoire
L'organisation du répertoire est importante. Les images utilisées pour entrainer le modèle doivent être dans le dossier dataset, avec des sous-dossiers correspondants a chaque personne a entrainer.

```
project
│   README.md
│   Makefile    
│   smart_lock.c
|
└───features
|   |   face_reco.cpp
|   |   train.cpp
|   |   read_rfid_uid.py
|   |   ultrasonic.c
|   |
│   └───cascades
│   │   |   lbpcascade_frontalface.xml
|   |
│   └───recognizer
│   |   |   embeddings.xml
│   |   │   labels.txt
│   |
|   └───dataset
│       └───Mark
│       |   Mark_01.jpg
|       |   Mark_02.jpg
│       |   ...
|       |
│       └───Tom
│       │   Tom_01.jpg
│       │   Tom_02.jpg
│       │   ...
│   
└───lib
    │   pthread.h
```

## Utilisation
    =>Entrainer le modèle : ./features/train
    =>Lancer l'ensemble : ./smart_lock