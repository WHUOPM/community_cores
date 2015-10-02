import os, sys
import re
import shutil

if (len(sys.argv) < 3):
        print("python simple-coeur.py graphe nomDossier")

else:	

	graph=sys.argv[1].split("/")[len(sys.argv[1].split("/")) - 1]
	dossier=sys.argv[2]
	
	listAlpha=[1,2,3,4,5,6,7,8,9]	

	for alpha in listAlpha:
		if(os.path.isfile("RUN/" + dossier + "/"  + str(alpha) + "/Communities_" + graph)):
			if(os.system("rm RUN/"+dossier+"/"+str(alpha)+"/coeurs/*")):
				f = open("RUN/" + dossier + "/"  + str(alpha) + "/Communities_" + graph,'r')
				i=0
				for ligne in f:
			        	f_pos = open("RUN/"+dossier+"/"+str(alpha)+"/coeurs/" + str(i),'w')
				        l = ligne.split(",")
				        for node in l:
				                f_pos.write(node + "\n")
				        i=i+1
				f_pos.close()
				f.close()


