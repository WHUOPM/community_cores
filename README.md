# Community cores

## Presentation

This C++ package is based on the [Louvain algorithm] (https://sites.google.com/site/findcommunities/) (**[2]**) dedicated to detect communities on graphs.
Its aim is to detect the community cores of the graph. These cores are obtained by running the Louvain algorithm many times and detecting consensus (**[1]**).

## Compilation

Run make in a shell in the **Release** folder.

## Usage

### Step 1 : Running Louvain executions to obtain cooccurences graphs
Running the Louvain algorithms **nbLouvain** times on the graph at the path **graph**. The algorithm stores the results in **RUN/nomDossier**. Cooccurences of nodes in communities detected by distinct Louvain runs are stored. **alpha_entier** is the minimum number of cooccurences per total run (from 1 to 9). The parameter **graph_renum** is optionnal, if it does not exist, **graph** is automatically renumbered and **relabel2** is created. 

**>**python simple-run.py graph [graph_renum] [separator] nomDossier nbLouvain alpha_entier

**Exemple :** **>**python simple-run.py exemple/graph graph_exemple 20 2

### Step 2 : Creating cores using cooccurence graphs of step 1
Using the cooccurences created at the previous step, the algorithm produces cores.

**>**python simple-coeur.py graphe nomDossier

**Exemple :** **>**python simple-coeur.py exemple/graph graph_exemple

## Results

In **RUN/nomDossier/alpha/coeurs**, the cores are stored. Each file is identified by an id and represents a core, namely a connected component in the cooccurence graph corresponding to **alpha**.

In **RUN/nomDossier/alpha/**, the cooccurences graphs are stored.

The relabelling file **relabel2** contains matching between the initial labels of the graph file and the new labels after renumbering.

## References
* **[1]** SEIFI, Massoud. Cœurs stables de communautés dans les graphes de terrain. 2012. Thèse de doctorat.
* **[2]** BLONDEL, Vincent D., GUILLAUME, Jean-Loup, LAMBIOTTE, Renaud, et al. Fast unfolding of communities in large networks. Journal of Statistical Mechanics: Theory and Experiment, 2008, vol. 2008, no 10, p. P10008.
