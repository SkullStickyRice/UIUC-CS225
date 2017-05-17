#include <algorithm>
#include <iostream>

#include "rgbapixel.h"
#include "png.h"

using namespace std;

PNG rotate(PNG inImage)
{	
	PNG outImage = PNG(size_t (inImage.width()), size_t (inImage.height()));

	for (size_t x=0; x < inImage.width(); x++) {
		for (size_t y=0; y < inImage.height(); y++) {
			RGBAPixel *in = inImage(x,y);
			RGBAPixel *out = outImage(inImage.width()-x-1,inImage.height()-y-1);
			out->red = in->red;
			out->green = in->green;
			out->blue = in->blue;
		}
	}
return outImage;

}

int main()
{
	PNG inImage("in.png");
	PNG outImage = rotate(inImage);
	outImage.writeToFile("out.png");
	return 0;
	
}
