import os, sys
import re
import shutil

if (len(sys.argv) < 2):
        print("python simple-density.py folder")

else:
	dossier=sys.argv[1]
	listAlpha = [1,2,3,4,5,6,7,8,9]
	listTriangle = [1,2,3,4,5,6,7]
	for triangle in listTriangle:
		for alpha in listAlpha:
			os.system("rm TRIANGLE-RUN/" + dossier + "/TYPE"  + str(triangle) + "/"  + str(alpha) + "/coeurs-triangles/measures")
			for files in sorted(os.listdir("TRIANGLE-RUN/" + dossier + "/TYPE"  + str(triangle) + "/"  + str(alpha) + "/coeurs-triangles/")):
				os.system("./density/density TRIANGLE-RUN/" + dossier + "/TYPE"  + str(triangle) + "/" + "Louvain/triangles.bin TRIANGLE-RUN/" + dossier + "/TYPE"  + str(triangle) + "/" + "Louvain/triangles.weight TRIANGLE-RUN/" + dossier + "/TYPE"  + str(triangle) + "/"  + str(alpha) + "/coeurs-triangles/" + files + " >> TRIANGLE-RUN/" + dossier + "/TYPE"  + str(triangle) + "/"  + str(alpha) + "/coeurs-triangles/measures")

