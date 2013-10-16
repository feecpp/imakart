imakart
=======
 * Le répértoire third-party contient les librairies externes utilisées par le projet (glew, assimp...)
Le répértoire est ajouté dans Git pour qu'on soit tous synchro pour son nom mais il ne doit pas synchroniser son contenu !
(il faut pour cela ajouter un .gitignore dans chaque répertoire de librairie)

 * Répértoire de build : il ne doit surtout pas être synchronisé ! Il vaut même mieux que vous
fassiez en sorte qu'il soit ailleurs que dans votre dossier 'imakart' pour vous simplifier la vie.

 * Le répertoire glimac est là si on veut centrer toutes les classes utilitaires vues en TD dans
cette lib...

 * Pour l'instant la plupart des répertoires sont vides avec un fichier '.gitdir' à l'intérieur
qui sert juste à faire en sorte que git les prenne en compte (git ne 'voit' pas un dossier s'il est vide, même
si vous essayer de l'ajouter explicitement).
