#ifndef SCENE_H
#define SCENE_H

#include "image.h"
#include "png.h"


//#include <iostream>
//using namespace std;

class Scene 
{
	public:
	/**
	*Initializes this Scene object to be able to hold "max" number of images with indices 0 through max_1
	*/ 
	Scene (int max);

	/**
	*Frees all space that was dynamically allocated by this scene
	*/
	~Scene ();
	
	/**
	*The copy constructor makes this scene an independent copy of the source.
	*/
	Scene (const Scene & source);
	
	/**
	*(1) checks for self assignment, (2) then deletes everything this Scene has allocated, (3) then makes this Scene an independent copy of the source, (4) then returns a reference to the current instance.
	*/
	const Scene & operator = (const Scene & source); 

	/**
	*Modifies the size of the array of Image pointers without changing their indices.
	*/	
	void changemaxlayers (int newmax);
	
	/**
	*This function will add a pucture to the scene, by placing it in the array cell correspoinding to the given index, and storing its x coordinate and y coordinate
	*/
	void addpicture (const char* FileName, int index, int x, int y);

	/**
	*Moves an Image from one layer to another
	*/
	void changelayer (int index, int newindex);
	
	/**
	*CHanges the x and y coordinates of the Image in the specified layer. 
	*/
	void translate(int index, int xcoord, int ycoord);

	/**
	*Deletes the Image at the given index
	*/
	void deletepicture (int index);

	/**
	*This function will return a ponter to the IMage at the specified index, not a copy ot it
	*/
	Image *getpicture (int index) const;

	/**
	*Draws the whole scene on one Image and returns that Image by value.
	*/
	Image drawscene() const;

	
	private:
	Image **theImage;
	int *xcoords;
	int *ycoords;
	int imax;
	void clear();
	void copy(const Scene &source);




};
#endif 
