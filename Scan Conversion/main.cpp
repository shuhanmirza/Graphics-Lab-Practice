///author: shuhan mirza
//
#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include<bits/stdc++.h>

using namespace std;

struct Point {
	GLint x;
	GLint y;
};

struct Color {
	GLfloat r;
	GLfloat g;
	GLfloat b;
};

#define PI 3.14159265

int sizei = 600;
float sizef = 600.0;
float midf = sizef/2;
float midi = sizei/2;

int choice;
int choiceRef;
int X1,Y1,X2,Y2;
int Xc,Yc,R;

Color red = {1.0,0.0,0.0};
Color white = {1.0,1.0,1.0};
Color green = {0.0,1.0,0.0};
Color blue = {0.0,0.0,1.0};

float enPixel(float x)
{
  float p = (x/midf);
  return p;
}

int dePixel(float x)
{
  float p = (x*midf);

  return (int)p;
}

Color getPixel(GLint x, GLint y) {
	Color color;
	glReadPixels(x+midi,y+midi,1,1, GL_RGB, GL_FLOAT, &color);
	return color;
}

void setPixel(float x,float y, Color color) {
	glColor3f(color.r, color.g, color.b);
	glBegin(GL_POINTS);
        glVertex2f(x, y);
	glEnd();
	glFlush();
}

void drawAxis()
{
    glColor3f(1.0,1.0,0.0);
    glBegin(GL_LINES);
        glVertex2f(enPixel(0),enPixel(-midi));
        glVertex2f(enPixel(0),enPixel(midi));

        glVertex2f(enPixel(-midi),enPixel(0));
        glVertex2f(enPixel(midi),enPixel(0));
   glEnd();
    glFlush();
}

void drawLine(int x0,int y0,int x1 , int y1 , Color color)
{
    glColor3f(color.r,color.g,color.b);
    glBegin(GL_LINES);
        glVertex2f(enPixel(x0),enPixel(y0));
        glVertex2f(enPixel(x1),enPixel(y1));
   glEnd();
   glFlush();
}

void midCircle()
{
    int x = 0, y = R;

    double P0 = (5/4) - R; ///decision variable

    //CirclePlot(x, y);
    setPixel(enPixel(x+Xc),enPixel(y+Yc),red);

    while(x < y)
    {
        if(P0 < 0)
        {
            P0 += (2*x) + 1;
            x++;
            y = y;
        }
        else
        {
            P0 += 2*(x-y) + 1;
            x++;
            y--;
        }
        setPixel(enPixel(x+Xc),enPixel(y+Yc),red);
        setPixel(enPixel(x+Xc),enPixel(-y+Yc),red);
        setPixel(enPixel(-x+Xc),enPixel(y+Yc),red);
        setPixel(enPixel(-x+Xc),enPixel(-y+Yc),red);

        setPixel(enPixel(y+Xc),enPixel(x+Yc),red);
        setPixel(enPixel(y+Xc),enPixel(-x+Yc),red);
        setPixel(enPixel(-y+Xc),enPixel(x+Yc),red);
        setPixel(enPixel(-y+Xc),enPixel(-x+Yc),red);

        //CirclePlot(x, y);
        //CirclePlot(x, -y);
        //CirclePlot(-x, y);
        //CirclePlot(-x, -y);
        //CirclePlot(y, x);
        //CirclePlot(y, -x);
        //CirclePlot(-y, x);
        //CirclePlot(-y, -x);
    }
}

