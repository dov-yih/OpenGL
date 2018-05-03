#include <windows.h>
#include <math.h>
#include <gl/GL.h>
#include <gl/glut.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * 这是 点 对象，为了方便使用设置的 public 成员变量
 */
class Point {
public:
	double a, b;
	Point():a(0.0),b(0.0){}
	Point(double x,double y):a(x), b(y){};
};

/**
 * 预定义的一些颜色数组，便于在绘制动态过程中便于区分
 * @param green 数组的每个索引对应 R G B 颜色值
 */
double green[3] = { 0.0, 1.0, 0.0 };
double red[3] = { 1.0, 0.0, 0.0 };
double blue[3] = { 0.0, 0.0, 1.0 };
double lightBlue[3] = { 0.0,1.0,1.0 };
double yellow[3] = { 1.0, 1.0, 0.0 };

/**
 * 简化编码，方便调试，将贝塞尔曲线的点都固定掉
 * @param Point 点对象
 */
Point A = Point(-0.9, -0.5);
Point B = Point(-0.3, 0.5);
Point C = Point(0.3, 0.5);
Point D = Point(0.9, -0.5);

/**
 * 这个是函数是按照给定的那个求和公式进行取值的。
 * @param  A A点对象
 * @param  B B点对象
 * @param  C C点对象
 * @param  D D点对象
 * @param  t 参数 t
 * @return   根据公式得到的下一个贝塞尔曲线上的点
 */
Point getNextPoint(Point A, Point B, Point C, Point D, double t)
{
	Point P = Point(0,0);

	double a1 = pow((1 - t), 3);
	double a2 = 3*pow((1 - t), 2)*t;
	double a3 = 3*t*t*(1 - t);
	double a4 = t*t*t;

	P.a = a1 * A.a + a2 * B.a + a3 * C.a + a4 * D.a;
	P.b = a1 * A.b + a2 * B.b + a3 * C.b + a4 * D.b;

	return P;
}

/**
 * 封装的一个函数，主要的功能就是根据传入的两个点和颜色，
 * 绘制一条直线
 * @param prev  直线的起点
 * @param next  直线的终点
 * @param color 直线的颜色数组
 */
void drawFunc(Point prev, Point next, double color[]) {
	glBegin(GL_LINES);
		glColor3f( color[0], color[1], color[2]);
		glVertex2f(prev.a, prev.b);
		glVertex2f(next.a, next.b);
	glEnd();
	glFlush();
}

/**
 * 这个是端点插值的封装的一个函数。
 * 主要功能就是求出 A，B 两点 1/T 之处的坐标，
 * 并返回。
 * @param  A 开始点
 * @param  B 结束点
 * @param  t 参数t
 * @return    A，B 两点 1/T 之处的坐标，
 */
Point getPoint(Point A, Point B, double t) {
	return Point(
		A.a - (A.a - B.a) * t,
		A.b - (A.b - B.b) * t
	);
}

/**
 * 端点插值实现的核心函数。
 * 在假定输入的是三次曲线的前提下：我们做的
 * 就是 求 A,B B,C C,D 三条曲线的 1/T 处
 * 点 one，two，three，再求 one,two，two,
 * three 的 1/T 处的点 line_b,line_e，最后
 * 一次便可求得所求得贝塞尔曲线上的一个点。
 * @param  A A点对象
 * @param  B B点对象
 * @param  C C点对象
 * @param  D D点对象
 * @param  t 参数 t
 */
Point endpointInterpolation(Point A, Point B, Point C, Point D, double t) {
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

	return res;
}

/**
 * 绘制主程序。
 * 主要是一个 for 循环。 令 t 从 0.0 递增到 1.0
 */
void displayFunc() {
	glClear(GL_COLOR_BUFFER_BIT);

	Point prev = A;
	Point next;
	drawFunc(A, B, blue );
	drawFunc(B, C, blue);
	drawFunc(C, D, blue);

	for (double t = 0.0; t <= 1.0; t += 0.05) {
		/**
		 * @NOTE 下面这行是根据公式来求值
		 */
		// next = getNextPoint(A, B, C, D, t);
		/**
		 * @NOTE 如果不想看具体的绘制过程，请取消下面的注释
		 */
		next = endpointInterpolation(A, B, C, D, t);

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
