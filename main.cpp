#include <GL/glew.h>
#include <GL/glut.h>
#include<iostream>
#include<vector>

using namespace std;

#include"shader.hpp"

// virablse global
int w=790,h=790;

float points[] = 
{
	-0.95-0.08,0.0,0.0,		// Top-left
	 -0.88-0.08,0.0,0.0,	// Top-right 
	 -0.88-0.08,-0.98,0.0,	// Bottom-right
	 -0.95-0.08,-0.98,0.0	// Bottom-left
};

vector<float> obj;

//


void move()
{
	points[0] +=0.08;
	points[3] +=0.08;
	points[6] +=0.08;
	points[9] +=0.08;
}

void set(float y)
{
	points[1]=points[4]=y;
}

void read(vector<float> &r)
{
	int i=1; char Agin='Y';  float y;

	 while((Agin == 'Y')||(Agin == 'y' ))
	 {
	 cout<<"Enter value "<<i++<<" : ";
	 cin>>y;
	 y=((float)y/(h/10.0))-1.0;
	 r.push_back(y);
	 cout<<"Do you want to continue entering points ( Y/N ) ? ";
	 cin>>Agin;
	 }
}

void changeViewPort(int w1, int h1)
{
	w=w1; h=h1;
	glViewport(0, 0, w, h);
}

void render()
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSwapBuffers();
}

void display()
{
	glDrawArrays(GL_POLYGON, 0, 4);
	glFlush();
}

void init()
{
	GLuint programID = LoadShaders("vs.hpp" , "fs.hpp");
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
	glUseProgram(programID);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);
}

void barChart(void)
{
	for(int i=0;i<obj.size();i++)
	{ 
		move();
		set(obj[i]);
		init();
		display();
	}
	glFlush();
}

void main(int argc, char** argv)
{
	read(obj);

	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); // Set display mode.
	glutInitWindowPosition (0, 0); // Set display-window position.
	glutInitWindowSize (w,h); // Set display-window width and height.
	glutCreateWindow ("chart 2d"); // Create display window.
	glClearColor (1.0, 1.0, 1.0, 0.0); // Set display-window color to white.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glutReshapeFunc(changeViewPort);
	glutDisplayFunc(render);

	GLenum err = glewInit();
	if (GLEW_OK != err) { fprintf(stderr, "GLEW error"); return; }
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

	barChart();
	//glutDisplayFunc(barChart);
	glutMainLoop ( ); // Display everything and wait.



}