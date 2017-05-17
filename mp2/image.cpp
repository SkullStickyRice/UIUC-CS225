#include "image.h"

void Image::flipleft()
{
	
	for (size_t x=0; x < (this->width()/2); x++) {
		for (size_t y=0; y < (this->height()); y++) {
			RGBAPixel temp = *(*this)(x,y);
			*(*this)(x,y) = *(*this)(this->width()-x-1,y);
			*(*this)(this->width()-x-1,y) = temp;
		}
	}
}

void Image::adjustbrightness(int r, int g, int b)
{
	for(unsigned int x=0; x < (this->width()); x++) {
		for (unsigned int y=0; y < (this->height()); y++) {

			RGBAPixel *temp = (*this)(x,y);

			if (temp -> red+r > 255)
				temp -> red = 255;
			else if (temp -> red+r < 0)
				temp -> red = 0;
			else temp -> red = temp -> red+r;

			if (temp -> green+g > 255)
				temp -> green = 255;
			else if (temp -> green+g < 0)
				temp -> green = 0;
			else temp-> green = temp -> green+g;

			if (temp -> blue+b > 255)
				temp -> blue = 255;
			else if (temp -> blue+b < 0)
				temp -> blue = 0;
			else temp-> blue = temp -> blue+b;

		}
	}
}

void Image::invertcolors()
{
	for(size_t x=0; x < (this->width()); x++) {
		for (size_t y=0; y < (this->height()); y++) {

			RGBAPixel *temp = (*this)(x,y);
			temp -> red = 255 - temp -> red;
			temp -> green = 255 - temp -> green;
			temp -> blue = 255 -temp -> blue;
			

		}
	}
}
