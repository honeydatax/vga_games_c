// need file libdos.c to be compile in directory
//bcc -x -i -L -Md hello.c -o HELLO.COM
#define varn 0x0080
#define vga 0x12
#define VIDEO 0xA000
#define stdout 0 
#define lpt 2 
#define com1 3 
#define blue 1
#define brish 8
#define transparent 0xf
#define white 7
#define ship_width 8
#define ship_height 16
#define mask_width 8
#define mask_height 16
#define seconds 18

int VID;
int ii;
void screens(n);
int getptr();
void backs(address,count,color);
void setcolor(color);
void rect(rectx,recty,rectx1,recty1,color);
void putsn(x,y,s,color,size);
int colorsbc(backsc,forec);
void locate(x,y);
void graphics(x,y,w,h,arrays);
void invgraphics(x,y,w,h,arrays);
int gettimer();
void sleep(i);
int getkey();

int main(){
static unsigned char ship_bits[] = {
   0x18, 0x3c, 0x7e, 0xff, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0x18};
static unsigned char mask_bits[] = {
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff};
    char a[20];
	int ii=0;
	int n;
	int nn;
	int xxx=320;
	int yyy=270;
	int xxx1=320;
	int yyy1=271;
	int x=10;
	int y=10;
	int x1=200;
	int y1=150;
	int color=2;
	int unsigned size=(640/8)*480; 
	char c[80];
	screens(vga);
	setcolor(blue);
	backs(VIDEO,(int)size,255);
	sleep(15);
	n=0;
	nn=0;
	while(n!=27){
		if (xxx!=xxx1 || yyy!=yyy1){
			setcolor(15);		
			invgraphics (xxx1,yyy1,mask_width,mask_height,mask_bits);
			setcolor(blue);
			graphics (xxx1,yyy1,mask_width,mask_height,mask_bits);

			setcolor(15);		
			graphics (xxx,yyy,ship_width,ship_height,ship_bits);
			setcolor(blue);		
			graphics (xxx,yyy,mask_width,mask_height,mask_bits);
			xxx1=xxx;
			yyy1=yyy;
		}
		n=getkey();
		nn=n >> 8;
		n=n & 255;
		a[0]=nn;
		if (xxx>16 && nn=='K') xxx=xxx-8;
		if (yyy>16 && nn=='H') yyy=yyy-1;
		if (xxx<620 && nn=='M') xxx=xxx+8;
		if (yyy<450 && nn=='P') yyy=yyy+1;
		if (nn!=0)putsn(1,1,a,15,1);
	}

setcolor(7);
		asm	"db 0xb4,0,0xcd,0x21";
		
	return 0;
}



void screens(n)
int n;
{
	int *c;
	c = (int * ) varn;
	*(c + 0) = n;


	asm	"db 0x1E,0x56,0x8C,0xC8,0x8E,0xD8,0xBE,0x80,0x00,0x2E,0x8A,0x04,0xB4,0x00,0xCD,0x10,0x5E,0x1F";
}



int getptr()
{
	int *c;
	c = (int * ) varn;

	asm	"db 0x8C,0xC8,0x2E,0xA3,0x80,0x0";
	return *(c + 0);
}

void backs(address,count,color)
int address;
int count;
int color;
{
	int *c;
	c = (int * ) varn;
	*(c + 0)=address;
	*(c + 1)=count;
	*(c + 2)=color;
	asm	"db 0x1E,0x06,0x0E,0x1F,0x8B,0x0E,0x82,0x00,0x8B,0x16,0x84,0x00,0xA1,0x80,0x00,0x50,0x07,0x88,0xD0,0x31,0xD2,0x89,0xD7,0x90,0xFC,0xF3,0xAA,0x07,0x1F";
	
}



void setcolor(color)
int color;
{
	int *c;
	c = (int * ) varn;
		*(c + 0)=color;
		asm	"db 0x1E,0x06,0x0E,0x1F,0x2E,0x8A,0x26,0x80,0x00,0xBA,0xC4,0x03,0xB0,0x02,0xEF,0x07,0x1F";
	
}

