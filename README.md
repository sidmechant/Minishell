# Minishell
Minishell est un projet réalisé à l'école 42 où j'ai développé un interpréteur de commandes minimaliste en langage C. Ce projet visait à recréer certaines fonctionnalités de base du shell Unix, telles que l'exécution de commandes, la gestion des environnements, et le traitement des signaux.
L'enjeu pour moi était de réaliser l'analyse syntaxique (ou parsing) afin de traiter les lignes de commande (CLI). Cependant, après avoir étudié la grammaire du shell et l'architecture des données utilisées, j'ai opté pour une structure de données plutôt qu'un arbre binaire. Ce choix a radicalement modifié l'ordre initial de validation de la chaîne de caractères avant de la transmettre à la phase d'exécution.

Dans mon approche, j'ai suivi un processus différent de celui décrit dans l'ordre standard de traitement du shell Bash :
  
    Vérifier la présence de guillemets ouvrants et fermants pour permettre la progression.
    Effectuer la vérification des erreurs de syntaxe pour valider la commande.
    Réaliser les expansions nécessaires sur les parties de la commande.
    Initialiser la structure de données pour représenter la commande analysée.(Tokenisation)
    
Processus Standard de Bash :

    Lecture de l'entrée (depuis un fichier, l'option -c ou d'autres fonctions du système).
    Découpage de l'entrée en tokens : mots et opérateurs.
    Analyse (parsing) de l'entrée en commandes simples et composées.
    Réalisation des différentes expansions sur les parties de chaque commande.
    Gestion des redirections et suppression des opérateurs de redirection.
    Exécution de la commande : fonction, commande interne, fichier exécutable ou script.
    Attente optionnelle de la fin de la commande et récupération du code de sortie.

Ce processus personnalisé s'inspire des étapes fondamentales du traitement de commandes par un shell, mais avec des adaptations spécifiques pour assurer une gestion efficace et précise des lignes de commande dans mon implémentation.
