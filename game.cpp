#include<GL/glut.h>
#include<iostream>
#include<cmath>
#include <stdlib.h>
#include <string>   
#include <time.h>
#include <stdio.h>      
#include"fish.h"
#include<list>
#include"bird.h"
using namespace std;

int flag=0;
Bird b(0.5,380);
int number=b.getpoints();
char s[]=": Score ";
char score[15];
int maxi=0;
//output score
// default font
void *font = GLUT_BITMAP_TIMES_ROMAN_24;
void renderBitmapString(
		float x,
		float y,
		float z,
		void *font,
		char *str) {
  char *c;
  glRasterPos3f(x, y,z);
  for (c=str; *c != '\0'; c++) {
    glutBitmapCharacter(font, *c);
  }
}


void drawcloud()
{
	glScalef(20,20,0);
	glColor3f(1.0f,1.0f,1.0f);
	glBegin(GL_POLYGON);
		glVertex2f(0,2);
		glVertex2f(1,3);
		glVertex2f(2,2);
		glVertex2f(1,1);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex2f(1,2);
		glVertex2f(2,3);
		glVertex2f(3,2);
		glVertex2f(2,1);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex2f(2,2);
		glVertex2f(3,3);
		glVertex2f(4,2);
		glVertex2f(3,1);
	glEnd();
	glColor3f(0.0f,0.0f,0.0f);
	glBegin(GL_LINE_LOOP);
		glVertex2f(0,2);
		glVertex2f(1,3);
		glVertex2f(1.5,2.5);
		glVertex2f(2,3);
		glVertex2f(2.5,2.5);
		glVertex2f(3,3);
		glVertex2f(4,2);
		glVertex2f(3,1);
		glVertex2f(2.5,1.5);
		glVertex2f(2,1);
		glVertex2f(1.5,1.5);
		glVertex2f(1,1);
	glEnd();
}
void loadEnvironment()
{
	//drawing pond
	glColor3f(0.6f, 0.8f, 1.0f);
	glBegin(GL_LINES);
		glVertex2d(0,100);
		glVertex2d(640,100);
	glEnd();

	glColor3f(0.0f, 0.0f, 0.6f);
	glBegin(GL_POLYGON);
		glVertex2d(0,0);
		glVertex2d(0,100);
		glVertex2d(640,100);
		glVertex2d(640,0);
	glEnd();
	
	// drawing cloud
	for(int i=10;i<=640;i+=200)
	{
		glPushMatrix();
		glTranslatef(i,420,0);
		drawcloud();
		glPopMatrix();
	}	
	
}


Fish f1(1,42,0,1,1);
Fish f2(300,52,1,0,1);
Fish f3(620,38,0.1,1,0.1);
Fish f4(147,22,0.3,0.5,0.3);
Fish f5(500,47,1,0,0.5);
Fish f6(550,39,1,1,0);
Fish f7;
Fish f8;
Fish f9;
Fish f10;
Fish *f[] = {&f1,&f2,&f3,&f4,&f5,&f6,&f7,&f8,&f9,&f10};
list<Fish *> fishes (f, f + sizeof(f) / sizeof(Fish) );

void renderScene(void)
{
	if(b.getpoints()>=0)
	{
		glClearColor(0,0.7,0.7,1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
		loadEnvironment();

		// render bird
	
		b.drawBird();
		b.roam();

	
		//fishes
		f1.drawFish();
		f1.roam();

		f2.roam();
		f2.drawFish();
	
		f3.drawFish();
		f3.roam();

		f4.drawFish();
		f4.roam();

		f5.drawFish();
		f5.roam();

		f6.drawFish();
		f6.roam();
		
		f7.drawFish();
		f7.roam();
		
		f8.drawFish();
		f8.roam();
			
		f9.drawFish();
		f9.roam();

		f10.drawFish();
		f10.roam();

		/*
		 *	Display Score
		 */
		glColor3f(1,1,0.5);
		number=b.getpoints();
		if(number>maxi){maxi=number;}
		sprintf(score,"%s%d :",s,number);
		renderBitmapString(500.0f, 400.5f, 0.0f, (void *)font ,score);
	}
	else
	{
		glClearColor(0,0,0,1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glColor3f(1,1,1);
		sprintf(score,"MAX Score : %d ",maxi);
		renderBitmapString(250.0f, 400.5f, 0.0f, (void *)font ,score);
		renderBitmapString(250.0f, 240.0f, 0.0f, (void *)font ,"GAME OVER");
		renderBitmapString(230.0f, 100.0f, 0.0f, (void *)font ,"\t\t\t\t\tDeveloped By");
		renderBitmapString(180.0f, 70.0f, 0.0f, (void *)font ,"\t\tKiran Kilingar Nadumane");
		glutIdleFunc(NULL);
	}
	glutSwapBuffers();
}
void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;
	float ratio = 1.0* w / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

        // Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45,ratio,1,1000);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}
void processNormalKeys(unsigned char key,int x,int y)
{
	if(key == 27)
		exit(0);
}

void processMouse(int button, int state, int x, int y) 
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && (480-y)>120 && (480-y)<380) 
	{
		b.fillFishBucket(fishes);
		b.roam(x,480-y);
	}
	glutPostRedisplay();
}

int main(int argc,char **argv)
{
	//initialize glut
	glutInit(&argc,argv);
	glutInitWindowSize(640,480);
	//glutInitWindowPosition(0,0);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-640)/2,(glutGet(GLUT_SCREEN_HEIGHT)-480)/2);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutReshapeFunc(changeSize);
	glutCreateWindow("Catch the Fish");
	gluOrtho2D(0,640,0,480);	

		
	//write callback functions
	glutDisplayFunc(renderScene);
	glutKeyboardFunc(processNormalKeys);
	glutIdleFunc(renderScene);
	glutMouseFunc(processMouse);
	
	//keep it in loop
	glutMainLoop();
}
