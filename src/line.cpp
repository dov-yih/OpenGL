/**
 * --- src/line.cpp
 * first opengl program.
 * how install opengl on arch/manjaro  @ref https://en.wikibooks.org/wiki/OpenGL_Programming/Installation/Linux
 * @author yidafu
 * @time 2018-4/17
 */

#ifdef linux

#include "include/base.h"

#endif

#ifdef WIN32

#include "stdafx.h"
#include <GL/glut.h>

#endif

 //
 // OpenGL.cpp: 定义控制台应用程序的入口点。
 //

#include <iostream>
using namespace std;

#define EDGE 600
#define SPACING 10


int move_count = EDGE / SPACING;
GLfloat line_movement = 2.0 / move_count;
GLfloat point_movement = line_movement;


void drawGrid(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	GLfloat line_pos = -1.0;
	while (line_pos < 1.0) {
		line_pos += line_movement;
		glBegin(GL_LINES);
		glVertex2f(line_pos, -1.0);
		glVertex2f(line_pos, 1.0);
		glEnd();
		glBegin(GL_LINES);
		glVertex2f(-1.0, line_pos);
		glVertex2f(1.0, line_pos);
		glEnd();
		glFlush();
	}
}

void bresenhanLine(int x0, int y0, int x1, int y1, int color) {
	int x = x0, y = y0, dx = x1 - x0, dy = y1 - y0;

	float k = (float)dy / (float)dx,
		//ye = y
		ye = -0.5;
	;

	while (x < x1) {
		glPointSize(10.0);
		glBegin(GL_POINTS);
		glColor3f(1, 0, 0);
		glVertex2f(x * point_movement - 1.0, y * point_movement - 1.0);
		glEnd();
		glFlush();
		// x y 应该同时改变
		x++, ye = ye + k;
		// y = (int)ye;

		/**
		这里假设斜率在 0 ~ 1 之间
		*/
		if (ye > 0) {
			y++;
			ye--;
		}
	}
}
void draw(void) {

	drawGrid();

	bresenhanLine(0, 0, 20, 5, 1);
}


int main(int argc, char** argv)

{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 100);

	glutInitWindowSize(EDGE, EDGE);


	glutCreateWindow("Bresenhan Line");


	glutDisplayFunc(draw);

	glutMainLoop();

	return 0;

}
