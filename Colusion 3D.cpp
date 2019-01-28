#include <iostream>
#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//////////////////////////////////////////////////// Declation ///////////////////////////////////////////////////////////////

// Camera
float camX =0 , camY =3 , camZ=25 ;


// focal position
float Fx = 0 ,Fy = 0 ,Fz = 0 ;

// colusion

float dx;
float dy;
float dz;
int zawiya=0;
//
boolean flashActivated=false,ballTouched=false, show= false , open=false;

float x2=1.0;
float y2=2.0;
float z3=0;

  int i,j;
  float k = 2.0 ;

//  float i=0;
float x,y , z=4;
int radius=2;

float air=0;
///////////////////////////////////////////////////////////////////////////////////



void delay(float secs)
{
	float end = clock()/CLOCKS_PER_SEC + secs;
	while((clock()/CLOCKS_PER_SEC) < end);
}

static void Reshape(int width,int height){
    glViewport(0,0,720,720);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
     gluPerspective(85,1,0.2,50);
     //gluLookAt(-20,2,15,0,0,0,0,1,0);
    gluLookAt(camX,camY,camZ,Fx,Fy,Fz,0,1,0);

}

void terre()
{
     glColor3f(0.0f,0.5f,0.1f);

glBegin(GL_QUADS);
glVertex3i(-10,-10,-60);
glVertex3i(10,-10,-60);
glVertex3i(10,-10,60);
glVertex3i(-10,-10,60);

    glEnd();


}

void flash(int camX,int camY,int camZ)
{

    glColor4f(0.5f,0.6f,0.6f,1);
   glPushMatrix();
glTranslatef(camX-0.1,camY-1,camZ-4);
glRotatef(180,0,1,0);
glutSolidCone(0.15,4,20,20);

glPopMatrix();
}

void light(void)
{
GLfloat light_couleur1[]={3.0,4.0,0.0,1.0};
GLfloat light_couleur2[]={255.0,255.0,255.0,1.0};
GLfloat light_position[]={-7.0,-3.0,-6.0,0.0};

GLfloat shine[]={120.0};

glLightfv(GL_LIGHT2,GL_POSITION,light_position);
glLightfv(GL_LIGHT1,GL_AMBIENT,light_couleur1);
glLightfv(GL_LIGHT2,GL_ACCUM,light_couleur2);
glLightfv(GL_LIGHT2,GL_SPECULAR,light_couleur2);
glMaterialfv(GL_FRONT,GL_SPECULAR,light_couleur1);
  glMaterialfv(GL_FRONT,GL_SHININESS,shine);

glEnable(GL_LIGHT2);


}
int s =0;
void KeyDirect( int touche, int x, int y)
{
switch(touche)
    {
case GLUT_KEY_LEFT:
 glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
     gluPerspective(85,1,0.2,50);
     camX--;
      gluLookAt(camX,camY,camZ,Fx,Fy,Fz,0,1,0);
    break;

case GLUT_KEY_RIGHT:
glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
     gluPerspective(85,1,0.2,50);
     camX++;
      gluLookAt(camX,camY,camZ,Fx,Fy,Fz,0,1,0);

   break;
case GLUT_KEY_UP:
    open=true;
zawiya=45;
   break;
case GLUT_KEY_DOWN:

flashActivated=true;

   break;
case GLUT_KEY_PAGE_UP:


 break;
case GLUT_KEY_PAGE_DOWN:

   break;

default:
        glClearColor(0.0f,0.0f,0.0f,0.05f);
        glClear(GL_COLOR_BUFFER_BIT);



    }
     glutPostRedisplay();
}

////////////////////////:




void collision(float camx,float camy,float camz,float x2,float y2,float z3)
{
dx = abs(camx - x2) ;
dy = abs(camy - y2)  ;
dz = camz-z3-15 ;
//printf("  flash  is %f\n",z3);
//printf("  boll  is %f\n",camz);

GLdouble distance = sqrt(dx*dx + dy*dy+ dz*dz);
//printf("before distance \n");
//printf("  distance  is %f\n",distance);
  if(dz<0 && dz > -20  &&  x2<camx+air && x2>-(camx+air)){
        ballTouched=true;
        //show= true; printf("enter distance \n");
  }

}
float aa =0.0f , bb =0.0f , cc =0.6f ;
void display(){

   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);


 glMatrixMode(GL_MODELVIEW);

 glLoadIdentity();

 glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);

  glRotatef(90,0.0,1.0,0.0);

 //light();
  glColor4f(0.5f,3.0f,4.0f,1);
   glClearColor(aa,bb,cc,0.05f);
  if(show==false)
  {
      glPushMatrix();
  glTranslatef(x2,y2,z3*10);
  glutSolidSphere(air,25,25);
  glPopMatrix();

  }else
  {
      glPushMatrix();
    //  glColor3f(255.0f,0.0f,0.0f);

  glTranslatef(x2,y2,z3*10);
  glutSolidSphere(air,25,25);
  glPopMatrix();

  }
       glPushMatrix();
       glRotatef(90,1,0,0);
        glColor3f(255*0.5f,0.5f,0.5f);
        glTranslatef(x2,y2-2,z3*10+7);

           glPushMatrix();