void BresenhamCircle(void)
{
    int x = 0, y = R;

    double d = 3 - 2*R;
    //CirclePlot(x, y);
    setPixel(enPixel(x+Xc),enPixel(y+Yc),red);

    while(x <= y)
    {
        if(d < 0)
        {
            d += 4*x + 6;
            x++;
            y = y;
        }
        else
        {
            d += 4*(x-y) + 10;
            x++;
            y--;
        }

        setPixel(enPixel(x+Xc),enPixel(y+Yc),red);
        setPixel(enPixel(x+Xc),enPixel(-y+Yc),red);
        setPixel(enPixel(-x+Xc),enPixel(y+Yc),red);
        setPixel(enPixel(-x+Xc),enPixel(-y+Yc),red);

        setPixel(enPixel(y+Xc),enPixel(x+Yc),red);
        setPixel(enPixel(y+Xc),enPixel(-x+Yc),red);
        setPixel(enPixel(-y+Xc),enPixel(x+Yc),red);
        setPixel(enPixel(-y+Xc),enPixel(-x+Yc),red);
        //CirclePlot(x, y);
        //CirclePlot(x, -y);
        //CirclePlot(-x, y);
        //CirclePlot(-x, -y);
        //CirclePlot(y, x);
        //CirclePlot(y, -x);
        //CirclePlot(-y, x);
        //CirclePlot(-y, -x);
    }
}

void LineDDA()
{
    double dx = (X2 - X1);
    double dy = (Y2 - Y1);
    double steps;
    float xINC, yINC, x = X1, y= Y1;
    steps = (abs(dx)>abs(dy))?(abs(dx)):(abs(dy)); ///if dx>dy, steps = dx, otherwise steps = dy
    xINC = dx/(float) steps;
    yINC = dy/(float) steps;

   // LinePlot(x,y);
    setPixel(enPixel(x),enPixel(y),red);
    int k;

    for (k=0; k<steps; k++)
    {
        x+= xINC;
        y+= yINC;
        //  printf("%0.6lf %0.6lf", floor(x), floor(y));
        //LinePlot(round_val(x),round_val(y));
        setPixel(enPixel(x),enPixel(y),red);

    }
}

void BresenhamLine()
{
    int x, y, dx, dy;
    int P0;

    if(X2 < X1) swap(X1, X2), swap(Y1, Y2);

    dx = abs(X2 - X1);
    dy = abs(Y2 - Y1);


    if(dy < dx && Y2 > Y1)
    {
        x = X1;
        y = Y1;

        //LinePlot(x, y);
        setPixel(enPixel(x),enPixel(y),red);
        P0 = 2*dy - dx;

        while(x < dx)
        {
            if(P0 < 0)
            {
                x++;
                y = y;
                P0 += 2*dy;
            }
            else
            {
                x++;
                y++;
                P0 += 2*(dy-dx);
            }
            //LinePlot(x, y);
            setPixel(enPixel(x),enPixel(y),red);
            //cout << x << " " << y << endl;
        }
    } else
    {
        printf("nope");
        LineDDA();
    }
}

