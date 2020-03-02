static float remx,remy;
class Bird
{
	float xpos;
	float ypos;
	float scalefactorx;
	float scalefactory;
	int flag;
	int reached;
	float theta;
	int g;
	int points;
	std::list <Fish *> fishes;
	public:
	Bird()
	{
		xpos = 0;
		ypos = 0;
		scalefactorx=8;
		scalefactory=8;
		flag=0;
		reached =0;
		g=0;
		points=0;
	}
	Bird(float x,float y)
	{
		xpos=x;
		ypos=y;	
		scalefactorx=8;
		scalefactory=8;
		flag=0;		
		reached=0;
		g=0;
		points=0;
	}
	void change_sf(float fx,float fy)
	{	
		scalefactorx=fx;
		scalefactory=fy;
	}
	void reverse_sf()
	{	
		scalefactorx=-scalefactorx;
	}
	void cal_theta(float t)
	{
		theta = t;
	}
	void fillFishBucket(std::list <Fish *> f)
	{
		fishes = f;
	}
	void drawBird()
	{
		//head
		glPushMatrix();
		glTranslatef(xpos,ypos,0);
		glScalef(scalefactorx,scalefactory,0);
		glRotatef(theta,0,0,1);
		glColor3f(1,1,0.5);
		glBegin(GL_POLYGON);
			glVertex2d(1,3);
			glVertex2d(2,4);
			glVertex2d(3,4);
			glVertex2d(4,3);
			glVertex2d(3,2);
			glVertex2d(2,2);
		glEnd();
		
		//eyes
		glColor3f(0.0f,0.0f,0.0f);
		glBegin(GL_POLYGON);
			glVertex2f(2.2,2.8);
			glVertex2f(2.2,3.2);
			glVertex2f(2.6,3.2);
			glVertex2f(2.6,2.8);
		glEnd();
		
		//beak
		glColor3f(1,0.4,0);
		glBegin(GL_TRIANGLES);
			glVertex2d(4,3);
			glVertex2d(5,2);
			glVertex2d(3,2);
		glEnd();
		
		//body
		glColor3f(1,1,0.5);
		glBegin(GL_TRIANGLES);
			glVertex2d(0,2);
			glVertex2d(3,2);
			glVertex2d(1,0);
		glEnd();
			
		//feather
		glColor3f(0.9f,0.9f,0.0f);
		glBegin(GL_POLYGON);
			glVertex2f(0.8,1);
			glVertex2f(0.8,1.5);
			glVertex2f(1.2,1.5);
			glVertex2f(1.2,1);
		glEnd();		

		//leg
		glColor3f(1,0,0);
		glBegin(GL_LINES);
			glVertex2d(1,0);
			glVertex2d(2,0);
		glEnd();
		glPopMatrix();	
	}
	void roam(float xin=0,float yin=0)
	{
		if(xin!=0 && yin!=0) {g=1;remx=xin;remy=yin;}
		if(g==1){xin=remx;yin=remy;}
		if(g==0)				// normal path
		{		
			cal_theta(-20);
			if(xpos>=620)
			{
				flag=1;
				change_sf(-8,8);
			}
			if(xpos<=0)
			{
				flag=0;
				change_sf(8,8);
			}
			if(flag==0)
			{
				xpos = xpos+0.06;
				ypos = ypos-sin(xpos*10);
			}		
			if(flag==1)
			{
				xpos = xpos-0.06;
				ypos = ypos+sin(xpos*10);
			}
		}
		else				//glide path
		{
			glide(xin,yin);
			cal_theta(-85);
			if(scalefactorx<0 && xpos<xin || scalefactorx>0 && xpos>xin)reverse_sf();
		}
	}
	void glide(float xin,float yin)
	{
		float X1,Y1,X2,Y2,xInc=0,yInc=0;
		double dx,dy,steps;
		if(reached==0)
		{
			X1=xpos;Y1=ypos;X2=xin;Y2=yin;
			dx=(X2-X1);
			dy=(Y2-Y1);

			steps=(abs(dx)>abs(dy))?abs(dx):abs(dy);/* Find out whether to increment x or y*/
			xInc=dx/(float)steps;
			yInc=dy/(float)steps;

			xpos+=(xInc);
			ypos+=(yInc);
			if(xpos==xin && ypos==yin)
			{
				reached=1;
				catch_fish();
			}
		}
		if(reached==1)
		{
			X1=xpos;Y1=ypos;
			if(xpos<320){X2=0;Y2=380;}
			if(xpos>=320){X2=640;Y2=380;}
			dx=(X2-X1);
			dy=(Y2-Y1);

			steps=(abs(dx)>abs(dy))?abs(dx):abs(dy);/* Find out whether to increment x or y*/
			xInc=dx/(float)steps;
			yInc=dy/(float)steps;
			
			xpos+=xInc;
			ypos+=yInc;
			if((xpos==0 && ypos==380) || (xpos==640 && ypos==380)){reached=0;g=0;};
		}
	}	
	int getpoints()
	{
		return points;
	}
	void catch_fish()
	{	
		float x,y;
		for (std::list<Fish *>::iterator it = fishes.begin(); it != fishes.end(); it++)
    	{
			Fish *f = *it;
			x = f->getxpos();
			y = f->getypos();
			//std::cout<<x<<","<<y<<std::endl;
			if(abs(x-xpos)<50 && abs(y-ypos)<50)
			{
				points++;
				f->resetfish();
			}
			else
			{
				points=points-2;
			}
		}
				
	}
};
