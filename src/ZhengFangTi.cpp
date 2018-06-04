#define _CRT_SECURE_NO_DEPRECATE //为了高版本VS中使用fopen（）函数
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include   <malloc.h>
#include <stdlib.h>

#define PI 3.14159265359

static GLuint texName[4];//存放纹理
static double Ox = 0;
static double Oy = 0;
static double direction = 0;//站立位置及前进方向；
static double step = 0.2;
static GLfloat angle = 0.0f;

GLUquadricObj * g_text;//曲面，制作一个包围房间的大球体做背景

					   //材质参数
					   //材质参数：镜面反射，所得到的光的强度（颜色）
GLfloat matiral_specular[4] = { 0.00, 0.00, 0.00, 1.00 };
//材质本身就微微的向外发射光线
GLfloat matiral_emission[4] = { 0.00, 0.00, 0.00, 1.00 };

const GLfloat matiral_shininess = 11.00;

//设置材质
GLfloat matiral_diffused[4] = { 0.20, 0.32, 0.80, 1.00 };

void setMetiral(GLfloat matiral_diffuse_ambient[4]) {
	GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);  //光线照射到该材质上,经过多次反射
	//	遗留在整个光照环境中的强度（颜色）
	//设置颜色
	//设置相同值更逼真
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matiral_diffuse_ambient);
	//设置参数
	//镜面反射，所得到的光的强度（颜色）
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matiral_specular);
	//材质本身就微微的向外发射光线，以至于眼睛感觉到它有这样的颜色
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, matiral_emission);
	//“镜面指数”（0~128） 该值越小，材质越粗糙，点光源发射的光线照射到上面，也可以产生较大
	//	的亮点。该值越大，表示材质越类似于镜面，光源照射到上面后，产生较小的亮点。
	glMaterialf(GL_FRONT_AND_BACK, matiral_shininess, 0);
}

void loadTexture(const char* filename, GLuint &texture) {
	static GLint    ImageWidth;
	static GLint    ImageHeight;
	static GLint    PixelLength;
	static GLubyte* PixelData;
	// 打开文件
	FILE* pFile = fopen(filename, "rb");
	if (pFile == 0)
		exit(0);
	// 读取24位bmp图象的大小信息
	fseek(pFile, 0x0012, SEEK_SET);
	fread(&ImageWidth, sizeof(ImageWidth), 1, pFile);
	fread(&ImageHeight, sizeof(ImageHeight), 1, pFile);
	// 计算像素数据长度
	PixelLength = ImageWidth * 3;
	//bmp图像保证数据区域的长度是4的倍数
	while (PixelLength % 4 != 0) {
		++PixelLength;
	}
	PixelLength *= ImageHeight;
	// 读取像素数据
	PixelData = (GLubyte*)malloc(PixelLength);
	if (PixelData == 0)
		exit(0);
	fseek(pFile, 54, SEEK_SET);
	fread(PixelData, PixelLength, 1, pFile);
	// 关闭文件
	fclose(pFile);

	//加载纹理
	//用来生成纹理的数量   存储纹理索引的第一个元素指针
	glGenTextures(1, &texture);
	//绑定（指定）纹理对象
	glBindTexture(GL_TEXTURE_2D, texture);
	//纹理过滤函数
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ImageWidth, ImageHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, PixelData);
	//生成一个2D纹理（Texture）。bmp图片的像素顺序是BGR所以用GL_BGR_EXT来反向加载数据
}

void init(void) {
	//清除颜色缓冲区，设置颜色
	glClearColor(0.0, 0.0, 0.0, 0.0);
	//设置着色模式 GL_FLAT 恒定着色，GL_SMOOTH光滑着色
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
	//这句代码需放置在绘图及显示之前
	g_text = gluNewQuadric();
	//图片与程序源代码放置在同一目录下即可
	loadTexture("floor3.bmp", texName[0]);
	loadTexture("wall2.bmp", texName[1]);
	loadTexture("ceiling2.bmp", texName[2]);
	loadTexture("wall.bmp", texName[3]);
	//所读取的图像数据的行对齐方式
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}

