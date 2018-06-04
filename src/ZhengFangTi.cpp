#include <GL/glut.h>
#include<iostream>
#include <math.h>
GLfloat w = 1100;
GLfloat h = 1100;
double rotate_x = 0.0;
double rotate_y = 0.0;
double rotate_z = 0.0;

# define sunshine 255.0/255.0, 210.0/255.0, 166.0/255.0


GLuint texWall;
GLuint texGrass;
GLuint texFloor;

//图像数据在内存块中的偏移量
#define BMP_Header_Length 54   
//旋转角度

static GLfloat angle = 0.0f; 
//材质参数
//材质参数：镜面反射，所得到的光的强度（颜色）
GLfloat matiral_specular[4] = { 0.00, 0.00, 0.00, 1.00 };  
//材质本身就微微的向外发射光线
GLfloat matiral_emission[4] = { 0.00, 0.00, 0.00, 1.00 }; 
const GLfloat matiral_shininess = 11.00;

GLfloat sca[3] = { 1.5, 1.5, 1.5 };
GLfloat tra[3] = { -300, 0, -470 };

// 旋转坐标
GLfloat AngleX;
GLfloat AngleY;


void setMetiral(GLfloat matiral_diffuse_ambient[4]) {
	//glMaterialfv(GL_FRONT,GL_AMBIENT,matiral_ambient); //光线照射到该材质上,经过多次反射
	//	遗留在整个光照环境中的强度（颜色）
	//glMaterialfv(GL_FRONT,GL_DIFFUSE,matiral_diffuse); //光线照射到该材质上,漫反射，所得
	//	到的光的强度（颜色）
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

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();          //增加M矩阵
	glRotatef(rotate_x, 1.0, 0.0, 0.0);
	glRotatef(rotate_y, 0.0, 1.0, 0.0);
	glRotatef(rotate_z, 0.0, 0.0, 1.0);
	//glScalef(1.5, 1.5, 1.5);
	glTranslatef(-470, 0, -470);


	glScalef(sca[0], sca[1], sca[2]);
	glTranslatef(tra[0], tra[1], tra[2]);


	//设置材质
	GLfloat matiral_diffused[4] = { 0.20, 0.32, 0.80, 1.00 };
	setMetiral(matiral_diffused);

	// 绘制这正方形
	// 1
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texFloor);
	glBegin(GL_QUADS);	
	// 贴图顶点							// x, y, z
	glTexCoord2f(0.0f, 0.0f); glVertex3f(60, 60, 260);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(60, 260, 260 );
	glTexCoord2f(1.0f, 1.0f); glVertex3f(260, 260, 260);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(260, 60, 260);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	// 2
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texGrass);
	glBegin(GL_QUADS);		
	glTexCoord2f(0.0f, 0.0f); glVertex3f(60, 60, 260);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(60, 60, 60);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(60, 260, 60);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(60, 260, 260);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	// 3
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texWall);
	glBegin(GL_QUADS);				
	glTexCoord2f(0.0f, 0.0f); glVertex3f(60, 60, 260);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(260, 60, 260);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(260, 60, 60);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(60, 60, 60);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	// 4
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texFloor);
	glBegin(GL_QUADS);				
	glTexCoord2f(0.0f, 0.0f); glVertex3f(60, 60, 60);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(260, 60, 60);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(260, 260, 60);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(60, 260, 60);
	glEnd();
	// 5
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texGrass);
	glBegin(GL_QUADS);				
	glTexCoord2f(0.0f, 0.0f); glVertex3f(260, 60, 260);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(260, 260, 260);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(260, 260, 60);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(260, 60, 60);
	glEnd();
	// 6
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texWall);
	glBegin(GL_QUADS);					
	glTexCoord2f(0.0f, 0.0f); glVertex3f(60, 260, 260);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(60, 260, 60);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(260, 260, 60);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(260, 260, 260);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	// 刷新
	glFlush(); 
	//还要加上swapbuffer函数
	glutSwapBuffers();
}

GLfloat diffuseMaterial[4] = { 0.5, 0.5, 0.5, 1.0 };
//GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.5 };//光源位置
GLfloat light_position[] = { 1.0,1.0,0,0};;//光源位置
GLfloat mat_specular[] = { 0.0, 0.0, 0.0, 1.0 };

void init(void) {
	//glTranslatef(700, 400, 0);
	//glutSolidSphere(35.0, 20, 20);
	//glTranslatef(-700, -400, 0);

	GLfloat sun_direction[] = { 700.0, 400.0, 100.0, 1.0 };
	GLfloat sun_intensity[] = { sunshine, 1.0 };
	GLfloat ambient_intensity[] = { 0.5, 0.5, 0.5, 1.0 };
	
	// Set up ambient light.环境光照
	glEnable(GL_LIGHTING);           
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_intensity);
	//glLightModelfv(GL_AMBIENT, ambient_intensity);

    // Set up sunlight.漫反射
	glEnable(GL_LIGHT0);     
	glLightfv(GL_LIGHT0, GL_POSITION, sun_direction);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_intensity);
    // Configure glColor().
	glEnable(GL_COLOR_MATERIAL);    
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glLineWidth(5); 

	//定义背景颜色-->  黑色
	glClearColor(0.0, 0.0, 0.0, 0.0);

	// 打开混合
	glEnable(GL_BLEND);
	// 关闭深度测试
	glDisable(GL_DEPTH_TEST);
	// 基于源象素alpha通道值的半透明混合函数
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	//打开深度测试
	glEnable(GL_DEPTH_TEST);

	// 貌似和视角有关的定义 places the camera at (0,0,0) and faces it along(0,0,-1).
	glMatrixMode(GL_PROJECTION);
	glOrtho(-w, w, -h, h, -w, w); 
}

 //键盘相应函数
