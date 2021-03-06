/* Your code here! */
#include <vector>
#include "dsets.h"

//creats n unconnected root nodes at the end of the vector
void DisjointSets::addelements(int num)
{
	for (int i=0; i < num; i++) {
		node.push_back(-1);
	}
}

//find the set!!!!!! which the elem is in
int DisjointSets::find(int elem)
{
	if(node[elem] < 0) {
		return elem;
	}
	else {
		node[elem] = find(node[elem]);
		return find(node[elem]);
	}

}

//union a and b, union by size; smaller point at the larger; find the roots of its arguments before combinning, if two are the same, second point to the first
void DisjointSets::setunion(int a, int b)
{
	int first = find(a);
	int second = find(b);

	if (first == second) { 
		return;
	}

	int newsize = node[first] + node[second];
	if (node[first] <= node[second]) {//since its negative, the smaller the larger
		node[second] = first;
		node[first] = newsize;
	}
	else {
		node[first] = second;
		node[second] = newsize;
	}
}
