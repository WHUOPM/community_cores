# Community cores

##Location

[https://github.com/nicolasdugue/community_cores](https://github.com/nicolasdugue/community_cores)

## Presentation

This C++ package is based on the [Louvain algorithm] (https://sites.google.com/site/findcommunities/) (**[2]**) which aims to detect graphs communities.
The specific aim of this package is to detect the community cores of the graph. These cores are obtained by running the Louvain algorithm many times and detecting consensus (**[1,3]** for detailed information).

This package was originally developped by Tennessy Kolubako and then updated by [Anthony perez] (http://www.univ-orleans.fr/lifo/membres/Anthony.Perez) and [Nicolas Dugué] (http://www.univ-orleans.fr/lifo/membres/Nicolas.Dugue/).

## Compilation

Run make in a shell in the **Release** folder.

## Usage

### Step 1 : Running Louvain executions to obtain cooccurences graphs
Running the Louvain algorithms **NbLouvain** times on the graph at the path **GraphFile**. The algorithm stores the results in **RUN/Expriment**. Cooccurences of nodes in communities detected by distinct Louvain runs are stored. **alpha** is the minimum number of cooccurences per total run (from 1 to 9). 

	**>**python simple-run.py -h

	usage: simple-run.py [-h] [-a {1,2,3,4,5,6,7,8,9}] [-r] [-s SEPARATOR]
		             GraphFile NbLouvain Experiment

	Run the louvain algorithm executions

	positional arguments:
	  **GraphFile**             The graph file to use
	  **NbLouvain**             The number of Louvain executions to run
	  **Experiment**            The experiment name. A folder will be created in RUN/
		                according to this name

	optional arguments:
	  -h, --help            show this help message and exit
	  -a {1,2,3,4,5,6,7,8,9}, --**alpha** {1,2,3,4,5,6,7,8,9}
		                The alpha minimum, namely the percentage of minimum
		                cooccurence in communities between two nodes to keep
		                them linked
	  -r, --**renum**          Mandatory if the graph labels do not start from 0
	  -s SEPARATOR, --**separator** SEPARATOR
		                Default separator is tab.

**Exemple :** **>**python simple-run.py exemple/graph graph_exemple 20 2

### Step 2 : Creating cores using cooccurence graphs of step 1
Using the cooccurences created at the previous step, the algorithm produces cores.

	**>**python simple-coeur.py graphe nomDossier

**Exemple :** **>**python simple-coeur.py exemple/graph graph_exemple

## Results

In **RUN/nomDossier/alpha/coeurs**, the cores are stored. Each file is identified by an id and represents a core, namely a connected component in the cooccurence graph corresponding to **alpha**.

In **RUN/nomDossier/alpha/**, the cooccurences graphs are stored.

## References
* **[1]** SEIFI, Massoud. Cœurs stables de communautés dans les graphes de terrain. 2012. Thèse de doctorat.
* **[2]** BLONDEL, Vincent D., GUILLAUME, Jean-Loup, LAMBIOTTE, Renaud, et al. Fast unfolding of communities in large networks. Journal of Statistical Mechanics: Theory and Experiment, 2008, vol. 2008, no 10, p. P10008.
* **[3]** SEIFI, Massoud, JUNIER, Ivan, ROUQUIER, Jean-Baptiste, et al. Stable community cores in complex networks. In : Complex Networks. Springer Berlin Heidelberg, 2013. p. 87-98.
