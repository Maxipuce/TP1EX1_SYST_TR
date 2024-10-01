<h1>TP1_SYST_TR</h1>

<h2>Exercice 1:<h2/>

<h3>Dans cet exercice il était question de vérifier la faisabilité d'un système comprenant plusieurs tâches.</h3>

<br><br>
  <h4>Ordonnancement Highest Priority First</i></h4>
  <p>
  Dans un premier temps il fallait tester sur un système avec ordonnancement statique en mode HPF (Highest Priority First).
  Pour cela nous avons créé une fonction <i>check_feasibility</i> qui fonctionne de la manière suivante:
  <ul>
    <li>Ordonne les tâches par ordre de priorité dans l'array 2D</li>
    <li>Display la liste des tâches dans l'ordre de priorité avec les infos correspondantes</li>
    <li>Puis va additioner les temps d'exécution de toutes les tâches du système, tout en s'assurant qu'aucune tâche ne dépasse sa deadline</li>
  </ul>
  Si une tâche vient à dépaser sa deadline alors la fonction va en informer l'utilisateur et arrêter son fonctionnement.
  </p>
  
  <br>
  Ensuite il fallait adapter l'algorithme à d'autres types d'ordonnancement.
  <br>

<br><br>
  <h4>Ordonnancement Rate Monotonic</h4>
  <p>

  Pour un ordonnancement Rate Monotonic il faut regarder 2 points importants:
  <ul>
    <li>Calculer la charge du processeur U pour vérifier si le processeur peut gérer toutes les tâches du system</li>
    <li>Calculer le temps de réponse des tâches</li>
  </ul>

  C'est ce qui est fait dans la fonction <i>ex1()</i>: dans un premier temps nous calculons et comparons U et Urm; puis l'algorithm choisi:
  <ul>
    <li>Si U > 1: alors le système n'est pas faisable</li>
    <li>Si U < Urm: le système est faisable car la charge du processeur est inférieur à la charge maximale possible</li>
    <li>Si Urm < U < 1: on ne peut pas décider donc il faut calculer le temps de réponse des tâches</li>
  </ul>

  Pour calculer le temps de réponse des tâches nous utilisons la fonction <i>calc_resp_time</i> qui fonctionne comme tel:
  <ul>
    <li>Ordonne les tâches par ordre de priorité dans l'array 2D</li>
    <li>Calcule le temps de réponse de chaque tâche en utilisant la formule vue en cours</li>
    <li>Vérifie que le temps de réponse soit bien inférieur ou égal à la deadline de la tâche</li>
  </ul>
Puis l'algorithme informe l'utilisateur sur la faisabilité du système
      
  </p>

  <br><br>
  <h4>Ordonnancement Deadline Monotonic</h4>
  <p>

  Pour un ordonnancement Deadline Monotonic il faut regarder si le temps de réponse est inférieur ou égal à la deadline de la tâche
  Pour cela nous utilisons encore une fois la fonction <i>calc_resp_time</i>.
  Puis l'algorithme informe l'utilisateur sur la faisabilité du système en mode Deadline Monotonic
      
  </p>

  <h2>Exercice 2: Ordonnanceur EDF (Earliest Deadline First)</h2>
  
  <h4>Ce programme simule un ordonnanceur de tâches temps réel utilisant l'algorithme EDF (Earliest Deadline First), qui exécute les tâches en fonction de leurs échéances les plus proches. Il est conçu pour gérer plusieurs tâches périodiques, chacune avec une durée d'exécution, une période, et une échéance. Il s'exécute jusqu'à atteindre le temps maximum déterminé par la période d'activité.</h3>

<br><br>

<h3>Structure et déclarations</h2>

<p>La structure Task représente une tâche avec plusieurs attributs :<br>

- <u>task_id</u>: Identifiant de la tâche (ex: "T1", "T2").<br>
- <u>execution_time</u>: Durée d'exécution totale de la tâche.<br>
- <u>remaining_time</u>: Temps restant pour terminer la tâche en cours d'exécution.<br>
- <u>deadline</u>: Échéance absolue (initialement égale à la première période).<br>
- <u>period</u>: Période de répétition de la tâche.<br>
- <u>original_deadline</u>: Échéance initiale (utile pour la réinitialisation).<br>
- <u>execution_count</u>: Compteur du nombre de fois où la tâche a été exécutée.<br></p>

<h3>Organisation du code</h3>


<p>Comparé à l'exercice 1, nous n'avions pas différents cas à traiter selon le choix de l'utilisateur. Mais la difficulté se cache dans le traitement des tâches et la manière et l'ordre dans lequel les tâches doivent être traitées afin que l'ensemble de ces dernières soit traitées dans les temps (avant leur période et échéance absolue). Cela demandait donc de nombreuses informations à traiter.</p>


<h4>Fonctions principales :</h4>

<p>Nous avons commencé, comme l'exercice précédent, par demander à l'utilisateur le nombre de tâches et leurs durée d'exécution, échéance relative et période respectives.<br>
  
Une fois entrée, le programme display l'ensemble des données sous forme de tableau, afin d'avoir un visuel simplifié des tâches, et calcule ensuite la période d'étude ou <i>busy_period</i> afin de déterminer la période pendant laquelle le processeur est constamment occupé à exécuter des tâches, sans temps d'attente. Cela correspondra à la période d'exécution des tâches que le programme affichera si l'ensemble des tâches est faisable.<br><br>

Cela est calculé grâce à la fonction <b>calculate_busy_period(Task tasks[], int num_tasks);</b>.<br><br>

L'aspect principal du programme et de l'exercice, à savoir l'ordonnancement des tâches est réalisé de manière autonome par la fonction <b>run_edf_scheduler(Task tasks[], int num_tasks, int hyperperiod);</b>.<br>
Cette dernière, après avoir fait appel à la fonction calculant la période d'étude, trie les tâches en fonction de l'échéance la plus proche. À chaque unité de temps, elle exécute la tâche ayant l'échéance la plus proche. Si une tâche ne respecte pas son échéance, le programme signale l'erreur et termine l'exécution. Les tâches sont réinitialisées à la fin de leur période pour être exécutées à nouveau lors du prochain cycle.<br><br>

C'est cette fonction qui simule l'exécution des tâches avec des messages d'information et de diagnostic.</p>


<h4>Fonctions secondaires :</h4>

<p>Les fonction principales reçoivent de l'aide de la part d'autres fonctions, question d'efficacité et pour séparer les actions à réaliser de manière intelligente.<br><br>

Nous avons notamment :<br><br>

- <b>compare(const void *a, const void *b);</b> qui trie les tâches par ordre croissant d'échéances,
- <b>print_task(Task task);</b> qui affiche les informations d'une tâche individuelle, incluant son temps d'exécution, temps restant, échéance, période et nombre d'exécutions,
- <b>get_positive_int(const char *prompt);</b> qui vérifie l'entrée utilisateur pour s'assurer que la valeur est un entier positif valide pour les informations des tâches,
- <b>calculate_hyperperiod(Task tasks[], int num_tasks);</b> qui calcule la durée après laquelle les tâches se répéteront dans un cycle parfait.
</p>

<h4>Le programme prends en compte toutes les données des tâches, les trie et les compare en temps réel à chaque instant afin de déterminer et choisir lesquelles exécuter, en prenant en compte l'évolution de leurs échéances absolues. Cela permet d'analyser en temps réel la situation de chacune des tâches et, le cas échéant, indiquer le dépassement d'une échéance et donc la non-faisabilité de l'ensemble des tâches données par l'utilisateur.</h4>