void rect(rectx,recty,rectx1,recty1,color)
int rectx;
int recty;
int rectx1;
int recty1;
int color;
{
	int r;
	int ir;
	int xx;
	int yy;
	int nx;
	int ny;
	int xx1;
	int yy1;
	int xxx;
	int yyy;
	int xxa;
	int *c;
	int gg=0;
	c = (int * ) varn;
	xx=rectx;
	yy=recty;
	xx1=rectx1;
	yy1=recty1;
	if (xx>639)xx=639;
	if (xx1>639)xx1=639;
	if (yy>479)yy=479;
	if (yy1>479)yy1=479;
	if (xx<0)xx=0;
	if (xx1<0)xx1=0;
	if (yy<0)yy=0;
	if (yy1<0)yy1=0;
	xx=xx/8;
	xx1=xx1/8;
	if (xx<=xx1 && yy<=yy1){
		xxa=xx1-xx;
		if (xxa<1)xxa=1;
		yyy=yy1-yy;
		if (yyy<1)yyy=1;
		xxx=yy*80+xx;
		nx=80-xxa;
		*(c + 0)=VIDEO;
		*(c + 1)=xxx;
		*(c + 2)=xxa;
		*(c + 3)=nx;
		*(c + 4)=yyy;
		*(c + 5)=color;
	}	
	if (xx<=xx1 && yy<=yy1){
		asm	"db 0x1E,0x06,0x0E,0x1F,0x8B,0x3E,0x82,0x00,0x8B,0x36,0x86,0x00,0x8B";
		asm "db 0x16,0x8A,0x00,0x8B,0x1E,0x88,0x00,0x8B,0x0E,0x84,0x00,0xA1,0x80,0x00";
		asm "db 0x50,0x07,0x88,0xD0,0x31,0xD2,0x51,0x90,0x59,0x51,0x90,0xFC,0xF3,0xAA";
		asm "db 0xF8,0x01,0xF7,0x4B,0x39,0xD3,0x75,0xF1,0x58,0x07,0x1F";
	}		
	
}



void putsn(x,y,s,color,size)
int x;
int y;
char *s;
int color;
int size;
{
	int *c;
	c = (int * ) varn;
	*(c + 0) = x;
	*(c + 1) = y;
	*(c + 2) = s;
	*(c + 3) = color;
	*(c + 4) = size;


	asm	"db 0x1E,0x06,0x50,0x53,0x51,0x52,0x56,0x57,0x0E,0x07,0x2E,0x8A,0x16,0x80,0x00,0x2E,0x8A,0x36,0x82,0x00,0x2E,0x8B,0x36,0x84,0x00,0x2E,0x8A,0x1E,0x86,0x00,0x2E,0x8B,0x0E,0x88,0x00,0xB7,0x00,0xB0,0x01,0xB4,0x13,0x55,0x89,0xF5,0xCD,0x10,0x5D,0x90,0x5F,0x5E,0x5A,0x59,0x5B,0x58,0x07,0x1F";
}


int colorsbc(backsc,forec)
int backsc;
int forec;
{
	return (backsc << 4) | forec;
}




void locate(x,y)
int x;
int y;
{
	int *c;
	c = (int * ) varn;
	*(c + 0) = x;
	*(c + 1) = y;


	asm	"db 0x1E,0x06,0x2E,0x8A,0x16,0x80,0x00,0x2E,0x8A,0x36,0x82,0x00,0xB7,0x00,0xB4,0x02,0xCD,0x10,0x90,0x07,0x1F";
}

void graphics(x,y,w,h,arrays)
int x;
int y;
int w;
int h;
char *arrays;
{
	int r;
	int ir;
	int xx;
	int yy;
	int nx;
	int ny;
	int xx1;
	int yy1;
	int xxx;
	int yyy;
	int xxa;
	int *c;
	int gg=0;
	c = (int * ) varn;
	xx=x;
	yy=y;
	xx1=w;
	yy1=h;
	if (xx>639)xx=639;
	if (xx1>639)xx1=639;
	if (yy>479)yy=479;
	if (yy1>479)yy1=479;
	if (xx<0)xx=0;
	if (xx1<0)xx1=0;
	if (yy<0)yy=0;
	if (yy1<0)yy1=0;
	xx=xx/8;
	xx1=xx1/8;
	if (xx1<1)xx1=1;
		xxa=xx1;
		if (xxa<1)xxa=1;
		yyy=yy1;
		if (yyy<1)yyy=1;
		xxx=yy*80+xx;
		nx=80-xxa;
		*(c + 0)=VIDEO;
		*(c + 1)=xxx;
		*(c + 2)=xxa;
		*(c + 3)=nx;
		*(c + 4)=yyy;
		*(c + 5)=arrays;
		
	
		asm	"db 0x1E,0x06,0x50,0x53,0x51,0x52,0x56,0x57,0x0E,0x07,0x2E,0xA1,0x80,0x00,0x8E,0xD8,0x2E,0x8B,0x3E,0x82,0x00,0x2E,0x8A,0x0E,0x84,0x00,0x2E,0x8B,0x16,0x86,0x00,0x2E,0x8A,0x2E,0x88,0x00,0x2E,0x8B,0x36,0x8A,0x00,0x90,0x51,0x90,0x2E,0x8A,0x04,0x3e,0x88,0x05,0x46,0x47,0xFE,0xC9,0x80,0xF9,0x00,0x75,0xF0,0x58,0x88,0xC1,0x01,0xD7,0xFE,0xCD,0x80,0xFD,0x00,0x75,0xE2,0x5F,0x5E,0x5A,0x59,0x5B,0x58,0x07,0x1F";

	
}

