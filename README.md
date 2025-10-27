# Construire le projet
Vous pouvez utiliser un dev container de base C++ de VScode.
Le projet utilise cmake, pensez à l'inclure dans votre dev container.

Voici les lignes de commandes pour compiler le projet:
```
$ mkdir build
$ cd build
$ cmake ..
$ make
```

# Répertoire data

Il contient 2 fichiers `books.txt`et `users.txt` que vous pouvez utilisez pour tester votre code.
Pour ca il suffit de les copiers dans le repertoire `build` avec l'application `bibliotheque`


# Question 1 : C++
La fonctionnalité qu'offre FileManager est une sauvegarde de données qui transforme des objets en format texte pour la mémoire dans un dossier. Ce dernier est possible à cause de la sérialisation et déserialisation des classes Book et User avec les fonctions toFileFormat et fromFileFormat. Ces derniers utilisent stringstream qui est un flux en mémoire qui permet de traiter une chaîne texte comme flux de données avec les délimiteurs ('|'). FileManager permet une gestion des fichiers avec fstream, ofstream qui permet d'ouvrir un fichier en mode écriture et ifstream en mode lecture. Cette classe peut aussi créer des sauvegarde de données avec filesystem.