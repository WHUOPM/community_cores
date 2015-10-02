// File: main_community.cpp
// -- community detection, sample main file
//-----------------------------------------------------------------------------
// Community detection 
// Based on the article "Fast unfolding of community hierarchies in large networks"
// Copyright (C) 2008 V. Blondel, J.-L. Guillaume, R. Lambiotte, E. Lefebvre
//
// This program must not be distributed without agreement of the above mentionned authors.
//-----------------------------------------------------------------------------
// Author   : E. Lefebvre, adapted by J.-L. Guillaume
// Email    : jean-loup.guillaume@lip6.fr
// Location : Paris, France
// Time	    : February 2008
//-----------------------------------------------------------------------------
// see readme.txt for more details

#include <stdlib.h>
#include <fstream>

#include "graph_binary.h"

using namespace std;

int type       = UNWEIGHTED;

void
usage(char *prog_name, const char *more) {
  cerr << more;
  cerr << "usage: " << prog_name << " input_binary_graphfile weight_file input_subgraph_to_evaluate" << endl;
  exit(0);
}

void
parse_args(int argc, char **argv) {
  if (argc < 2)
    usage(argv[0], "Bad arguments number\n");

  
}



int
main(int argc, char **argv) {
  parse_args(argc, argv);
 
  Graph* g = NULL;
  g = new Graph(argv[1], argv[2], type);
  (*g).densite_weighted(argv[3]);
  //(*g).display();
}

