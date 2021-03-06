import argparse
import os, sys
import re
import shutil

parser = argparse.ArgumentParser(description='Run the louvain algorithm executions')
parser.add_argument('GraphFile', help='The graph file to use. One edge per line : src dst (weight). Automatically detect if weighted.', nargs=1)
parser.add_argument('NbLouvain', help="The number of Louvain executions to run", nargs=1, type=int)
parser.add_argument('Experiment', help="The experiment name. A folder will be created in RUN/ according to this name", nargs=1)
parser.add_argument('-a','--alpha', help="The alpha minimum, namely the percentage of minimum cooccurence in communities between two nodes to keep them linked", nargs=1, type=int,choices=[1,2,3,4,5,6,7,8,9] ,default=5)
parser.add_argument('-r', '--renum', action='store_true', help="Mandatory if the graph labels do not start from 0")
parser.add_argument('-s', '--separator', help="Default separator is tab.", default="\t")
args = parser.parse_args()

graph=args.GraphFile[0]
dossier=args.Experiment[0]
nbLouvain=args.NbLouvain[0]
alpha_min=args.alpha[0]
separator=args.separator
renum=args.renum

weighted=False

if not os.path.exists ("RUN/"):
	os.system("mkdir RUN/");

listAlpha=list(range(int(alpha_min),10))
listAlpha += (list(range(92, 99, 2)))
listAlpha.append(99)
if not os.path.exists ("RUN/" + dossier):
	os.system("mkdir RUN/" + dossier);
	os.system("mkdir RUN/" + dossier + "/Louvain")

#os.system("mkdir RUN/" + dossier + "-OLD");
#os.system("mkdir RUN/" + dossier + "-OLD/Louvain")

for alpha in listAlpha:
	if not os.path.exists ("RUN/" + dossier + "/" + str(alpha)):
		os.system("mkdir RUN/" + dossier + "/" + str(alpha))
		os.system("mkdir RUN/" + dossier + "/" + str(alpha) + "/coeurs")

	#os.system("mkdir RUN/" + dossier + "-OLD/" + str(alpha))
	#os.system("mkdir RUN/" + dossier + "-OLD/" + str(alpha) + "/coeurs")

# renum if needed to get a graph file with ids starting from 0
if renum:
	f = open(graph,'r')
	if "." in graph:
		graph_renum=graph[0:graph.rindex(".")]+"_renum"+graph[graph.rindex("."):]
	else:
		graph_renum=graph+"_renum"
        f_renum = open(graph_renum,'w')
	f_label=open(graph+"_labels","w")
	dico=dict()
	for ligne in f:
		w=""
		print ligne
		try:
        		src,dst = ligne.split(separator)
		except:
			src,dst,w = ligne.split(separator)
			weighted=True
                if src.strip() not in dico:
			dico[src.strip()]=len(dico)
		src=dico[src.strip()]
		if dst.strip() not in dico:
			dico[dst.strip()]=len(dico)
		dst=dico[dst.strip()]
      	        f_renum.write(str(src) + separator+ str(dst))
		if w != "":
			f_renum.write(separator+ w.strip())
               	f_renum.write("\n")
	f_renum.close()
        f.close()
	for src in dico:
		f_label.write(str(src)+"\t"+str(dico[src])+"\n")
	f_label.close()
	graph=graph_renum
else:
	f = open(graph,'r')
	for ligne in f:
		try:
        		src,dst = ligne.split(separator)
		except:
			src,dst,w = ligne.split(separator)
			weighted=True
		break
if weighted:
	print "./Release/CoeurCommunaute " + graph + " " + str(nbLouvain) + " " + dossier + " " + str(alpha_min)+ " weighted"
	os.system("./Release/CoeurCommunaute " + graph + " " + str(nbLouvain) + " " + dossier + " " + str(alpha_min)+ " weighted")
else:
	os.system("./Release/CoeurCommunaute " + graph + " " + str(nbLouvain) + " " + dossier + " " + str(alpha_min))
#os.system("./Release/CoeurCommunaute-Old " + graph + " " + nbLouvain + " " + dossier)
