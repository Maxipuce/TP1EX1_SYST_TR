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
  
  


