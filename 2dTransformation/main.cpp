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

typedef float matrix3x3 [3][3];
typedef float matrix1x3 [1][3];

#define PI 3.14159265

int sizei = 600;
float sizef = 600.0;
float midf = sizef/2;
float midi = sizei/2;

int polygonX[100];
int polygonY[100];
int numPolygon;

int choice;
int refX;
int refY;
float rotAngle;
float scaleX;
float scaleY;
float shearX;
float shearY;
int transY;
int transX;
int choiceRef;
float slope,yIntercept;

Color red = {1.0,0.0,0.0};
Color white = {1.0,1.0,1.0};
Color green = {0.0,1.0,0.0};
Color blue = {0.0,0.0,1.0};

matrix3x3 TR;

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
        for(int i = 1 ; i < numPolygon ; i++)
        {
            glVertex2f(enPixel(polygonX[i-1]) , enPixel(polygonY[i-1]));
            glVertex2f(enPixel(polygonX[i]) , enPixel(polygonY[i]));
        }
        glVertex2f(enPixel(polygonX[numPolygon-1]) , enPixel(polygonY[numPolygon-1]));
        glVertex2f(enPixel(polygonX[0]) , enPixel(polygonY[0]));
    glEnd();
    glFlush();
}

void matrixMultply3x3(matrix3x3 a,matrix3x3 b)
{
    matrix3x3 c;
    int x=3, y=3, i, j, m=3, n=3;

    cout << "\n\nMatrix A :\n\n";
    for (i = 0; i < x; i++)
    {
        for (j = 0; j < y; j++)
        {
            cout << "\t" << a[i][j];
        }
        cout << "\n\n";
    }

    cout << "\n\nMatrix B :\n\n";
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            cout << "\t" << b[i][j];
        }
        cout << "\n\n";
    }

        for (i = 0; i < x; i++)
        {
            for (j = 0; j < n; j++)
            {
                c[i][j] = 0;
                for (int k = 0; k < m; k++)
                {
                    c[i][j] = c[i][j] + a[i][k] * b[k][j];
                }
            }
        }

        cout << "\n-----------------------------------------------------------\n";
        cout << "\n\nMultiplication of Matrix A and Matrix B :\n\n";
        for (i = 0; i < x; i++)
        {
            for (j = 0; j < n; j++)
            {
                cout << "\t" << c[i][j];
            }
            cout << "\n\n";
        }

        for (i = 0; i < x; i++)
        {
           for (j = 0; j < n; j++)
            {
                TR[i][j] = c[i][j];
            }
        }


}

void matrixTransform(matrix1x3 a,matrix3x3 b,int index)
{
    matrix1x3 c;
    int x=1, y=3, i, j, m=3, n=3;

    cout << "\n\nMatrix A :\n\n";
    for (i = 0; i < x; i++)
    {
        for (j = 0; j < y; j++)
        {
            cout << "\t" << a[i][j];
        }
        cout << "\n\n";
    }

    cout << "\n\nMatrix B :\n\n";
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            cout << "\t" << b[i][j];
        }
        cout << "\n\n";
    }

        for (i = 0; i < x; i++)
        {
            for (j = 0; j < n; j++)
            {
                c[i][j] = 0;
                for (int k = 0; k < m; k++)
                {
                    c[i][j] = c[i][j] + a[i][k] * b[k][j];
                }
            }
        }

        cout << "\n-----------------------------------------------------------\n";
        cout << "\n\nMultiplication of Matrix A and Matrix B :\n\n";
        for (i = 0; i < x; i++)
        {
            for (j = 0; j < n; j++)
            {
                cout << "\t" << c[i][j];
            }
            cout << "\n\n";
        }


        polygonX[index] = c[0][0] ;
        polygonY[index] = c[0][1] ;
}

void matrixIdentity()
{
    TR[0][0] = 1;
    TR[1][0] = 0;
    TR[2][0] = 0;

    TR[0][1] = 0;
    TR[1][1] = 1;
    TR[2][1] = 0;


    TR[0][2] = 0;
    TR[1][2] = 0;
    TR[2][2] = 1;
}

void matrixMirror(int mx , int my)
{
    matrix3x3 M;
    matrix1x3 P;
    int i;

    M[0][0] = mx;
    M[1][0] = 0;
    M[2][0] = 0;

    M[0][1] = 0;
    M[1][1] = my;
    M[2][1] = 0;


    M[0][2] = 0;
    M[1][2] = 0;
    M[2][2] = 1;

    matrixMultply3x3(TR,M);
}

