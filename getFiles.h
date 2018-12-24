#ifndef GETFILES_H
#define	GETFILES_H

#include <cstring>
#include <stack>

class Files {
private:
	const char* filename;

public:
	Files(const char*);
	~Files();
	const char* getFile();
	void openFile(const char*);
	struct Points {
		int x;
		int y;
		double distance;
		double angle;
	};
	void calculateAngles(Points[], int);
	void print(Points*, int);
	int lowestPoint(Points[], int);
	void mergeSort(Points[], int, int, int);
	void merge(Points*, int, int, int, int);
	void convexHull(Points*, int);
	int getDeterminant(Points, Points, Points);

};
#endif //FILES_H

