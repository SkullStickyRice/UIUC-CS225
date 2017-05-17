/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include "math.h"

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
//if (curDim < Dim && curDim >= 0) {

	if (first[curDim] == second[curDim]) {
		return first < second;
	}
	return first[curDim] < second[curDim];
    //return false;
//}

}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */

	int currDist = distance(target, currentBest);
	int potenDist = distance(target, potential);

	if (currDist == potenDist) {
		return potential < currentBest;
	}
	return potenDist < currDist; 
    //return false;
}

//helper function distance
template<int Dim>
int KDTree<Dim>::distance(const Point<Dim>& p, const Point<Dim>& q) const
{

	int distance = 0;
	for (int i=0; i<Dim; i++) {
		distance += pow(p[i]-q[i],2);
	}
	return distance;

}


template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */

	points = newPoints;
	KDTree_helper(0,newPoints.size()-1, 0); //left, right, dimension

}

template<int Dim>
void KDTree<Dim>::KDTree_helper(int a, int b, int dimension)
{
	if (a == b) {
		return;
	}
	int mid = (a+b)/2;
	quickSelect(a,b,dimension,mid);
	
	if (a < mid-1){
		KDTree_helper(a, mid-1, (dimension+1)%Dim);
	}
	if (b > mid+1){
		KDTree_helper(mid+1, b, (dimension+1)%Dim);
	}
}

template<int Dim>
void KDTree<Dim>::quickSelect(int left, int right, int dimension, int mid)
{
	if (left >= right) {
		return;
	}

	int pivotIndex = partition(left,right,mid,dimension);
	if (mid == pivotIndex) {
		return;
	}
	else if (mid < pivotIndex) {
		quickSelect(left,pivotIndex-1,dimension,mid);
	}
	else {
		quickSelect(pivotIndex+1,right,dimension,mid);
	}
	}
	
	


template<int Dim>
int KDTree<Dim>::partition(int left, int right, int pivotIndex, int dimension)
{
	Point<Dim> pivotValue = points[pivotIndex];
	Point<Dim> temp = points[right];
	
	points[right] = points[pivotIndex];
	points[pivotIndex] = temp;

	int storeIndex = left;
	for (int i=left; i<right; i++) {
		if (smallerDimVal(points[i],pivotValue,dimension)) {
			temp = points[storeIndex];
			points[storeIndex] = points[i];
			points[i] = temp;
			storeIndex++;
		}
	}
	
	temp = points[right];
	points[right] = points[storeIndex];
	points[storeIndex] = temp;
	return storeIndex;

}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo 
	Implement this function!
     */
	return NN_helper(0,points.size()-1,0,query);
	
   
}
template <int Dim>
Point<Dim> KDTree<Dim>::NN_helper(int left, int right, int dimension, const Point<Dim>& query) const
{
	Point<Dim> currentBest;
	
	if (left >= right) {
		return points[left];
	}
	
	int mid = (left+right)/2;
	
	if (smallerDimVal(points[mid], query, dimension)) {
		currentBest = NN_helper(mid+1, right, (dimension+1)%Dim,query);
	}
	else {
		currentBest = NN_helper(left,mid-1,(dimension+1)%Dim,query);
	}

	if (shouldReplace(query, currentBest,points[mid])) {
			currentBest = points[mid];
		}

	Point<Dim> temp;
	if (pow(query[dimension]-points[mid][dimension],2) <= distance(query, currentBest)) {
		if (smallerDimVal(points[mid], query, dimension)) {
			temp = NN_helper(left,mid-1,(dimension+1)%Dim,query);
		}
		else {
			temp = NN_helper(mid+1,right,(dimension+1)%Dim,query);
			}
		if (shouldReplace(query,currentBest,temp)) {
			currentBest = temp;
		}
	}

	return currentBest;
}

