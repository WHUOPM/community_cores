/*
 * Diagraph.cpp
 *
 *  Created on: 1 avr. 2014
 *      Author: ten
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include "Digraph.hpp"
#include "Edge.hpp"
#include "Triangle.hpp"
#include "nodeDeg.hpp"


 using namespace std;


 Digraph::~Digraph() {

 }

 void Digraph::loadEdgeList(string data){
 	this->neigh = vector<Edge>(0);

 	FILE* file = fopen(data.c_str(), "r");
 	int source, target, weight;
 	int scanfReturn;
 	while ((scanfReturn = fscanf(file,"%d %d", &source, &target)) != EOF) {
 		if(scanfReturn == 2){
				
 			this->dim=max3(this->dim,source,target);
 			if (source>target) {
 				this->neigh.push_back(Edge(source, target, 1));
 			}
 			else {
 				this->neigh.push_back(Edge(target, source, 2));
 			}
 			this->nbEdge++;
 		}
 	}
 	fclose(file);

 	if(!this->neigh.empty()){
 		this->dim++;
 		this->relabel();
 		//this->triplet1_count();
 	}


 	this->genDegcum();

 }

 unsigned int Digraph::max3(unsigned int x, unsigned int y, unsigned int z) {
 	unsigned int max = x;

 	if (y > max) {
 		max = y;
 	}

 	if (z > max) {
 		max = z;
 	}

 	return max;
 }

 ostream& operator<<( ostream &flux, std::vector<Edge> const& edgeList )
 {
 	for(unsigned int i=0; i<edgeList.size(); i++){
 		flux << edgeList[i] << " | ";
 	}
 	return flux;
 }

 unsigned long int Digraph::getDim(){
 	return this->dim;
 }

 vector<Edge> Digraph::getEdgeList(){
 	return this->neigh;
 }

 void Digraph::genDegcum(){
 	vector<unsigned int> deg(this->dim);
 	this->degcum.resize(this->dim+1);
 	for(unsigned int i=0; i<this->nbEdge; i++){
 		deg[this->neigh[i].getSource()]++;
 	}

 	unsigned int i;
 	for(i=1; i<this->dim+1; i++){
 		this->degcum[i] = deg[i-1] + this->degcum[i-1];
 	}

 	deg.clear();
 	deg.shrink_to_fit();
 }

 std::vector<unsigned long int> Digraph::getDegcum(){
 	return this->degcum;
 }

 vector<Triangle> Digraph::triangle_count(){
 	vector<Triangle> vecT(0);

 	unsigned long int n=this->dim, i, j, k, u, v, u2, v2;
 	for (u=0;u<n;u++) {
 		for (i=this->degcum[u];i<this->degcum[u+1];i++) {
 			v=this->neigh[i].getTarget();
 			j=this->degcum[u];
 			k=this->degcum[v];
 			u2=this->neigh[j].getTarget();
 			v2=this->neigh[k].getTarget();
 			while (j<this->degcum[u+1] && k<this->degcum[v+1]) {
 				if (u2>v2) {v2=this->neigh[++k].getTarget(); continue;}
 				if (v2>u2) {u2=this->neigh[++j].getTarget(); continue;}
 				if(evo){
 					int type = identifyTypeTriangle(this->neigh[i].getDirection(), this->neigh[k].getDirection(), this->neigh[j].getDirection());
 					Triangle t = Triangle(this->neigh[i].getSource(), max(this->neigh[i].getTarget(), this->neigh[j].getTarget()), min(this->neigh[j].getTarget(), this->neigh[i].getTarget()), type);
 					this->typeTriangle[type]++;
 					vecT.push_back(t);
 				}

 				else
 					this->typeTriangle[identifyTypeTriangle(this->neigh[i].getDirection(), this->neigh[k].getDirection(), this->neigh[j].getDirection())]++;

 				u2=this->neigh[++j].getTarget();
 				v2=this->neigh[++k].getTarget();
 			}
 		}
 	}
 	this->triplet2Count();

	for(int i = 0; i < typeTriangle.size(); i++) {

		cout << "nombre de triangles de type " << i << " : " << typeTriangle[i] << endl;

	}

 	return vecT;
 }



 unsigned int Digraph::getNbEdge(){
 	return this->nbEdge;
 }

 int Digraph::identifyTypeTriangle(int i, int j, int k){
	//	int i = e1.getDirection();
	//	int j = e2.getDirection();
	//	int k = e3.getDirection();

 	if (i==1) {
 		if (j==1) {if (k==1) return 0; if (k==2) return 1; return 4;}
 		if (j==2) {if (k==1) return 0; if (k==2) return 0; return 3;}
 		if (k==1) return 2; if (k==2) return 4; return 5;
 	}
 	if (i==2) {
 		if (j==1) {if (k==1) return 0; if (k==2) return 0; return 2;}
 		if (j==2) {if (k==1) return 1; if (k==2) return 0; return 4;}
 		if (k==1) return 4; if (k==2) return 3; return 5;
 	}
 	if (j==1) {if (k==1) return 3; if (k==2) return 4; return 5;}
 	if (j==2) {if (k==1) return 2; if (k==2) return 2; return 5;}
 	if (k==1) return 5; if (k==2) return 5; return 6;


 }

 std::vector<unsigned long int> Digraph::getTypeTriangle(){
 	return this->typeTriangle;
 }
 std::vector<unsigned long int> Digraph::getTypeWedge(){
 	return this->typeWedge;
 }

 void Digraph::triplet2Count(){
 	this->typeTripler2[2] = this->typeWedge[2]- 3*this->typeTriangle[1]- this->typeTriangle[0]- this->typeTriangle[4];
 	this->typeTripler2[0] = this->typeWedge[0]-this->typeTriangle[0]-this->typeTriangle[2];
 	this->typeTripler2[1] = this->typeWedge[1]-this->typeTriangle[0]-this->typeTriangle[3];
 	this->typeTripler2[3] = max((unsigned long int)0, (unsigned long int)(this->typeWedge[3]-2*this->typeTriangle[2]-this->typeTriangle[4]-this->typeTriangle[5]));
 	this->typeTripler2[4] = max((unsigned long int)0, (unsigned long int)(this->typeWedge[4]-2*this->typeTriangle[3]-this->typeTriangle[4]-this->typeTriangle[5]));
 	this->typeTripler2[5] = max((unsigned long int)0, (unsigned long int)(this->typeWedge[5]-3*this->typeTriangle[6]-this->typeTriangle[5]));
 }

 void Digraph::triplet1_count(){
 	unsigned int simpleIn = 0;
 	unsigned int simpleOut = 0;
 	vector <unsigned long int> in((this->dim));
 	vector <unsigned long int> out(this->dim);
 	vector <unsigned long int> bi(this->dim);
 	for(unsigned int j=0; j<this->nbEdge; j++){
 		if (this->neigh[j].getDirection() == 3){

 			bi[this->neigh[j].getSource()]++;
 			bi[this->neigh[j].getTarget()]++;
 		}
 		else if (this->neigh[j].getDirection() == 1){
 			out[this->neigh[j].getSource()]++;
 			in[this->neigh[j].getTarget()]++;
 		}
 		else if(this->neigh[j].getDirection() == 2){
 			in[this->neigh[j].getSource()]++;
 			out[this->neigh[j].getTarget()]++;
 		}
 	}

 	for (unsigned int i=0;i<this->dim;i++) {
 		simpleIn += in[i];
 		simpleOut += out[i];
 		this->doubleEdge += bi[i];

 		typeWedge[2]+=(long unsigned int)in[i]*out[i];
 		typeWedge[0]+=((long unsigned int)out[i]*(out[i]-1))/2;
 		typeWedge[1]+=((long unsigned int)in[i]*(in[i]-1))/2;
 		typeWedge[3]+=(long unsigned int)bi[i]*in[i];
 		typeWedge[4]+=(long unsigned int)bi[i]*out[i];
 		typeWedge[5]+=((long unsigned int)bi[i]*(bi[i]-1))/2;

 	}
 	this->doubleEdge /= 2;
 	this->simpleEdge = simpleIn;

 }

 vector<unsigned long int> Digraph::getTriplet2(){
 	return this->typeTripler2;
 }

 unsigned int Digraph::getNbSimpleEdge(){
 	return this->simpleEdge;
 }
 unsigned int Digraph::getNbDoubleEdge(){
 	return this->doubleEdge;
 }

 void Digraph::relabel(){
 	vector<nodeDeg> node_deg_list(this->dim);

//	cout << "Sorting neigh" << endl;
 	std::sort(this->neigh.begin(), this->neigh.end());

 	for(unsigned long int i=0; i<this->dim; i++){
 		node_deg_list[i].node = i;
 	}

//	cout << "node_deg_list initialized" << endl;
 	unsigned int j=0;
 	unsigned int j2=0;

 	while(j<nbEdge){
 		if(j>0 && !(neigh[j]==neigh[j-1])){
 			j2++;
 			neigh[j2] = neigh[j];
 			node_deg_list[neigh[j2].getSource()].deg++;
 			node_deg_list[neigh[j2].getTarget()].deg++;
 		}
 		else if(j>0 && neigh[j]==neigh[j-1]){
 			if(neigh[j2].getDirection() == 3 || (neigh[j].getDirection() != neigh[j-1].getDirection())){
 				neigh[j2].setDirection(3);
 			}
 			else{
 				node_deg_list[neigh[j2].getSource()].deg++;
 				node_deg_list[neigh[j2].getTarget()].deg++;
 			}

 		}
 		else{
 			node_deg_list[neigh[j2].getSource()].deg++;
 			node_deg_list[neigh[j2].getTarget()].deg++;
 		}

 		j++;
 	}
 	j2++;
 	this->nbEdge = j2;




 	unsigned int i = this->neigh.size()-1;
 	while(i > nbEdge-1){
 		neigh.pop_back();
 		i--;
 	}
 	this->neigh.shrink_to_fit();
 	if(!evo)
 		std::sort(node_deg_list.begin(), node_deg_list.end(), std::greater<nodeDeg>());

 	vector<unsigned long int> new_label(this->dim);
 	ofstream relab(pathRelabFile, ios::out);
 	i=0;
 	for (j=0; j<this->dim; j++) {
 		if (node_deg_list[j].deg!=0){
 			new_label[node_deg_list[j].node]=i;
 			relab << node_deg_list[j].node << " " << i << endl;
 			i++;
 		}
 	}
 	relab.close();

 	this->dim = i;
 	node_deg_list.clear();
 	node_deg_list.shrink_to_fit();


 	for (unsigned int j=0;j<this->nbEdge;j++) {
 		unsigned int source=new_label[this->neigh[j].getSource()];
 		unsigned int target=new_label[this->neigh[j].getTarget()];
 		if (source<target) {
 			this->neigh[j].setSource(target);
 			this->neigh[j].setTarget(source);
 			if (this->neigh[j].getDirection()==1) this->neigh[j].setDirection(2);
 			else if (this->neigh[j].getDirection()==2) this->neigh[j].setDirection(1);
 		}
 		else {
 			this->neigh[j].setSource(source);
 			this->neigh[j].setTarget(target);
 		}
 	}
//	cout << "list edge new label done" << endl;
 	new_label.clear();
 	new_label.shrink_to_fit();

 	std::sort(this->neigh.begin(), this->neigh.end());
	//	for(unsigned int i=0; i<neigh.size(); i++){ cout << (this->neigh[i]) << endl;}
	//	cout << "sorting done" << endl;
 }

 void Digraph::setEdgeList(vector<Edge> _edgeList){
 	this->neigh = _edgeList;
 	this->relabel();
 	this->genDegcum();
 }
