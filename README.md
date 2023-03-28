# Projet d'échecs 
*Projet réalisé par [Alexander Yanovskyy](https://yanovskyy.com).* 

## Sommaire
- [Projet d'échecs](#projet-déchecs)
  - [Sommaire](#sommaire)
  - [Compilation \& utilisation](#compilation--utilisation)
    - [CLI](#cli)
    - [GUI](#gui)
  - [Tests](#tests)
  - [Réalisations](#réalisations)
    - [Traitement des coups légaux](#traitement-des-coups-légaux)
    - [Traitement des pièces](#traitement-des-pièces)
    - [Déplacement des pièces](#déplacement-des-pièces)
    - [CLI \& GUI](#cli--gui)
  - [Note](#note)

## Compilation & utilisation
### CLI
```
$ make
$ ./bin/chess-cli
Game init
Game running

     a     b     c     d     e     f     g     h    
  +-----+-----+-----+-----+-----+-----+-----+-----+
8 |  ♖  |  ♘  |  ♗  |  ♕  |  ♔  |  ♗  |  ♘  |  ♖  |
  +-----+-----+-----+-----+-----+-----+-----+-----+
7 |  ♙  |  ♙  |  ♙  |  ♙  |  ♙  |  ♙  |  ♙  |  ♙  |
  +-----+-----+-----+-----+-----+-----+-----+-----+
6 |     |     |     |     |     |     |     |     |
  +-----+-----+-----+-----+-----+-----+-----+-----+
5 |     |     |     |     |     |     |     |     |
  +-----+-----+-----+-----+-----+-----+-----+-----+
4 |     |     |     |     |     |     |     |     |
  +-----+-----+-----+-----+-----+-----+-----+-----+
3 |     |     |     |     |     |     |     |     |
  +-----+-----+-----+-----+-----+-----+-----+-----+
2 |  ♟  |  ♟  |  ♟  |  ♟  |  ♟  |  ♟  |  ♟  |  ♟  |
  +-----+-----+-----+-----+-----+-----+-----+-----+
1 |  ♜  |  ♞  |  ♝  |  ♛  |  ♚  |  ♝  |  ♞  |  ♜  |
  +-----+-----+-----+-----+-----+-----+-----+-----+
White eaten pieces: 0
Black eaten pieces: 0
Turn: WHITE

Enter your move: 
```
Possibilité de saisie : 
- Pour bouger une pièce : ``e2e4``
- Grand rook : ``Regex[(O|o|0)-(O|o|0)-(O|o|0)]``, par exemple ``O-O-O``.
- Petit rook : ``Regex[(O|o|0)-(O|o|0)]``, par exemple ``0-0``.
- Abandonner : ``/resign``
-  Etablir une égalité : ``/draw``
- Quitter : ``/quit``

### GUI
```
$ make gui
$ ./bin/chess-gui --gui
```

⚠️ Package nécessaire ⚠️ 
```
libsdl2-dev
libsdl2-image-dev
libsdl2-ttf-dev
```

Aperçu : 
![GUI](https://i.imgur.com/RW7rHsh.png)
 ou similaire en fonction de la distribution d'installé sur votre machine.



## Tests
Aucun test n'échoue.

## Réalisations
Le code à étais divisé en plusieurs partie :
- ``board/``
- ``pieces/`` 
- ``ui/``  comportant la partie CLI et GUI.

### Traitement des coups légaux
La  classe ``GameRuler`` s'occupe de cela, elle à la particularité de suivre le pattern [Singleton](https://refactoring.guru/design-patterns/singleton).

### Traitement des pièces
``PieceHandler`` s'occupe d'initialiser les pièces sur l'échéquié en suivant la notation ["Forsyth-Edwards Notation"](https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation),  mais aussi de faire l'effort de déplacer une pièce en une position donnée à une autre sur l'échéquié lorsque le coup est légal.

### Déplacement des pièces
Tous les types de mouvements pour les pièces on étais écrite dans ``checkmove.cpp`` puis ils sont dispatché dans les en-têtes attitrés (``bishopchecker.hpp``, ``kingchecker.hpp`` ...). 

Cela permet une granularité sur la gestion des coups et évite les répetitions de code, par exemple il est possible de réutiliser les fonctions écrite pour le Fou et la Tour et de les appliquer pour la Reine. 

Pour plus d'information sur l'idée/réalisation : https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Friendship_and_the_Attorney-Client

### CLI & GUI
La classe ``Game`` possède une méthode abstraite ``run()`` qui vas être redéfini par la classe ``CLI`` et ``GUI`` pour gérer les comportements de l'utilisateur. 

La manière optimal de faire d'implémenter cela aurais étais d'utiliser le pattern [Observer](https://refactoring.guru/design-patterns/observer) avec comme observer un CLI et un GUI, mais le projet n'est pas réalisé dans le cadre d'un cours de conception, donc je me permet certaine libertés.

## Note
- ``ui/gui/gui.cpp`` est un petit bazar, elle nécessite une refactorisation mais vue que la réalisation d'un GUI n'a pas étais demandé, cela ne vas certainement pas être fait.