///
void directUse() {
    int xx0 = X1;
    int xx1 = X2;
    int yy0 = Y1;
    int yy1 = Y2;

    int dx=abs(xx1-xx0), dy=abs(yy1-yy0);
    double x=xx0,y=yy0;
    if(dy <= dx) { // As |m| <= 1 we are going to increase x and get the corresponding y value
        double m = (double)(yy1-yy0)/(double)(xx1-xx0);
        double b = yy0-m*xx0;
        while(x<=xx1){
            y = m*x + b;
            //setPixel((int)x,(int)y);
            setPixel(enPixel(x),enPixel(y),red);
            x++;
        }
    } else { // |m| > 1, so the interval in ys is greater than that of x. so we shall iterate over y to get more points.
        int k = yy0 < yy1 ? 1 : -1;
        double m = (double)(yy1-yy0)/(double)(xx1-xx0), b = (yy0-m*xx0)/m;
        while((y <= yy1 && k == 1) || (y >= yy1 && k == -1)){
            x = y/m - b;
            //setPixel((int)x, (int)y);
            setPixel(enPixel(x),enPixel(y),red);
            y = y+k;
        }
    }
}

 void trigonometric(void)
 {
 double XEnd,I,J,A;
 int i,j;
 double a;
 int h = Xc;
 int k = Yc;
 //glClear (GL_COLOR_BUFFER_BIT);
 //glColor3f (0.0, 0.0, 1.0);
 XEnd=(R/1.414);
 //glBegin(GL_POINTS);
 //glVertex2s(h,k);
 setPixel(enPixel(h),enPixel(k),red);
 for(a=0 ; a<=45 ; a++)
 {
 A=a*11/630;
 I=R*sin(A);
 J=R*cos(A);
 i=(int)(I);
 j=(int)(J);

 setPixel(enPixel(h+i),enPixel(k+j),red);
 setPixel(enPixel(h-i),enPixel(k+j),red);
 setPixel(enPixel(h-i),enPixel(k-j),red);
 setPixel(enPixel(h+i),enPixel(k-j),red);

 setPixel(enPixel(h+j),enPixel(k+i),red);
  setPixel(enPixel(h-j),enPixel(k+i),red);
   setPixel(enPixel(h-j),enPixel(k-i),red);
    setPixel(enPixel(h+j),enPixel(k-i),red);
 //glVertex2s(h+i,k+j);
 //glVertex2s(h+j,k+i);
 //glVertex2s(h-i,k+j);
 //glVertex2s(h-j,k+i);
 //glVertex2s(h-j,k-i);
 //glVertex2s(h-i,k-j);
 //glVertex2s(h+i,k-j);
 //glVertex2s(h+j,k-i);
 }
 /*glColor3f (1.0, 1.0, 1.0);
 for(i=-100 ; i<=100 ; i++)
 {
 glVertex2s(i,0);
 glVertex2s(0,i);
 }*/
 //glEnd();
 //glFlush();
 }
///
static void display(void)
{
  int x;
  int y = 0;
  drawAxis();
}

static void on(int button ,int state ,int x, int y)
{
    if(state == 1) ///clicked
    {
        switch(choice)
        {
            case 1:
                    switch(choiceRef)
                    {
                        case 1:
                            LineDDA();
                            break;

                        case 2:
                            BresenhamLine();
                            break;
                        case 3:
                            directUse();
                            break;
                    }
                    break;

            case 2:
                if(R >= 0)
                {
                    switch(choiceRef)
                    {
                        case 1:
                            midCircle();
                            break;

                        case 2:
                            BresenhamCircle();
                            break;
                        case 3:
                            trigonometric();
                    }
                    break;
                }
                else cout << "Radius can not be negative!!! Sorry for the inconvenience\n";
        }
    }

    //glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    display();
    return;
}

void initGL()
{
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glPointSize(1.0);
}

void userInput()
{
    int i;

    cout << "Welcome To the scan conversion console\n\n";
    cout <<"1.Line \n2.Circle\n\n select your choice by entering number\n";
    cin >> choice;

    switch(choice)
    {
        case 1:
            cout << "1.DDA  \n2.Bresenham\n3.Direct use of equ\n\nselect your choice by entering number\n";
            cin >> choiceRef;
            cout << "enter coordinates : X1 & Y1 & X2 & Y2\n";
            cin >> X1 >> Y1 >> X2 >> Y2;
            break;

        case 2:
            cout <<"1.MidPoint  \n2.Bresenham\n3.trigonometric \n\nselect your choice by entering number\n";
            cin >> choiceRef;
            cout << "enter center coordinates : X & Y\n";
            cin >> Xc >> Yc ;

            cout << "enter radius : R \n";
            cin >> R;
            break;
    }

}

void manualInput()
{

}

int main(int argc, char *argv[])
{
    int i;

    glutInit(&argc, argv);
    glutInitWindowSize(sizei,sizei);
    glutInitWindowPosition(10,10);
    //glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Scan Conversion");

    userInput();
    //manualInput();

    initGL();
    glutDisplayFunc(display);
    glutMouseFunc(on); ///mouse click hole on() call hobe

    glutMainLoop();

    return EXIT_SUCCESS;
}
