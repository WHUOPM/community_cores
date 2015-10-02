import os, sys
import re
import shutil

if (len(sys.argv) < 3):
        print("python simple-coeur.py graphe nomDossier")

else:	

	graph=sys.argv[1]
	dossier=sys.argv[2]

	listTriangle=[1,2,3,4,5,6,7]	
	listAlpha=[1,2,3,4,5,6,7,8,9]	

	for triangle in listTriangle:
		for alpha in listAlpha:
			if(os.path.isfile("TRIANGLE-RUN/" + dossier + "/TYPE"  + str(triangle) + "/" + str(alpha) + "/Communities-" + graph)):
				if(os.system("rm TRIANGLE-RUN/"+dossier+"/TYPE"  + str(triangle) + "/" +str(alpha)+"/coeurs/*")):
					f = open("TRIANGLE-RUN/" + dossier + "/TYPE"  + str(triangle) + "/"   + str(alpha) + "/Communities-" + graph,'r')
					i=0
					for ligne in f:
				        	f_pos = open("TRIANGLE-RUN/"+dossier+"/TYPE"  + str(triangle) + "/" +str(alpha)+"/coeurs/" + str(i),'w')
					        l = ligne.split(",")
					        for node in l:
					                f_pos.write(node + "\n")
					        i=i+1
					f_pos.close()
					f.close()

				if(os.system("rm TRIANGLE-RUN/"+dossier+"/TYPE"  + str(triangle) + "/" +str(alpha)+"/coeurs-triangles/*")):
                                        f = open("TRIANGLE-RUN/" + dossier + "/TYPE"  + str(triangle) + "/"   + str(alpha) + "/Communities-Triangles-" + graph,'r')
                                        i=0
                                        for ligne in f:
                                                f_pos = open("TRIANGLE-RUN/"+dossier+"/TYPE"  + str(triangle) + "/" +str(alpha)+"/coeurs-triangles/" + str(i),'w')
                                                l = ligne.split(",")
                                                for node in l:
                                                        f_pos.write(node + "\n")
                                                i=i+1
                                        f_pos.close()
                                        f.close()

				if(os.system("rm TRIANGLE-RUN/"+dossier+"/TYPE"  + str(triangle) + "/" +str(alpha)+"/coeurs-origine/*")):
                                        f = open("TRIANGLE-RUN/" + dossier + "/TYPE"  + str(triangle) + "/"   + str(alpha) + "/Coeurs-Origine-" + graph,'r')
                                        i=0
                                        for ligne in f:
                                                f_pos = open("TRIANGLE-RUN/"+dossier+"/TYPE"  + str(triangle) + "/" +str(alpha)+"/coeurs-origine/" + str(i),'w')
                                                l = ligne.split(",")
                                                for node in l:
                                                        f_pos.write(node + "\n")
                                                i=i+1
                                        f_pos.close()
                                        f.close()

