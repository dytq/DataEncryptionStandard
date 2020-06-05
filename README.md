# Simple implémentation de DES 

## Quick-Start

Télécharger le binaire ici: coming soon et taper sur le termial ./des.out aide

## Aide

TAPER ./des.out {option} {MESSAGE} {MOT\_DE\_PASSE}

Les différentes options:

	- '-e': pour encoder
	- '-d': pour decoder

Bien evidement appliquer une seule option et chaque argument est séparé par un espace.

Un argument peut-etre un fichier à importer ou un text. Par defaut le programme prend le nom du fichier s'il est inexistant.

L'agument {MESSAGE} est le message, soit ascii pour chiffrer soit en hexa pour dechiffrer.

L'argument {MOT\_DE\_PASSE} est le mot de passe qu'on veut chiffrer.


## Ecrire la sortie vers un fichier

```echo | ./des.out -e test mdp >> fichier.txt ```

## Outil de developpement

- ```make``` pour compiler et generer le binaire
- ```make clean``` pour enlever les objets et binaire

## Source d'implémentation:

- https://docs.google.com/file/d/0B5F6yMKYDUbrYXE4X1ZCUHpLNnc/view
- https://fr.wikipedia.org/wiki/Constantes_du_DES

## Note de l'auteur 

Rester descret ^^