void display(void) {
	//清除颜色缓冲以及深度缓冲
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	//纹理和材质混合方式
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	setMetiral(matiral_diffused);

	glPushMatrix();

	glRotatef((GLfloat)direction, 0.0, 0.0, 1.0);

	glTranslated(Ox, Oy, 0.0);
	glBindTexture(GL_TEXTURE_2D, texName[3]);

	gluSphere(g_text, 30, 15, 15);
	//建立纹理坐标
	gluQuadricTexture(g_text, GLU_TRUE);
	//用面填充
	gluQuadricDrawStyle(g_text, GLU_FILL);

	//地板
	glBindTexture(GL_TEXTURE_2D, texName[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-10.0, -10.0, 0.0);
	glTexCoord2f(0.0, 10.0); glVertex3f(-10.0, 10.0, 0.0);
	glTexCoord2f(10.0, 10.0); glVertex3f(10.0, 10.0, 0.0);
	glTexCoord2f(10.0, 0.0); glVertex3f(10.0, -10.0, 0.0);
	glEnd();

	//四周墙壁
	glBindTexture(GL_TEXTURE_2D, texName[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-10.0, -10.0, 0.0);
	glTexCoord2f(0.0, 10.0); glVertex3f(-10.0, -10.0, 10.0);
	glTexCoord2f(10.0, 10.0); glVertex3f(-10.0, 10.0, 10.0);
	glTexCoord2f(10.0, 0.0); glVertex3f(-10.0, 10.0, 0);

	glTexCoord2f(0.0, 0.0); glVertex3f(10.0, -10.0, 0.0);
	glTexCoord2f(0.0, 10.0); glVertex3f(10.0, -10.0, 10.0);
	glTexCoord2f(10.0, 10.0); glVertex3f(10.0, 10.0, 10.0);
	glTexCoord2f(10.0, 0.0); glVertex3f(10.0, 10.0, 0);

	glTexCoord2f(0.0, 0.0); glVertex3f(-10.0, 10.0, 0.0);
	glTexCoord2f(0.0, 10.0); glVertex3f(-10.0, 10.0, 10.0);
	glTexCoord2f(10.0, 10.0); glVertex3f(10.0, 10.0, 10.0);
	glTexCoord2f(10.0, 0.0); glVertex3f(10.0, 10.0, 0.0);

	glTexCoord2f(0.0, 0.0); glVertex3f(-10.0, -10.0, 0.0);
	glTexCoord2f(0.0, 10.0); glVertex3f(-10.0, -10.0, 10.0);
	glTexCoord2f(10.0, 10.0); glVertex3f(10.0, -10.0, 10.0);
	glTexCoord2f(10.0, 0.0); glVertex3f(10.0, -10.0, 0);
	glEnd();

	//房顶
	glBindTexture(GL_TEXTURE_2D, texName[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-10.0, -10.0, 10.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(-10.0, 10.0, 10.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(10.0, 10.0, 10.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(10.0, -10.0, 10.0);
	glEnd();

	glPopMatrix();

	//用于强制刷新缓存
	glFlush();
	//交换双缓存
	glutSwapBuffers();
	//标志下次刷新，没有的话，程序打开后不会刷新界面
	glutPostRedisplay();
}
void reshape(int w, int h) {
	//在默认情况下，视口被设置为占据打开窗口的整个像素矩形
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	//选择投影矩阵
	glMatrixMode(GL_PROJECTION);
	//重置当前指定的矩阵为单位矩阵
	glLoadIdentity();
	//角度，宽高比，z轴近处，远处。
	gluPerspective(90.0, (GLfloat)w / (GLfloat)h, 0.1, 30.0);
	//模型视景矩阵||GL_TEXTURE,对纹理矩阵堆栈应用随后的矩阵操作.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 3, 0, 10, 3, 0.0, 0.0, 1.0);
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'w':;
	case 'W':
		Ox -= step * sin(direction / 180 * PI);
		Oy -= step * cos(direction / 180 * PI);
		glutPostRedisplay();
		break;
	case 's':;
	case 'S':
		Ox += step * sin(direction / 180 * PI);
		Oy += step * cos(direction / 180 * PI);
		glutPostRedisplay();
		break;
	case 'a':
	case 'A':
		direction = direction - 2;
		glutPostRedisplay();
		break;
	case 'd':;
	case 'D':
		direction = direction + 2;
		glutPostRedisplay();
		break;
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}
int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Zheng Fang Ti");

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
