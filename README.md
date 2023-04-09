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
ou similaire en fonction de la distribution d'installé sur votre machine.


Aperçu : 
![GUI](https://i.imgur.com/RW7rHsh.png)

## Tests
Aucun test n'échoue.

## Réalisations
Le code à étais divisé en plusieurs partie :
- ``board/``
- ``pieces/`` 
- ``ui/``  comportant la partie CLI et GUI.

### Traitement des coups légaux
La classe "GameRuler" s'occupe de cela. Elle a la particularité de suivre le pattern [Singleton](https://refactoring.guru/design-patterns/singleton).

### Traitement des pièces
"PieceHandler" s'occupe d'initialiser les pièces sur l'échiquier en suivant la notation ["Forsyth-Edwards Notation"](https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation). Elle est également responsable du déplacement des pièces en une position donnée à une autre sur l'échiquier lorsque le coup est légal.

### Déplacement des pièces
Tous les types de mouvements pour les pièces ont été écrits dans ``checkmove.cpp``, puis ils ont été répartis dans les en-têtes correspondants (``bishopchecker.hpp``, ``kingchecker.hpp``, etc...).

Cela permet une granularité dans la gestion des coups et évite les répétitions de code. Par exemple, il est possible de réutiliser les fonctions écrites pour le Fou et la Tour et de les appliquer à la Reine. Pour plus d'informations sur cette idée/réalisation, voir :
https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Friendship_and_the_Attorney-Client

### CLI & GUI
La classe ``Game`` possède une méthode abstraite ``run()`` qui est redéfinie par les classes ``CLI`` et ``GUI`` pour gérer les comportements de l'utilisateur.

La manière optimale de le faire aurait été d'utiliser le pattern  [Observer](https://refactoring.guru/design-patterns/observer) avec un CLI et un GUI comme observateurs, mais ce projet n'a pas été réalisé dans le cadre d'un cours de conception, donc j'ai pris certaines libertés.

## Note
- ``ui/gui/gui.cpp`` est un peu désorganisé. Il nécessite une refonte, mais comme la réalisation d'une interface graphique n'a pas été demandée, cela ne sera probablement pas fait.


