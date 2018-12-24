#include "getFiles.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <math.h>
#include <stack>


#define PI 3.1415

using namespace std;

Files::Files(const char* name) :filename(name) {

}

Files::~Files() {
}

const char* Files::getFile() {

	return filename;
}

void Files::openFile(const char* fileName) {

	int count = 0;
	Points info[25];
	struct Points data;
	string line;
	ifstream inFile;

	inFile.open(fileName);
	if (!inFile) {
		printf("File does not exist \n");
	}
	else {
		while (getline(inFile, line)) {
			istringstream iss(line);
			iss >> data.x;
			iss >> data.y;
			info[count] = data;
			count++;
		}
	}
	calculateAngles(info, count);
	inFile.close();
}

int Files::lowestPoint(Points coordinates[], int count) {
	int lowest = 0;
	for (int i = 1; i < count; i++) {
		if (coordinates[i].y < coordinates[lowest].y) {
			lowest = i;
		}
		else if (coordinates[i].y == coordinates[lowest].y) {
			if (coordinates[i].x < coordinates[lowest].x)
				lowest = i;
		}
	}
	return lowest;
}

void Files::calculateAngles(Points coordinates[], int count) {

	int lowest = lowestPoint(coordinates, count);

	// Swap the content at index[0] with index [lowest]
	Points firstCoordinate = coordinates[lowest];
	coordinates[lowest] = coordinates[0];
	coordinates[0] = firstCoordinate;
	coordinates[0].distance = 0;
	coordinates[0].angle = 0;


	for (int i = 1; i < count; i++) {
		int x_vector = coordinates[i].x - coordinates[0].x;
		int y_vector = coordinates[i].y - coordinates[0].y;
		double slope = sqrt(pow(x_vector, 2) + pow(y_vector, 2));
		coordinates[i].distance = slope;
		coordinates[i].angle = atan2(y_vector, x_vector) * (180 / PI);
	}

	mergeSort(coordinates, 1, count - 1, count);
	convexHull(coordinates, count);
}

void Files::print(Points* data, int count) {

	const char* filename = getFile();
	printf("%s%s\n", "   ", filename);
	printf("---------------\n");
	for (int i = 0; i < count; i++) {
		printf("%4i%s%2i\n\n", data[i].x, " , ", data[i].y);
	}
	printf("\n");
}

void Files::mergeSort(Points data[], int low, int high, int count) {

	if (low < high) {
		int mid = low + (high - low) / 2;
		mergeSort(data, low, mid, count);
		mergeSort(data, mid + 1, high, count);
		merge(data, low, high, mid, count);
	}
}

void Files::merge(Points *coordinates, int low, int high, int mid, int count) {

	int leftArraySize = mid - low + 1;
	int rightArraySize = high - mid;

	// Temp arrays
	Points *leftArray = new Points[leftArraySize];
	Points *rightArray = new Points[rightArraySize];


	// Making Left sub array
	for (int i = 0; i < leftArraySize; i++) {
		leftArray[i] = coordinates[low + i];
	}

	// Making right sub array
	for (int i = 0; i < rightArraySize; i++) {
		rightArray[i] = coordinates[mid + 1 + i];
	}

	int i = 0, j = 0, k = low;

	// Making comparisions
	while (i < leftArraySize && j < rightArraySize) {

		if (leftArray[i].angle <= rightArray[j].angle) {
			coordinates[k] = leftArray[i];
			i++;
		}
		else {
			coordinates[k] = rightArray[j];
			j++;
		}
		k++;
	}

	// Copying the left overs from the left sub array back into original array
	while (i < leftArraySize) {
		coordinates[k] = leftArray[i];
		i++; k++;
	}

	// Copying the left overs from the right sub array back into original array
	while (j < rightArraySize) {
		coordinates[k] = rightArray[j];
		j++; k++;
	}

	delete rightArray; delete leftArray;
}

void Files::convexHull(Points* coordinates, int SIZE) {

	stack<Points>nStack;

	int i = 0, determinate, stackSize;

	Points nextToTop, top;

	// Adding the first two elements to the stack
	for (i; i < 2; i++) {
		nStack.push(coordinates[i]);
	}

	while (i < SIZE) {

		// Popping the first two structures to pass into getDeterminant(coordinates[i], top, nextToTop)
		top = nStack.top();
		nStack.pop();
		nextToTop = nStack.top();
		nStack.pop();

		// Calculating the determinate
		determinate = getDeterminant(coordinates[i], top, nextToTop);

		// Cases for find the convex hull
		if (determinate > 0) {
			nStack.push(nextToTop);
			nStack.push(top);
			nStack.push(coordinates[i]);
		}
		else if (determinate < 0) {
			nStack.push(nextToTop);
			i--;
		}
		else if (determinate == 0) {

			// Take the point with the longest distance
			double newPointDistance = sqrt((pow((coordinates[i].x - nextToTop.x), 2) + (pow((coordinates[i].y - nextToTop.y), 2))));
			double topStackPointDistance = sqrt((pow((top.x - nextToTop.x), 2) + (pow((top.y - nextToTop.y), 2))));

			if (newPointDistance > topStackPointDistance) {
				nStack.push(nextToTop);
				nStack.push(coordinates[i]);
			}
		}
		i++;
	}

	stackSize = (int)nStack.size();

	Points* stack = new Points[stackSize];

	// Adding points in reverse to an array in order to print in non-decreasing order
	if (!nStack.empty()) {
		for (int i = nStack.size() - 1; i >= 0; i--) {
			stack[i] = nStack.top();
			nStack.pop();
		}
	}
	// Printing final stack
	print(stack, stackSize);

	delete stack;
}

int Files::getDeterminant(Points top, Points middle, Points bottom) {
	int x1_vector = bottom.x - middle.x;
	int y1_vector = bottom.y - middle.y;

	int x2_vector = bottom.x - top.x;
	int y2_vector = bottom.y - top.y;

	return((x1_vector*y2_vector) - (x2_vector*y1_vector));
}
