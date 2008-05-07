#include "screenio.h"
#include "imageutils.h"
#include "texcode.h"
#include "getwhim.h"
#include "getorim.h"
#include "curtain.h"
#include "blackglobals.h"
#include "blackmain.h"
#include <stdio.h>
#include <stdlib.h>
extern "C" {
#include "utilfuncs.h"
}

using namespace blackbarrels;
static Buffer2D<PixelRGB> The_Processed_Image;

namespace blackbarrels{
	static Image * infr1=new Image;
	static Buffer2D<PixelRGB> whim,orim,fr1,barim,fr2;
	static Buffer2D<bool> mask;
}

extern "C" void getBlackedImage(Image* infr2,Image* imout){
	fr1.copyFrom (infr2->width,infr2->height, (PixelRGB*) infr2->data);
	blackmain();
	imout->width	=The_Processed_Image.width;
	imout->height	=The_Processed_Image.height;
	imout->data		=(char*)The_Processed_Image.data;//The_Processed_Image.data;
}


//static Buffer2D<PixelRGB> * fr1;
//static Buffer2D<PixelRGB> * barim;

namespace blackbarrels{

void blackmain() {
	
	/* get image */
	long long t1=currentTimeMicros();
	//ImageLoad ("12.bmp", infr1);
	//fr1.copyFrom (infr1->width,infr1->height, (PixelRGB*) infr1->data);
	//free (infr1->data);					//don't leak memory!
	
	
	
	fr2.copyFrom(fr1);
	fr2.shrink(5);
	
	int width=fr2.width;
	int height=fr2.height;
	
	//put black borders on
	for(int i=0;i<height;i++){
		fr2[i*width].r=fr2[i*width].g=fr2[i*width].b=0;
		fr2[(i+1)*width-1].r=fr2[(i+1)*width-1].g=fr2[(i+1)*width-1].b=0;
	}
	memset((void*)&(fr2[0]),0,width*sizeof(PixelRGB));
	memset((void*)&(fr2[(height-1)*width]),0,width*sizeof(PixelRGB));
	
	/* process */
	orim = getorim (fr2);
	whim = getwhim (fr2);
	mask.copyFrom(curtain (whim, orim));
	//Buffer2D<PixelRGB> test2=test.toRGB();
	mask.grow(5);
	blackout(mask,fr1);

    //barim.copyFrom(fr1);
	/* put image into screen */
	//screen = &barim;
	/* put screen into graphics card*/
	
	double diff=currentTimeMicros()-t1;
	printf("framerate: %.2f\n",1.0/diff*1000000.0);
	
	//NextFrame();
	The_Processed_Image.copyFrom(fr1);
}

}