# OpenGL 入门指南

## main 函数

```cpp
/**
 * main 函数
 * 模板就是这样 :(
 * 可以自定义 ~Position，~Size 函数的参数
 * 所有画图相关的函数在，glutDisplayFunc 里的
 * drawFunc 里面实现
 */
int main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );
	glutInitWindowPosition( 50, 100 );
	glutInitWindowSize( WIDTH, HEIGHT );
	glutCreateWindow( "Bresenhan Line" );


	glutDisplayFunc( drawFunc );

	glutMainLoop( );

	return 0;
}
```
## 作画函数

```cpp
void drawFunc() {
  glClear( GL_COLOR_BUFFER_BIT );
  glColor3f( 1.0, 1.0, 1.0 );
  glBegin( GL_LINES );
    glVertex2f( 0, -1.0 );
    glVertex2f( 0, 1.0 );
    glEnd();
  glFlush();
}
```
### glClear()

清空缓冲区

### glColor3f()

设置绘画出的线条的颜色，RGB 形式

### glBegin() & glEnd()

两个函数必须成对出现。

glBegin 的参数代表其两个函数之间所画图形的种类。

### glVertex2f()

是 glVertex*() 系列函数中的一个。其参数的值为 -1 ~ 1
