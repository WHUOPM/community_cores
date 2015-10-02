import os, sys
import re
import shutil

if (len(sys.argv) < 2):
        print("python simple-density.py folder")

else:
	dossier=sys.argv[1]
	listAlpha = [1,2,3,4,5,6,7,8,9]
	for alpha in listAlpha:
		os.system("rm RUN/" + dossier + "/" + str(alpha) + "/coeurs/measures")
		for files in sorted(os.listdir("RUN/" + dossier + "/" + str(alpha) + "/coeurs/")):
			os.system("./density/density RUN/" + dossier + "/Louvain/graph.bin RUN/" + dossier + "/" + str(alpha) + "/coeurs/" + files + " >> RUN/" + dossier + "/" + str(alpha) + "/coeurs/measures")
	print "./density/density RUN/" + dossier + "/Louvain/graph.bin RUN/" + dossier + "/" + str(alpha) + "/coeurs/" + files + " >> RUN/" + dossier + "/" + str(alpha) + "/coeurs/measures"
