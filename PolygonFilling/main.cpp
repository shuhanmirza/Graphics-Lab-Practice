
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


int sizei = 200;
float sizef = 200.0;
float midf = sizef/2;
float midi = sizei/2;

int polygonX[100];
int polygonY[100];
int numPolygon;

Color red = {1.0,0.0,0.0};
Color white = {1.0,1.0,1.0};

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

void drawPolygon()
{
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_LINES);
        for(int i = 0 ; i < numPolygon ; i++)
        {
            glVertex2f(enPixel(polygonX[i]) , enPixel(polygonY[i]));
            glVertex2f(enPixel(polygonX[i+1]) , enPixel(polygonY[i+1]));
        }
    glEnd();
    glFlush();
}

static void display(void)
{
  int x;
  int y = 0;
  //drawAxis();
  drawPolygon();
}

void scanLine()
{
  int x;
  int y = 0;
  bool flg = false;


    for( y = -midi ; y <= midi ; y++)
  {
      int Sx[2];
      int Sy[2];
      int i = 0;
      flg = false;
      for(x = -midi ; x <= midi ; x++)
      {
          Color c = getPixel(x,y);
          //cout << c.r <<" " << c.g <<" " << c.b <<" " <<endl;

          if( c.r == 1.0 && c.g == 1.0 && c.b == 1.0)
          {
             if(flg == false) flg = true;
             else flg = false;

             x+=10;
          }

          if(flg == true)
          {
              drawLine(x-10,y,x,y,red);
          }
      }
      glFlush();
  }
}

void floodfill(int x , int y , Color fillColor , Color old)
{
    Color c = getPixel(x,y);

    if(c.r == old.r && c.g == old.g && c.b == old.b)
    {
        setPixel(enPixel(x),enPixel(y),fillColor);
        floodfill(x+1,y,red,old);
        floodfill(x-1,y,red,old);
        floodfill(x,y-1,red,old);
        floodfill(x,y+1,red,old);

    }
    //cout << c.r << " " << c.g << " " << c.b << endl;
}

static void on(int button ,int state ,int x, int y)
{
    //scanLine();
    int seedX = 50;
    int seedY = 50;
    Color c = getPixel(seedX,seedY);
    floodfill(seedX,seedY,red,c);

    drawAxis();
    return;
}

void initGL()
{
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glPointSize(1.0);
}

int main(int argc, char *argv[])
{
    int i;

    glutInit(&argc, argv);
    glutInitWindowSize(sizei,sizei);
    glutInitWindowPosition(10,10);
    //glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT Shapes");

    /*cout << "give number of vertices of polygon"<<endl;
    cin >> numPolygon;

    for(i = 0 ; i < numPolygon ; i++)
    {
        cin >> polygonX[i];
        cin >> polygonY[i];
    }

    polygonX[i] = polygonX[0];
    polygonY[i] = polygonY[0];
*/

numPolygon = 4;
polygonX[0] = -75;
polygonY[0] = 10;

polygonX[1] = 85;
polygonY[1] = 85;

polygonX[2] = -10;
polygonY[2] = -75;

polygonX[3] = 25;
polygonY[3] = 25;

polygonX[4] = -75;
polygonY[4] = 10;

    initGL();
    glutDisplayFunc(display);
    glutMouseFunc(on);

    glutMainLoop();

    return EXIT_SUCCESS;
}