void matrixTranslation(int tx , int ty)
{
    matrix3x3 T;
    matrix1x3 P;
    int i;

    T[0][0] = 1;
    T[1][0] = 0;
    T[2][0] = tx;

    T[0][1] = 0;
    T[1][1] = 1;
    T[2][1] = ty;


    T[0][2] = 0;
    T[1][2] = 0;
    T[2][2] = 1;

    matrixMultply3x3(TR,T);
}

void matrixRotation(float theta)
{
    matrix3x3 R;

    theta = theta*PI;
    theta = theta/180;
    int i;

    R[0][0] = cos(theta);
    R[1][0] = -sin(theta);
    R[2][0] = 0;

    R[0][1] = sin(theta);
    R[1][1] = cos(theta);
    R[2][1] = 0;


    R[0][2] = 0;
    R[1][2] = 0;
    R[2][2] = 1;

    matrixMultply3x3(TR,R);
}

void matrixScaling(float sx , float sy)
{
    matrix3x3 S;

    S[0][0] = sx;
    S[1][0] = 0;
    S[2][0] = 0;

    S[0][1] = 0;
    S[1][1] = sy;
    S[2][1] = 0;


    S[0][2] = 0;
    S[1][2] = 0;
    S[2][2] = 1;

    matrixMultply3x3(TR,S);
}

void matrixShearing(float sx , float sy)
{
    matrix3x3 S;

    S[0][0] = 1;
    S[1][0] = sx;
    S[2][0] = 0;

    S[0][1] = sy;
    S[1][1] = 1;
    S[2][1] = 0;


    S[0][2] = 0;
    S[1][2] = 0;
    S[2][2] = 1;

    matrixMultply3x3(TR,S);
}

void matrixFinalTransformation()
{
    matrix1x3 P;
    int i;
    for( i = 0 ; i < numPolygon ; i++)
    {
        P[0][0] = polygonX[i];
        P[0][1] = polygonY[i];
        P[0][2] = 1;
        matrixTransform(P,TR,i);
    }
}
void translation(int tx,int ty)
{
    int i;

      for(i = 0 ; i < numPolygon ; i++)
    {
        polygonX[i] = polygonX[i] + tx;
        polygonY[i] = polygonY[i] + ty;
    }
}

void rotation(float theta)
{
    int i;
    theta = theta*PI;
    theta = theta/180;
    for( i = 0 ; i < numPolygon ; i++)
    {
        polygonX[i] = polygonX[i] * cos(theta) - polygonY[i] * sin(theta);
        polygonY[i] = polygonX[i] * sin(theta) + polygonY[i] * cos(theta);
    }
}

void mirrorX()
{
    int i;
    for( i = 0 ; i < numPolygon ; i++)
    {
        polygonX[i] = polygonX[i] * 1;
        polygonY[i] = polygonY[i] * -1;
    }
}

void mirrorY()
{
    int i;
    for( i = 0 ; i < numPolygon ; i++)
    {
        polygonX[i] = polygonX[i] * -1;
        polygonY[i] = polygonY[i] * 1;
    }
}

void mirrorTemp()
{
    matrix3x3 M;
    matrix1x3 P;
    int i;

    M[0][0] = 1;
    M[1][0] = 0;
    M[2][0] = 0;

    M[0][1] = 0;
    M[1][1] = -1;
    M[2][1] = 0;


    M[0][2] = 0;
    M[1][2] = 0;
    M[2][2] = 1;
    ///

    for( i = 0 ; i < numPolygon ; i++)
    {
        P[0][0] = polygonX[i];
        P[0][1] = polygonY[i];
        P[0][2] = 1;
        matrixTransform(P,M,i);
    }

    ///
    /*int i;
    for( i = 0 ; i < numPolygon ; i++)
    {
        int tempX = polygonX[i];
        int tempY = polygonY[i];
        polygonX[i] = tempY ;
        polygonY[i] = tempX ;
    }
    */
}

void mirrorXY()
{
    int i;
    for( i = 0 ; i < numPolygon ; i++)
    {
        polygonX[i] = polygonX[i] * -1;
        polygonY[i] = polygonY[i] * -1;
    }
}

