#!/usr/bin/env python3.7
#-- coding: utf-8 --

import RPi.GPIO as GPIO #Importe la bibliothèque pour contrôler les GPIOs
from pirc522 import RFID
import time

GPIO.setmode(GPIO.BOARD) #Définit le mode de numérotation (Board)
GPIO.setwarnings(False) #On désactive les messages d'alerte

RFID_UID = [ 243, 217, 126, 36, 112]

rc522 = RFID() #On instancie la lib

print('En attente d\'un badge (pour quitter, Ctrl + c): ') #On affiche un message demandant à l'utilisateur de passer son badge

#On va faire une boucle infinie pour lire en boucle
while True :
    file = open("rfid_is_accepted.txt", "w")
    file.truncate()
    file.write("0")
    file.close()
    rc522.wait_for_tag() #On attnd qu'une puce RFID passe à portée
    print('tag readed')
    (error, tag_type) = rc522.request() #Quand une puce a été lue, on récupère ses infos

    if not error : #Si on a pas d'erreur
        (error, uid) = rc522.anticoll() #On nettoie les possibles collisions, ça arrive si plusieurs cartes passent en même temps

    if not error : #Si on a réussi à nettoyer
        print('Vous avez passé le badge avec l\'id : {}'.format(uid)) #On affiche l'identifiant unique du badge RFID
    
    if not error : #Si on a réussi à nettoyer
        if RFID_UID == uid :
            print('Badge {} autorisé !'.format(uid))
            file = open("rfid_is_accepted.txt", "w")
            file.truncate()
            file.write("1")
            file.close()
            time.sleep(2)
        else :
            print('Badge {} interdit !'.format(uid))
            file = open("rfid_is_accepted.txt", "w")
            file.truncate()
            file.write("0")
            file.close()
    
    time.sleep(0.2) #On attend 1 seconde pour ne pas lire le tag des centaines de fois en quelques milli-secondes
    