glTranslatef(x2-1,y2-2,z3*10-8+3);
glRotatef(180,0,1,0);
glutSolidSphere(radius,10,20);



glPopMatrix();
/*
glPushMatrix();
glTranslatef(x2,y2-2,z3*10-8+3.5);
 glColor3f(1.0f,0.0f,1.0f);
glutSolidTorus(1,2,20,20);
glPopMatrix();
*/
glColor3f(255.0f,1.0f,1.0f);
               glBegin(GL_QUAD_STRIP);



    for(int i=0 ; i<240 ; i++)
    {
        x=cos(i)*radius;
        y=sin(i)*radius;

        glVertex3f(x,y,z3+3);

        glVertex3f(x,y,z3-8+3);
    }
glEnd();
        glPopMatrix();



glPushMatrix();
glTranslatef(x2,y2-2+5,z3*10);
glRotatef(90,1,0,0);





/*
glPushMatrix();
glTranslatef(x2,y2-2,z3*10-8+3.5);
 glColor3f(1.0f,0.0f,1.0f);
glutSolidTorus(1,2,20,20);
glPopMatrix();
*/
glColor3f(255.0f,1.0f,1.0f);
               glBegin(GL_QUAD_STRIP);



    for(int i=0 ; i<240 ; i++)
    {
        x=cos(i)*(radius-1.8);
        y=sin(i)*(radius-1.8);

        glVertex3f(x,y,z3+3);

        glVertex3f(x,y,z3+5);
    }
glEnd();
        glPopMatrix();


        glPushMatrix();
        glColor3f(0.0f,0.0f,255.0f);
        glTranslatef(x2-2,y2-2-2.3,z3*10);
        glRotatef(zawiya,1,0,0);
        glScalef(0.1,0.5,2.2);
        glutSolidCube(0.5);



        glPopMatrix();

          glPushMatrix();
        glColor3f(0.0f,0.0f,255.0f);
        glTranslatef(x2-2,y2-2-2.3,z3*10);
         glRotatef(90+zawiya,1,0,0);
        glScalef(0.1,0.5,2.2);

        glutSolidCube(0.5);



        glPopMatrix();

          glPushMatrix();
        glColor3f(0.0f,0.0f,255.0f);
        glTranslatef(x2-2,y2-2-2.3,z3*10);
         //glRotatef(90,1,0,0);
        //glScalef(0.1,0.5,2);

        glutSolidSphere(0.28,20,20);



        glPopMatrix();





flash(camX,camY,camZ);

  ////// ball player


collision(camX,camY,camZ,x2,y2,z3);

 terre();
   glutSwapBuffers();
   // glutPostRedisplay();
}
boolean ww=false ;
void always()
{

  if(flashActivated)
  {
     camZ-=0.2;
  }
  /*if(ww)
  {
      if(aa!=0.5f)
        aa+=0.01f;
       if(bb!=3.0f)
        bb+=0.01f;
         if(cc!=4.0f)
        cc-=0.01f;
  } */
if(open)
  if(ballTouched)
  {
     if(air>0)
      air-=0.5;

     ww=true;
aa=0.5f ;
      bb=3.0f ;
      cc=4.0f ;


  }
  else
  {
      if(air<3)
      air+=0.001;

      if(air>2.998)
       {
         zawiya=0;
        // open=false;
       }

  }
glutPostRedisplay();
}

int main()
{
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(720,720);
    glutInitWindowPosition(100,100);
    glutCreateWindow("OPen GL TP");
    glutReshapeFunc(Reshape);
    glutDisplayFunc(display);
  glutIdleFunc(always);
glutSpecialFunc(KeyDirect);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();

}

