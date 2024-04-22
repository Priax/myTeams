# Documentation sur la Communication Client-Serveur

Cette documentation fournit un aperçu du système de communication client-serveur implémenté dans cette application. Le système se compose d'un composant côté serveur et d'un composant côté client correspondant. Il est important de comprendre comment les inputs sont gérés et renvoyés si besoin est de créer sa propre application communiquant avec le serveur.

## Côté Serveur
Gestion des Commandes

    Le serveur maintient une liste des commandes prises en charge ainsi que de leurs gestionnaires respectifs.
    Les commandes prises en charge comprennent :
        /login ["USERNAME"]: Initie un processus de connexion utilisateur.
        /logout : Déconnecte l'utilisateur actuel.
        /help : Affiche les commandes disponibles et leur utilisation.
        /user [UUID]: Récupère des informations sur un utilisateur spécifique.
        /users : Récupère une liste de tous les utilisateurs.
        /send [UUID] ["MESSAGE_BODY"]: Envoie un message à un autre utilisateur.
        /messages [UUID]: Récupère une liste de messages pour l'utilisateur actuel.
    Le serveur analyse les commandes entrantes et délègue leur exécution aux gestionnaires de commandes correspondants.
    Les gestionnaires de commandes vérifient le statut d'authentification de l'utilisateur avant d'exécuter certaines commandes.
    Les commandes non reconnues ou émises par des utilisateurs non authentifiés reçoivent des réponses d'erreur appropriées. Chaque erreur sera renvoyé sous ce format : CODE MESSAGE_D'ERREUR\r\n
    Le serveur lit également les inputs du client en terminant toujours son read sur \r\n.

## Journalisation et Authentification des Utilisateurs

    Le serveur maintient un journal des clients connectés, y compris leurs détails de session.
    Le statut d'authentification est suivi pour chaque session client afin de garantir le respect des restrictions d'exécution des commandes.
    Les tentatives d'accès non autorisées entraînent des réponses d'erreur appropriées.

## Côté Client
Gestion des Réponses

    Le client maintient une liste des réponses attendues du serveur ainsi que de leurs gestionnaires respectifs.
    Les réponses incluent :
        L01 : Réponse de connexion réussie.
        U01 : Réponse d'informations utilisateur.
        U02 : Réponse d'utilisateur invalide.
        US01 : Liste des utilisateurs en réponse.
        S01 : Réponse d'envoi de message réussie.
        S02 : Réponse d'envoi de message échouée.
        M01 : Liste des réponses de messages.
        221 : Réponse de déconnexion réussie.
        220 : Réponse d'initialisation.
    À la réception d'une réponse du serveur, le client identifie le type de réponse et invoque le gestionnaire correspondant pour la traiter.
    Les réponses sont gérées en fonction de leur type, permettant un retour d'information et une interaction utilisateur appropriés. Généralement, le serveur renverra l'UUID et le nom d'utilisateur, mais il peut aussi renvoyer une information, ou bien une date selon la commande.

## Conclusion

Ce système de communication client-serveur permet aux utilisateurs d'interagir avec le serveur à travers un ensemble défini de commandes et de recevoir des réponses en conséquence. En appliquant des règles d'authentification et d'exécution des commandes côté serveur, le système garantit un accès sécurisé et contrôlé aux ressources du serveur.
