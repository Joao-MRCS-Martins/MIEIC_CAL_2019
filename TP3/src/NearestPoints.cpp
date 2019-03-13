/*
 * NearestPoints.cpp
 */

#include <limits>
#include <thread>
#include <algorithm>
#include <cmath>
#include "NearestPoints.h"
#include "Point.h"

const double MAX_DOUBLE = std::numeric_limits<double>::max();

Result::Result(double dmin, Point p1, Point p2) {
	this->dmin = dmin;
	this->p1 = p1;
	this->p2 = p2;
}

Result::Result() {
	this->dmin = MAX_DOUBLE;
	this->p1 = Point(0,0);
	this->p2 = Point(0,0);
}

/**
 * Auxiliary functions to sort vector of points by X or Y axis.
 */
static void sortByX(vector<Point> &v, int left, int right)
{
	std::sort(v.begin( ) + left, v.begin() + right + 1,
		[](Point p, Point q){ return p.x < q.x || (p.x == q.x && p.y < q.y); });
}

static void sortByY(vector<Point> &v, int left, int right)
{
	std::sort(v.begin( ) + left, v.begin() + right + 1,
		[](Point p, Point q){ return p.y < q.y || (p.y == q.y && p.x < q.x); });
}

/**
 * Brute force algorithm O(N^2).
 */
Result nearestPoints_BF(vector<Point> &vp) {
	Result res;

	Point p1,p2;
	double dmin=MAX_DOUBLE;
	for(int i =0; i < vp.size(); i++) {
		for(int j = i+1; j < vp.size();j++) {
			if(vp[i].distance(vp[j]) < dmin) {
				dmin = vp[i].distance(vp[j]);
				p1 = vp[i];
				p2 = vp[j];
			}
		}
	}
	res.dmin = dmin;
	res.p1=p1;
	res.p2=p2;
	return res;
}

/**
 * Improved brute force algorithm, that first sorts points by X axis.
 */
Result nearestPoints_BF_SortByX(vector<Point> &vp) {
	Result res;
	sortByX(vp, 0, vp.size()-1);
	Point p1,p2;
	double dmin=MAX_DOUBLE;
	for(int i =0; i < vp.size(); i++) {
		for(int j = i+1; j < vp.size();j++) {
			if(vp[i].distance(vp[j]) < dmin) {
				dmin = vp[i].distance(vp[j]);
				p1 = vp[i];
				p2 = vp[j];
			}
		}
	}
	res.dmin = dmin;
	res.p1=p1;
	res.p2=p2;
	return res;
}


/**
 * Auxiliary function to find nearest points in strip, as indicated
 * in the assignment, with points sorted by Y coordinate.
 * The strip is the part of vp between indices left and right (inclusive).
 * "res" contains initially the best solution found so far.
 */
static void npByY(vector<Point> &vp, int left, int right, Result &res)
{
	// TODO
}

/**
 * Recursive divide and conquer algorithm.
 * Finds the nearest points in "vp" between indices left and right (inclusive),
 * using at most numThreads.
 */
static Result np_DC(vector<Point> &vp, int left, int right, int numThreads) {
	// Base case of two points
	if((right - left) == 1) {
		Result res;
		res.p1 = vp[left];
		res.p2 = vp[right];
		res.dmin = res.p1.distance(res.p2);
		return res;
	}

	// Base case of a single point: no solution, so distance is MAX_DOUBLE
	if((right - left) == 0) {
		Result res;
		res.p1 = vp[left];
		res.p2 = vp[left];
		res.dmin = MAX_DOUBLE;
		return res;
	}

	// Divide in halves (left and right) and solve them recursively,
	// possibly in parallel (in case numThreads > 1)
	int mid = (left + right)/2;
	Result esq = np_DC(vp,left,mid,numThreads);
	Result dir = np_DC(vp,mid+1,right,numThreads);

	// Select the best solution from left and right
	if(esq.dmin < dir.dmin)
		return esq;

	// Determine the strip area around middle point
	// TODO

	// Order points in strip area by Y coordinate
	// TODO

	// Calculate nearest points in strip area (using npByY function)
	// TODO

	// Reorder points in strip area back by X coordinate
	//TODO

	//return res;
}


/**
 * Defines the number of threads to be used.
 */
static int numThreads = 1;
void setNumThreads(int num)
{
	numThreads = num;
}

/*
 * Divide and conquer approach, single-threaded version.
 */
Result nearestPoints_DC(vector<Point> &vp) {
	sortByX(vp, 0, vp.size() -1);
	return np_DC(vp, 0, vp.size() - 1, 1);
}


/*
 * Multi-threaded version, using the number of threads specified
 * by setNumThreads().
 */
Result nearestPoints_DC_MT(vector<Point> &vp) {
	sortByX(vp, 0, vp.size() -1);
	return np_DC(vp, 0, vp.size() - 1, numThreads);
}
