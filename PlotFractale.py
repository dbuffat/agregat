import numpy as np
import matplotlib.pyplot as plt
from scipy import stats

def ajustement_lineaire_et_fichier(fichier):
    # Lecture des données à partir du fichier texte
    donnees = np.loadtxt(f"Data/DonneesFractale_{fichier}.txt", delimiter=' ')

    # Séparation des données en x et y
    x = donnees[:, 0]  # Première colonne
    y = donnees[:, 1]  # Deuxième colonne

    # Ajustement linéaire
    pente, intercept, _, _, _ = stats.linregress(x, y)
    y_pred = pente * x + intercept

    # Création du graphique
    plt.scatter(x, y, label='Données')

    # Affichage de la droite de régression
    plt.plot(x, y_pred, color='red', label='Ajustement linéaire')

    # Ajout de légendes et titres
    plt.xlabel('X')
    plt.ylabel('Y')
    plt.title('Ajustement linéaire')
    plt.legend()

    # Affichage du graphique
    plt.grid(True)
    plt.savefig(f"Data/fractale_{fichier}.pdf")
    plt.close() #Ferme la figure

    # Ajout du coefficient directeur au fichier de sortie
    with open("Data/DimensionFractale.txt", "a") as f:
        f.write(f"{pente}\n")

# Nombre de fichiers à traiter
nombre_de_fichiers = 3  # Vous pouvez changer cette valeur selon le nombre de fichiers à traiter

# Réinitialisation du fichier de sortie
open("Data/DimensionFractale.txt", "w").close()

# Boucle sur les fichiers
for i in range(1, nombre_de_fichiers + 1):
    nom_fichier = i
    ajustement_lineaire_et_fichier(nom_fichier)
