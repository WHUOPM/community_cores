import argparse
import os, sys
import re
import shutil

parser = argparse.ArgumentParser(description='Get the max alpha core for each node')
parser.add_argument('GraphFile', help='The graph file to use. One edge per line : src dst (weight). Automatically detect if weighted.', nargs=1)
parser.add_argument('Experiment', help="The experiment name. A folder with this name should exist in RUN/", nargs=1)
parser.add_argument('-s', '--separator', help="Default separator is tab.", default="\t")
args = parser.parse_args()

graph=args.GraphFile[0]
dossier=args.Experiment[0]
separator=args.separator

	
nodes=dict()
graph=open(sys.argv[1])
for ligne in graph:
	try:
		src, dst =ligne.split(separator)
	except:
		src,dst,weight=ligne.split(separator)
	src=int(src)
	dst=int(dst.strip())
	nodes[src]=-1
	nodes[dst]=-1

listAlpha=os.listdir('RUN/'+dossier)
listAlpha.sort()
try:
	listAlpha.remove("Louvain")
	listAlpha.remove("maxcore")
except:
	pass
for alpha in listAlpha:
	listCoeur=os.listdir('RUN/'+dossier+"/"+alpha+"/coeurs/")
	for coeur in listCoeur:
		coeur_file=open('RUN/'+dossier+"/"+alpha+"/coeurs/"+coeur)
		for ligne in coeur_file:
			try:
				nodes[int(ligne.strip())]=alpha
			except:
				pass
resultat=open("RUN/"+dossier+"/maxcore", "w")
for node in nodes:
	resultat.write(str(node)+" "+str(nodes[node])+"\n")
resultat.close()
	