void specialkeys(int key, int x, int y){  

	//旋转
	if (key == GLUT_KEY_RIGHT)
		rotate_y -= 1;
	else if (key == GLUT_KEY_LEFT)
		rotate_y += 1;
	else if (key == GLUT_KEY_DOWN)
		rotate_x -= 1;
	else if (key == GLUT_KEY_UP)
		rotate_x += 1;

	//场景放缩
	if (key == GLUT_KEY_F7){
		for (int i = 0; i < 3; i++)
			sca[i] = sca[i] + 0.1;
	} else if (key == GLUT_KEY_F8){
		for (int i = 0; i < 3; i++)
			sca[i] = sca[i] - 0.1;
	}
	glutPostRedisplay();
}

// 函数power_of_two用于判断一个整数是不是2的整数次幂
int power_of_two(int n) {
	if (n <= 0)
		return 0;
	return (n & (n - 1)) == 0;
}

/* 函数load_texture
* 读取一个BMP文件作为纹理
* 如果失败，返回0，如果成功，返回纹理编号
*/
GLuint load_texture(const char* file_name) {
	GLint width, height, total_bytes;
	GLubyte* pixels = 0;
	GLuint last_texture_ID = 0, texture_ID = 0;
	FILE *pFile;
	errno_t err;

	// 打开文件，如果失败，返回
	if ((err = fopen_s(&pFile, file_name, "rb")) != 0) {
		//如果打不开，就输出打不开
		printf("can't open file: %s\n",file_name);   
		//终止程序
		exit(0);
	}

	// 读取文件中图象的宽度和高度
	fseek(pFile, 0x0012, SEEK_SET);
	fread(&width, 4, 1, pFile);
	fread(&height, 4, 1, pFile);
	fseek(pFile, BMP_Header_Length, SEEK_SET);

	// 计算每行像素所占字节数，并根据此数据计算总像素字节数
	{
		GLint line_bytes = width * 3;
		while (line_bytes % 4 != 0)
			++line_bytes;
		total_bytes = line_bytes * height;
	}

	// 根据总像素字节数分配内存
	pixels = (GLubyte*)malloc(total_bytes);
	if (pixels == 0) {
		fclose(pFile);
		return 0;
	}

	// 读取像素数据
	if (fread(pixels, total_bytes, 1, pFile) <= 0) {
		free(pixels);
		fclose(pFile);
		return 0;
	}

	// 对就旧版本的兼容，如果图象的宽度和高度不是的整数次方，则需要进行缩放
	// 若图像宽高超过了OpenGL规定的最大值，也缩放
	{
		GLint max;
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
		if (!power_of_two(width)
			|| !power_of_two(height)
			|| width > max
			|| height > max)
		{
			// 规定缩放后新的大小为边长的正方形
			const GLint new_width = 256;
			const GLint new_height = 256; 
			GLint new_line_bytes, new_total_bytes;
			GLubyte* new_pixels = 0;

			// 计算每行需要的字节数和总字节数
			new_line_bytes = new_width * 3;
			while (new_line_bytes % 4 != 0)
				++new_line_bytes;
			new_total_bytes = new_line_bytes * new_height;

			// 分配内存
			new_pixels = (GLubyte*)malloc(new_total_bytes);
			if (new_pixels == 0) {
				free(pixels);
				fclose(pFile);
				return 0;
			}

			// 进行像素缩放
			gluScaleImage(GL_RGB,
				width, height, GL_UNSIGNED_BYTE, pixels,
				new_width, new_height, GL_UNSIGNED_BYTE, new_pixels);

			// 释放原来的像素数据，把pixels指向新的像素数据，并重新设置width和height
			free(pixels);
			pixels = new_pixels;
			width = new_width;
			height = new_height;
		}
	}

	// 分配一个新的纹理编号
	glGenTextures(1, &texture_ID);
	if (texture_ID == 0) {
		free(pixels);
		fclose(pFile);
		return 0;
	}

	// 绑定新的纹理，载入纹理并设置纹理参数
	// 在绑定前，先获得原来绑定的纹理编号，以便在最后进行恢复
	GLint lastTextureID = last_texture_ID;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &lastTextureID);
	glBindTexture(GL_TEXTURE_2D, texture_ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
	//恢复之前的纹理绑定
	glBindTexture(GL_TEXTURE_2D, lastTextureID);  
	free(pixels);
	return texture_ID;
}

 //  main函数 增加键盘事件
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(w, h);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("The House");
	init();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
   
	// 启用纹理
	glEnable(GL_TEXTURE_2D); 
	//加载纹理
	texWall = load_texture("wall.bmp"); 
	texGrass = load_texture("grass.bmp");
	texFloor = load_texture("floor.bmp");

	glutDisplayFunc(display);
	//调用键盘控制函数
	glutSpecialFunc(specialkeys); 
	glutMainLoop();
	return 0;
}
