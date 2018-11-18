
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


int sizei = 500;
float sizef = 500.0;
float midf = sizef/2;
float midi = sizei/2;

int radious,CenterX,CenterY;

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

void bresenhamCircle()
{
  int r = radious;
  int d = 3 - (2 * r);

  int x = 0;
  int y = r;

  while ( x <= y)
  {
      setPixel(enPixel(x+CenterX),enPixel(y+CenterY),green);
      setPixel(enPixel(-x+CenterX),enPixel(y+CenterY),green);
      setPixel(enPixel(-x+CenterX),enPixel(-y+CenterY),green);
      setPixel(enPixel(x+CenterX),enPixel(-y+CenterY),green);
      setPixel(enPixel(y+CenterX),enPixel(x+CenterY),green);
      setPixel(enPixel(-y+CenterX),enPixel(x+CenterY),green);
      setPixel(enPixel(-y+CenterX),enPixel(-x+CenterY),green);
      setPixel(enPixel(y+CenterX),enPixel(-x+CenterY),green);

      if(d < 0)
      {
          d = d + 4*x + 6;
      }

      else
        {
           d = d + 4*(x-y) + 10;
           y--;
        }

        x++;
  }
}

static void display(void)
{
  int x;
  int y = 0;
  drawAxis();
  bresenhamCircle();
  //drawPolygon();
}

static void on(int button ,int state ,int x, int y)
{
   return;
}

void initGL()
{
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glPointSize(1.0);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(sizei,sizei);
    glutInitWindowPosition(10,10);
    //glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT Shapes");

    //freopen("in.txt","r",stdin);

    //cout << "give radious"<<endl;
    scanf("%d %d %d",&radious , &CenterX , &CenterY);
    //cout << "center"<<endl;
    //cin >> CenterX;
    //cin >> CenterY;




    initGL();
    glutDisplayFunc(display);
    glutMouseFunc(on);

    glutMainLoop();

    return EXIT_SUCCESS;
}
