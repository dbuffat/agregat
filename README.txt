Merci de me lire en entier avant de continuer

Avant de lancer le programme veuillez ouvrir le fichier Data.txt qui se trouve dans le dossier Data.
Dedans vous pourrez definir (dans l'ordre) :
La taille d'une grille carre (entier)
Le nombre de grains a generer aleatoirement (entier)
Le pas aleatoire des grains entre 1 et n+1 (n est le nombre rentre, si n=0 la valeur du pas sera constante et egale a 1) (entier)
Le probabilite de collage des grains a l'agregat (reel entre 0 (exclu) et 1)
La generation par rayon (booleen : 1 pour oui et 0 pour non)
La fonction du rayon, il s'agit du rayon inferieur (reel plus grand que 1)
Le rayon initial, dans ce rayon les grains ne pourront pas apparaitre (entier)
Le rayon maximal, il s'agit du rayon superieur, si un grain va au dela il sera perdu (reel plus grand que la fonction du rayon)
Le nombre de grains au depart (entier) suivi de leur position sur la grille

Ensuite vous pouvez lancer le probleme


Les scripts a appele dans cette partie sont dans le meme dossier que le programme. Il ne faut donc pas changer de repertoire avec votre terminal.

Une fois que celui-ci est terminer vous trouverez tout les .txt dans le dossier Data
Pour obtenir les agregats en pdf il suffit d'utiliser PlotAgregat.bash
Pour obtenir les fit lineaire pour la dimension fractale en pdf il faudra lancer PlotFractale.py
Enfin pour avoir des informations statistiques sur la dimension fractale de votre jeu de donnees, il faudra lancer TraitementFractale.bash (toutes les informations apparaitront sur le terminal)

Ps1 : Si vous obtenez des fichiers de fractales vides c'est que votre agregat n'est pas assez grand pour qu'il puisse y avoir un calcul.
Ps2 : Le 3e script depend du 2e script. Par contre le 1er et le 2e script sont independants.
Ps3 : Penser a changer le nombre de boucle a realiser dans les .bash et dans le .py les lignes concernes sont commenter.
