static float t=0;
class Fish
{
	float xpos;
	float ypos;
	float scalefactorx;
	float scalefactory;
	int flag;
	float r,g,b;
	float rem;
	float range;	
	float resetx,resety;
	public:
	Fish()
	{
		xpos = rand() % 620;
		ypos = rand() % 90;
		resetx=1;
		resety=0;
		scalefactorx=4;
		scalefactory=4;
		flag=0;
		r=((double) rand() / (RAND_MAX));
		g=((double) rand() / (RAND_MAX));
		b=((double) rand() / (RAND_MAX));
		srand (time(NULL));	
		range = 360;
	}
	Fish(float x,float y)
	{
		xpos=x;
		ypos=y;
		resetx=x;
		resety=y;	
		scalefactorx=4;
		scalefactory=4;
		flag=0;
		r=((double) rand() / (RAND_MAX));
		g=((double) rand() / (RAND_MAX));
		b=((double) rand() / (RAND_MAX));
		rem=y;
		srand (time(NULL));
		range=360;
	}
	Fish(float x,float y,float red,float green,float blue)
	{
		xpos=x;
		ypos=y;
		resetx=x;
		resety=y;	
		scalefactorx=4;
		scalefactory=4;
		flag=0;
		r=red;
		g=green;
		b=blue;
		rem=y;
		srand (time(NULL));
		range=360;
	}
	void resetfish()
	{
		xpos=resetx;
		ypos=resety;
		r=((double) rand() / (RAND_MAX));
		g=((double) rand() / (RAND_MAX));
		b=((double) rand() / (RAND_MAX));
	}
	float getxpos(){return xpos;}
	float getypos(){return ypos;}
	void change_sf(float fx,float fy)
	{	
		scalefactorx=fx;
		scalefactory=fy;
	}
	void change_color(float red,float green,float blue)
	{
		g=green;
		r=red;
		b=blue;
	}	
	void drawFish()
	{
		//head
		glPushMatrix();
		glTranslatef(xpos,ypos,0);
		glScalef(scalefactorx,scalefactory,0);
		glColor3f(r,g,b);
		glBegin(GL_POLYGON);
			glVertex2d(1,1);
			glVertex2d(2,2);
			glVertex2d(3,1);
			glVertex2d(2,0);
		glEnd();
		
		//eyes
		glColor3f(0.0f,0.0f,0.0f);
		glBegin(GL_POLYGON);
			glVertex2f(2,1);
			glVertex2f(2,1.5);
			glVertex2f(2.5,1.5);
			glVertex2f(2.5,1);
		glEnd();
		
		
		//body
		glColor3f(r,g,b);
		glBegin(GL_POLYGON);
			glVertex2f(1,1);
			glVertex2f(0.7,1.5);
			glVertex2f(0.5,1);
			glVertex2f(0.7,0.5);
		glEnd();
			
		glPopMatrix();	
	}

	void jump(float x, float theta, float r)
	{
		
		float xe = (x>r)? 0:x;
		ypos = (rem+xe*tan(theta)*(1-(xe/r)));
	}
	
	void roam()
	{
		if(xpos>=620)
		{
			flag=1;
			change_sf(-scalefactorx,scalefactory);
		}
		if(xpos<=0)
		{
			flag=0;
			change_sf(-scalefactorx,scalefactory);
			range= rand() % 620 + 1;
		}
		if(flag==0)
		{
			xpos = xpos+0.05;
			jump(xpos,45,range);
		}		
		if(flag==1)
		{
			xpos = xpos-0.05;
		}
	}
};
