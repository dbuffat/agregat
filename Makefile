##############################
# Makefile du Projet
##############################

#Modifier le chargement des fichiers
OBJECTSMAIN = generation.o agregat.o simulation.o main.o
all: main.exe

#Commande pour la compilation et le chargement de ROOT
COMPILCOMMAND=g++ -fopenmp -c -o $@   $<

# Commande generique pour generer tous les fichiers objets
# a partir des fichiers d'en tete et des fichiers source
%.o: %.cpp %.h
	$(COMPILCOMMAND)

# La regle ci-dessus ne marche pas necessairement pour main.o du fait de
# l'absence d'un fichier main.h...
%.o: %.cpp 
	$(COMPILCOMMAND)

# Fichiers source a generer
# A noter les "dependances" en plus des fichiers d'en tete et des fichiers
# source definis dans la commande generique ci-dessus
generation.o:		
agregat.o:			agregat.h
simulation.o:
main.o:	

# Creation de l'executable
main.exe: $(OBJECTSMAIN)
	g++ -fopenmp -o main.exe $(OBJECTSMAIN)
	

# Commande de nettoyage
clean:
	rm -rf *.o main.exe *~ Print
