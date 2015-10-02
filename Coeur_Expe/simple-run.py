# Usage : coeur graphe_court nom_graphe graphe_chemin_absolu nombre_louvain

import os, sys
import re
import shutil

if (len(sys.argv) < 5):
        print("python simple-run.py graph [graph_renum] [separator] nomDossier nbLouvain alpha_entier")

else:

	# on recupere les arguments
	if(len(sys.argv) == 5):
		graph=sys.argv[1]
		dossier=sys.argv[2]
		nbLouvain=sys.argv[3]
		alpha_min=sys.argv[4]
	else:
		graph=sys.argv[2]
		separator=sys.argv[3]
		dossier=sys.argv[4]
		nbLouvain=sys.argv[5]
		alpha_min=sys.argv[6]

        listAlpha=list(range(int(alpha_min),10))
        os.system("mkdir RUN/" + dossier);
	os.system("mkdir RUN/" + dossier + "/Louvain")
        
	os.system("mkdir RUN/" + dossier + "-OLD");
	os.system("mkdir RUN/" + dossier + "-OLD/Louvain")

	for alpha in listAlpha:
                os.system("mkdir RUN/" + dossier + "/" + str(alpha))
                os.system("mkdir RUN/" + dossier + "/" + str(alpha) + "/coeurs")

		os.system("mkdir RUN/" + dossier + "-OLD/" + str(alpha))
		os.system("mkdir RUN/" + dossier + "-OLD/" + str(alpha) + "/coeurs")

	# renum uniquement si demande
	if(len(sys.argv) >= 6):
		f = open(sys.argv[1],'r')
	        f_renum = open(sys.argv[2],'w')
        	for ligne in f:
                	l = ligne.split("\t")
	                for node in l:
        	                node_renum = int(node) - 1
              	        	f_renum.write(str(node_renum) + "\t")
	               	f_renum.write("\n")
		f_renum.close()
	        f.close()

        os.system("./Release/CoeurCommunaute " + graph + " " + nbLouvain + " " + dossier + " " + alpha_min)
	#os.system("./Release/CoeurCommunaute-Old " + graph + " " + nbLouvain + " " + dossier)