void scaling(float sx,float sy)
{
    int i;
    for( i = 0 ; i < numPolygon ; i++)
    {
        polygonX[i] = (int)((float)polygonX[i] * sx);
        polygonY[i] = (int)((float)polygonY[i] * sy);
    }
}

void shear(float sx,float sy)
{
    int i;
    for( i = 0 ; i < numPolygon ; i++)
    {
        polygonX[i] = polygonX[i] + (int)((float)polygonY[i] * sx);
        polygonY[i] = polygonY[i] + (int)((float)polygonX[i] * sy);
    }
}
static void display(void)
{
  int x;
  int y = 0;
  drawAxis();
  drawPolygon();
}

static void on(int button ,int state ,int x, int y)
{
    if(state == 1) ///clicked
    {
        if(choice == 1)
        {
            matrixIdentity();
            matrixTranslation(transX,transY);
            matrixFinalTransformation();
            //translation(transX,transY);
        }
        else if(choice == 2)
        {
            if(choiceRef == 1 )
            {
                matrixIdentity();
                matrixRotation(rotAngle);
                matrixFinalTransformation();
                //rotation(rotAngle);
            }

            else if (choiceRef == 3)
            {
                int tmp;
                transX = 0;
                transY = 0;
                for(tmp = 0 ; tmp < numPolygon ; tmp++)
                {
                    transX += polygonX[tmp];
                    transY += polygonY[tmp];
                }
                transX /= numPolygon;
                transY /= numPolygon;

                setPixel(enPixel(transX),enPixel(transY),red);

                //cout << transX <<"\n";
                //cout << transY << "\n";

                matrixIdentity();
                matrixTranslation(-transX,-transY);
                matrixRotation(rotAngle);
                matrixTranslation(transX,transY);
                matrixFinalTransformation();
            }
            else
            {
               // translation(-transX,-transY);
               // rotation(rotAngle);
               // translation(transX,transY);

                setPixel(enPixel(transX),enPixel(transY),red);
                matrixIdentity();
                matrixTranslation(-transX,-transY);
                matrixRotation(rotAngle);
                matrixTranslation(transX,transY);
                matrixFinalTransformation();
            }

        }
        else if(choice == 3)
        {
            if(choiceRef == 1)
            {
                matrixIdentity();
                matrixScaling(scaleX,scaleY);
                matrixFinalTransformation();
            }
            else
            {
                int tmp;
                transX = 0;
                transY = 0;
                for(tmp = 0 ; tmp < numPolygon ; tmp++)
                {
                    transX += polygonX[tmp];
                    transY += polygonY[tmp];
                }
                transX /= numPolygon;
                transY /= numPolygon;

                setPixel(enPixel(transX),enPixel(transY),red);

                matrixIdentity();
                matrixTranslation(-transX,-transY);
                matrixScaling(scaleX,scaleY);
                matrixTranslation(transX,transY);
                matrixFinalTransformation();
            }
          //scaling(scaleX,scaleY);
        }
        else if(choice == 4)
        {
            if(choiceRef == 1)
            {
                matrixIdentity();
                matrixMirror(-1,-1);
                matrixFinalTransformation();
                //mirrorXY();
            }
            else if(choiceRef == 2)
            {
                matrixIdentity();
                matrixMirror(1,-1);
                matrixFinalTransformation();
                //mirrorX();
            }
            else if(choiceRef == 3)
            {
                matrixIdentity();
                matrixMirror(-1,1);
                matrixFinalTransformation();
                //mirrorY();
            }
            else
            {
                rotAngle = atan(slope);
                rotAngle = rotAngle*180;
                rotAngle = rotAngle/PI;

                //cout << rotAngle;

                ///

                matrixIdentity();
                matrixTranslation(0,-yIntercept);
                matrixRotation(-rotAngle);
                matrixMirror(1,-1);
                matrixRotation(rotAngle);
                matrixTranslation(0,yIntercept);
                matrixFinalTransformation();
                ///

                //translation(0,-yIntercept);
                //rotation(-rotAngle);
                //mirrorX();
                //rotation(rotAngle);
                //translation(0,yIntercept);

                int y0 = (int)(midf*slope) + yIntercept;
                int y1 = (int)(-midf*slope) + yIntercept;
                drawLine(midi,y0,-midi,y1,red);

            }

        }
        else if (choice == 5)
        {
            if(choiceRef == 1)
            {
                matrixIdentity();
                matrixShearing(shearX,shearY);
                matrixFinalTransformation();
            }

            else
            {
                int tmp;
                transX = 0;
                transY = 0;
                for(tmp = 0 ; tmp < numPolygon ; tmp++)
                {
                    transX += polygonX[tmp];
                    transY += polygonY[tmp];
                }
                transX /= numPolygon;
                transY /= numPolygon;

                setPixel(enPixel(transX),enPixel(transY),red);

                matrixIdentity();
                matrixTranslation(-transX,-transY);
                matrixShearing(shearX,shearY);
                matrixTranslation(transX,transY);
                matrixFinalTransformation();

            }
            //shear(shearX,shearY);
        }


        //translation(30,30);
        //rotation(10);
        //mirrorXY();
        //scaling(0.5,0.5);
        //shear(1,0);
        //mirrorTemp();

      /*  matrixIdentity();
        matrixScaling(0.5,0.5);
        matrixTranslation(30,30);
        matrixMirror(1,-1);
        matrixRotation(-10);
        matrixShearing(0.5,0);
        matrixFinalTransformation();
        */
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
    cout << "give number of vertices of polygon"<<endl;
    cin >> numPolygon;
    cout <<"enter co-ordinates X & Y\n";

    for(i = 0 ; i < numPolygon ; i++)
    {
        cin >> polygonX[i];
        cin >> polygonY[i];
    }

cout <<"1.translation\n2.rotation\n3.scaling\n4.reflection\n5.shearing\n";

cout << "enter your choice =>  ";

  scanf("%d",&choice);
  switch(choice)
  {
    case 1:
      printf("Enter translation along X & Y\n=>");
      scanf("%d%d",&transX , &transY);
      break;
    case 2:
      printf("Enter your choice number for Rotation about:\n1.Origin\n2.arbitary point \n3.center of the object\n=>");
      scanf("%d",&choiceRef);
      printf("Enter Angle of Rotation\n=>");
      scanf("%f",&rotAngle);
      if(choiceRef == 2)
      {
          cout <<"arbitary point X and Y ==> ";
          cin >> transX >> transY;
      }

      break;
    case 3:
      printf("Enter Scaling ratios along X & Y\n=>");
      scanf("%f%f",&scaleX , &scaleY);
      printf("Enter your choice number for Scaling about:\n1.Origin\n2.center of the object\n=>");
      scanf("%d",&choiceRef);
      break;
    case 4:
      printf("Enter your choice number for Reflection about:\n1.Origin\n 2.X-axis\n 3.Y-axis\n 4.y = mx+c\n=>");
      scanf("%d",&choiceRef);
      if(choiceRef == 4)
      {
        printf("Enter m & c: \n=>");
        scanf("%f %f",&slope,&yIntercept);
      }
      break;
    case 5:
      printf("Enter your shear factor X and Y\n=> ");
      scanf("%f%f",&shearX , &shearY);
      printf("Enter your choice number for Shearing about:\n1.Origin\n2.center of the object\n=>");
      scanf("%d",&choiceRef);
      break;
  }

}

void manualInput()
{
    numPolygon = 4;
    polygonX[0] = 100;
    polygonY[0] = 100;

    polygonX[1] = 200;
    polygonY[1] = 100;

    polygonX[2] = 200;
    polygonY[2] = 200;

    polygonX[3] = 100;
    polygonY[3] = 200;

    choice = 5;
    choiceRef = 2;
    yIntercept = 10.0;
    slope = 0.3;
    //transX = 10;
    //transY = 10;
    rotAngle = 10;
    shearX = 0.0;
    shearY = -1.0;

}

int main(int argc, char *argv[])
{
    int i;

    glutInit(&argc, argv);
    glutInitWindowSize(sizei,sizei);
    glutInitWindowPosition(10,10);
    //glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("2D transformation");

   //userInput();
  manualInput();

    initGL();
    glutDisplayFunc(display);
    glutMouseFunc(on); ///mouse click hole on() call hobe

    glutMainLoop();

    return EXIT_SUCCESS;
}

/*
translation
1 0 0
0 1 0
tx ty 1

rot

cosT sinT 0
-sinT cosT 0
0 0 1

scaling
sx 0 0
0 sy 0
0 0 1

shear
1 shy 0
shx 1 0
0 0 1

mirror
1 0 0
0 -1 0
0 0 1
*/
