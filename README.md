**IRC**

- L'IRC (Internet Relay Chat) est un protocole qui permet de dialoguer en temps réel avec d'autres utilisateurs en se connectant grâce à un logiciel spécifique (appelé un client) à un serveur IRC, lui-même relié avec d'autres serveurs IRC.

**Consignes**

- Vous devez développer un serveur IRC en C++ 98.
- Vous ne devez pas développer de client. (donc utilse hexchat je pense)
- Vous ne devez pas gérer la communication de serveur à serveur.
- Votre exécutable sera exécuté comme suit :
- ./ircserv <port> <mot de passe>
- port : Le numéro de port sur lequel votre serveur IRC écoutera les connexions IRC entrantes.
connexions IRC entrantes.
- password : Le mot de passe de la connexion. Il sera nécessaire à tout client IRC qui tente de se connecter à votre serveur.
de se connecter à votre serveur.

A revoir pour la fonction poll() si on a droit de l'utiliser ou pas

**Exigences**

- [ ] Le serveur doit être capable de gérer plusieurs clients en même temps et de ne jamais se bloquer.
se bloquer.
- [ ] La fourche n'est pas autorisée. Toutes les opérations d'E/S doivent être non bloquantes.
- [ ] Un seul poll() (ou équivalent) peut être utilisé pour gérer toutes ces opérations (lecture, écriture, mais aussi écoute, etc.),
écriture, mais aussi écoute, etc.)

**Attention** 
(Comme vous devez utiliser des descripteurs de fichiers non bloquants, il est possible d'utiliser des fonctions de lecture/récupération ou d'écriture/envoi sans poll().
possible d'utiliser les fonctions read/recv ou write/send sans poll() (ou équivalent), et votre serveur ne serait pas bloquant.
(ou équivalent), et votre serveur ne serait pas bloquant.
Mais il consommerait plus de ressources système.
Ainsi, si vous essayez de lire/recourir ou d'écrire/envoyer dans n'importe quel descripteur de fichier
sans utiliser poll() (ou équivalent), votre note sera de 0.)
**============**

Il existe plusieurs clients IRC. Vous devez choisir l'un d'entre eux comme référence. Votre client de référence sera utilisé pendant le processus d'évaluation.
client de référence sera utilisé pendant le processus d'évaluation.
- [ ] Votre client de référence doit pouvoir se connecter à votre serveur sans rencontrer d'erreur.
aucune erreur.
- [ ] La communication entre le client et le serveur doit se faire via TCP/IP (v4 ou v6).
- [ ] L'utilisation de votre client de référence avec votre serveur doit être similaire à son utilisation avec n'importe quel serveur IRC officiel.
serveur IRC officiel. Cependant, vous n'avez qu'à implémenter les fonctionnalités suivantes :
◦ Vous devez pouvoir vous authentifier, définir un pseudo, un nom d'utilisateur, rejoindre un canal,
envoyer et recevoir des messages privés en utilisant votre client de référence.
◦ Tous les messages envoyés par un client à un canal doivent être transmis à tous les autres clients qui ont rejoint le canal.
à tous les autres clients qui ont rejoint le canal.
◦ Vous devez avoir des opérateurs et des utilisateurs réguliers.
◦ Il faut ensuite implémenter les commandes spécifiques aux opérateurs de canaux
des opérateurs :
    ∗ **KICK** - Ejecter un client du canal
    ∗ **INVITE** - Inviter un client sur un canal
    ∗ **TOPIC** - Changer ou voir le sujet du canal
    ∗ **MODE** - Changer le mode du canal :
- **i** : Set/remove Invite-only channel (Définir/supprimer le canal sur invitation uniquement)
- **t** : Définir/supprimer les restrictions de la commande TOPIC pour les opérateurs du canal
aux opérateurs du canal
- **k** : Définir/supprimer la clé du canal (mot de passe)
- **o** : Donner/retirer le privilège de l'opérateur de canal
 **l** : Définir/supprimer la limite d'utilisateurs pour le canal

 **Interdit**
Cependant, vous ne pouvez utiliser fcntl() que de la manière suivante :
fcntl(fd, F_SETFL, O_NONBLOCK) ;
Tout autre drapeau est interdit.

**Pour la verification plus tard**
Vérifier absolument toutes les erreurs et tous les problèmes possibles (réception de données partielles, faible largeur de bande, etc,
etc.)
Pour s'assurer que votre serveur traite correctement tout ce que vous lui envoyez, vous pouvez effectuer le test simple suivant en utilisant nc
test simple suivant, utilisant nc, peut être effectué :
\$> nc 127.0.0.1 6667
com^Dman^Dd
\$>
Utilisez ctrl+D pour envoyer la commande en plusieurs parties : 'com', puis 'man', puis 'd\n'.
Pour traiter une commande, il faut d'abord agréger les paquets reçus afin de la reconstruire.
afin de la reconstruire.

**Partit Bonus**
- Gestion du transfert de fichiers.
- Un bot.