void invgraphics(x,y,w,h,arrays)
int x;
int y;
int w;
int h;
char *arrays;
{
	int r;
	int ir;
	int xx;
	int yy;
	int nx;
	int ny;
	int xx1;
	int yy1;
	int xxx;
	int yyy;
	int xxa;
	int *c;
	int gg=0;
	c = (int * ) varn;
	xx=x;
	yy=y;
	xx1=w;
	yy1=h;
	if (xx>639)xx=639;
	if (xx1>639)xx1=639;
	if (yy>479)yy=479;
	if (yy1>479)yy1=479;
	if (xx<0)xx=0;
	if (xx1<0)xx1=0;
	if (yy<0)yy=0;
	if (yy1<0)yy1=0;
	xx=xx/8;
	xx1=xx1/8;
	if (xx1<1)xx1=1;
		xxa=xx1;
		if (xxa<1)xxa=1;
		yyy=yy1;
		if (yyy<1)yyy=1;
		xxx=yy*80+xx;
		nx=80-xxa;
		*(c + 0)=VIDEO;
		*(c + 1)=xxx;
		*(c + 2)=xxa;
		*(c + 3)=nx;
		*(c + 4)=yyy;
		*(c + 5)=arrays;
		
	
		asm	"db 0x1E,0x06,0x50,0x53,0x51,0x52,0x56,0x57,0x0E,0x07,0x2E,0xA1,0x80,0x00,0x8E,0xD8,0x2E,0x8B,0x3E,0x82,0x00,0x2E,0x8A,0x0E,0x84,0x00,0x2E,0x8B,0x16,0x86,0x00,0x2E,0x8A,0x2E,0x88,0x00,0x2E,0x8B,0x36,0x8A,0x00,0x90,0x51,0x90,0x2E,0x8A,0x04,0xF6,0xD0,0x3E,0x88,0x05,0x46,0x47,0xFE,0xC9,0x80,0xF9,0x00,0x75,0xEE,0x58,0x88,0xC1,0x01,0xD7,0xFE,0xCD,0x80,0xFD,0x00,0x75,0xE0,0x5F,0x5E,0x5A,0x59,0x5B,0x58,0x07,0x1F";
		
		
		
		

	
}

int gettimer()
{
	int *c;
	c = (int * ) varn;

		asm	"db 0x1E,0x06,0x50,0x53,0x51,0x52,0x56,0x57,0xB4,0x00,0xCD,0x1A,0x2E,0x89,0x16,0x80,0x00,0x5F,0x5E,0x5A,0x59,0x5B,0x58,0x07,0x1F";
	return *(c + 0) & 0x7fff;	
}

void sleep(i)
int i;
{
	int t1;
	int t2;
	t1=gettimer();
	t1=t1+i;
	t2=gettimer();
	while(t1<t2){
		t2=gettimer();
	}
	while(t1>t2){
		t2=gettimer();
	}
}

int getkey()
{
	int *c;
	c = (int * ) varn;

		asm	"db 0x1E,0x06,0x50,0x53,0x51,0x52,0x56,0x57,0xB4,0x01,0xCD,0x16,0x75,0x09,0xB8,0x00,0x00,0x2E,0xA3,0x80,0x00,0xEB,0x09,0x90,0xB4,0x00,0xCD,0x16,0x2E,0xA3,0x80,0x00,0x90,0x5F,0x5E,0x5A,0x59,0x5B,0x58,0x07,0x1F";
	return *(c + 0);	
}

