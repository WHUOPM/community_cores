# Usage : coeur graphe_court nom_graphe graphe_chemin_absolu nombre_louvain

import os, sys
import re
import shutil

if(len(sys.argv) < 3):
        print("python simple-run.py graph [graph_renum] [separator] nomDossier nbLouvain")

else:

        # on recupere les arguments
        if(len(sys.argv) == 4):
                graph=sys.argv[1]
                dossier=sys.argv[2]
                nbLouvain=sys.argv[3]
        else:
                graph_ori=sys.argv[1]
                graph=sys.argv[2]
                separator=sys.argv[3]
                dossier=sys.argv[4]
                nbLouvain=sys.argv[5]

	listTriangle=[1,2,3,4,5,6,7]
        listAlpha=[1,2,3,4,5,6,7,8,9]

	os.system("mkdir TRIANGLE-RUN/" + dossier);
	for triangle in listTriangle:
		os.system("mkdir TRIANGLE-RUN/" + dossier + "/" + "TYPE" + str(triangle))
       		os.system("mkdir TRIANGLE-RUN/" + dossier + "/" + "TYPE" + str(triangle) + "/Louvain")
		for alpha in listAlpha:
               	 	os.system("mkdir TRIANGLE-RUN/" + dossier + "/" + "TYPE" + str(triangle) + "/" + str(alpha))
                	os.system("mkdir TRIANGLE-RUN/" + dossier + "/" + "TYPE" + str(triangle) + "/" + str(alpha) + "/coeurs")
			os.system("mkdir TRIANGLE-RUN/" + dossier + "/" + "TYPE" + str(triangle) + "/" + str(alpha) + "/coeurs-triangles")
       			os.system("mkdir TRIANGLE-RUN/" + dossier + "/" + "TYPE" + str(triangle) + "/" + str(alpha) + "/coeurs-origine")
			os.system("mkdir TRIANGLE-RUN/" + dossier + "/" + "TYPE" + str(triangle) + "/" + str(alpha) + "/coeurs-origine-triangles")
	# renum uniquement si demande
       	if(len(sys.argv) >= 6):
		f = open(graph_ori,'r')
       		f_renum = open(graph,'w')
               	for ligne in f:
                       	l = ligne.split(separator)
                       	for node in l:
                               	node_renum = int(node) - 1
                               	f_renum.write(str(node_renum) + separator)
                       	f_renum.write("\n")
               	f_renum.close()
	       	f.close()

	for triangle in listTriangle:
		os.system("./Release/Triangles " + graph + " " + nbLouvain + " " + dossier + " " + str(triangle))
