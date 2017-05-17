EXENAME = testimage testscene
OBJS = testimage.o  image.o png.o rgbapixel.o
OBJSS = testscene.o scene.o image.o png.o rgbapixel.o 

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -Werror -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi

all : $(EXENAME)

testscene : $(OBJSS)
	$(LD) $(OBJSS) $(LDFLAGS) -o testscene

testscene.o : testscene.cpp scene.h image.h png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) testscene.cpp

scene.o : scene.cpp image.h png.h rgbapixel.h 
	$(CXX) $(CXXFLAGS) scene.cpp

testimage: $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o testimage

testimage.o : testimage.cpp  image.h png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) testimage.cpp

image.o : image.cpp image.h png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) image.cpp

png.o : png.cpp png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) png.cpp

rgbapixel.o : rgbapixel.cpp rgbapixel.h
	$(CXX) $(CXXFLAGS) rgbapixel.cpp



clean :
	-rm -f *.o $(EXENAME) 
