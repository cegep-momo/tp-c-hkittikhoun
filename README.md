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
La fonctionnalité qu'offre FileManager est une sauvegarde de données qui transforme des objets en format texte pour stocker cette mémoire dans un dossier. Ceci est possible à cause de la sérialisation et déserialisation des classes Book et User avec les fonctions toFileFormat et fromFileFormat. Ces derniers utilisent stringstream qui est un flux en mémoire qui permet de traiter une chaîne texte comme flux de données avec les délimiteurs ('|'). FileManager permet une gestion des fichiers avec fstream, ofstream qui permet d'ouvrir un fichier en mode écriture et ifstream en mode lecture. Cette classe peut aussi créer des sauvegardes de données avec filesystem.

# Question 2 : Options de développement possible
Pour contenir une grande base de données de livres comme la bibliothèque d'Alexandrie, nous pourrions utiliser MongoDB. Ce dernier est une des technologies de bases de données NoSQL parmi les plus populaires, elle offre des schémas flexible, une bonne performance, une scalabilité horizontale native et une facilité d'utilisation. Pour intégrer cette technologie avec le code, il faudrat installer le driver MongoDB C++, qui est une interface entre MongoDB et l'application. Le système de fichier texte sera remplacer par des collections MongoDB avec des indices optimisés, qui permmettraient une recherche rapide par titre ou auteur.