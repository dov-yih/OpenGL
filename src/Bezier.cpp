#include <windows.h>
#include <math.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include <stdio.h>
#include <stdlib.h>

class Point {
public:
	double a, b;
	Point():a(0.0),b(0.0){}
	Point(double x,double y):a(x), b(y){};
	void setXY(int x, int y) {
		this->a = x;
		this->b = y;
	}
};

double green[3] = { 0.0, 1.0, 0.0 };
double red[3] = { 1.0, 0.0, 0.0 };
double blue[3] = { 0.0, 0.0, 1.0 };
double lightBlue[3] = { 0.0,1.0,1.0 };
double yellow[3] = { 1.0, 1.0, 0.0 };

Point A = Point(-0.9, -0.5);
Point B = Point(-0.3, 0.5);
Point C = Point(0.3, 0.5);
Point D = Point(0.9, -0.5);

Point getNextPoint(Point A, Point B, Point C, Point D, double t)
{
	Point P = Point(0,0);
	
	double a1 = pow((1 - t), 3);
	double a2 = pow((1 - t), 2)*3*t;
	double a3 = 3*t*t*(1 - t);
	double a4 = t*t*t;

	P.a = a1 * A.a + a2 * B.a + a3 * C.a + a4 * D.a;
	P.b = a1 * A.b + a2 * B.b + a3 * C.b + a4 * D.b;
	
	return P;
}

void drawFunc(Point prev, Point next, double color[]) {
	glBegin(GL_LINES);
		glColor3f( color[0], color[1], color[2]);
		glVertex2f(prev.a, prev.b);
		glVertex2f(next.a, next.b);
	glEnd();
	glFlush();
}

Point getPoint(Point A, Point B, double t) {
	return Point(
		A.a - (A.a - B.a) * t,
		A.b - (A.b - B.b) * t
	);
}
void endpointInterpolation(Point A, Point B, Point C, Point D, double t) {
	Point one = getPoint(A, B, t);
	Point two = getPoint(B, C, t);
	Point three = getPoint(C, D, t);

	drawFunc(one, two, green);
	drawFunc(two, three, green);
	
	Point line_b = getPoint(one, two, t);
	Point line_e = getPoint(two, three, t);

	drawFunc(line_b, line_e, lightBlue);

	Point res = getPoint(line_b, line_e, t);

	glPointSize(3.0);
	glBegin(GL_POINTS);
	glColor3f(yellow[0], yellow[1], yellow[2]);
	glVertex2f(res.a, res.b);
	glEnd();
	glFlush();
}

void displayFunc() {
	glClear(GL_COLOR_BUFFER_BIT);

	Point prev = A;
	Point next;
	drawFunc(A, B, blue );
	drawFunc(B, C, blue);
	drawFunc(C, D, blue);

	for (double t = 0.0; t <= 1.0; t += 0.05)
	{
		glClearColor(green[0], green[1], green[2], 1.0);
		glClear(GL_ACCUM_BUFFER_BIT);
		glFlush();

		next = getNextPoint(A, B, C, D, t);
		// endpointInterpolation(A, B, C, D, t);
		Sleep(500);
		drawFunc(prev, next, red);
		prev = next;
	}

}

int main(int argc, char * agrv[]) {
	glutInit(&argc, agrv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(600, 600);

	glutInitWindowPosition(100, 150);

	glutCreateWindow("Bezier Curve");

	glutDisplayFunc(&displayFunc);

	glutMainLoop();

	return 0;
}

