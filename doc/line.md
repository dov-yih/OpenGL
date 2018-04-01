# OpenGL 画线


## 原理

在显示屏上所有的图形都是一个个的像素点组成。我们看到说有直线，曲线都是像素点拟合出来的产物。

这里使用 Bresenham 算法，来实现一个基本的画线函数

Bresenham 的基本原理是: 求出 x 坐标增加 1 时， y 坐标的增加值， 每当 x 加 1 时， y 坐标增加一个斜率 k， 再进行四舍五入。


## OpenGL 函数解释

```cpp
int main(int argc， char** argv) {
    glutInit(&argc， argv);

    glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );
    glutInitWindowPosition( 50， 100 );
    glutInitWindowSize( WIDTH， HEIGHT );
    glutCreateWindow( "Bresenhan Line" );

    glutDisplayFunc( drawFunc );

    glutMainLoop( );

    return 0;
}
```

### `main` 函数

main 函数模板就是这样。

可以自定义 glutInitWindowPosition，glutInitWindowSize，glutCreateWindow 函数

#### `glutInitWindowPosition` 函数

窗口所处位置。 原点是屏幕右上角。参数是整型。

#### `glutInitWindowSize` 函数

窗口的初始化大小。

#### `glutCreateWindow` 函数

该函数负责创建窗口。参数为字符串。

#### `glutDisplayFunc` 函数

所有画图相关的函数在，glutDisplayFunc 里的 drawFunc 里面实现．

### 作画函数

```cpp
void drawFunc() {
  glClear( GL_COLOR_BUFFER_BIT );
  glColor3f( 1.0， 1.0， 1.0 );
  glBegin( GL_LINES );
    glVertex2f( 0， -1.0 );
    glVertex2f( 0， 1.0 );
    glEnd();
  glFlush();
}
```
### `glClear()`

清空缓冲区

### `glColor3f()`

设置绘画出的线条的颜色，RGB 形式

### `glBegin()` & `glEnd()`

两个函数必须成对出现。

glBegin 的参数代表其两个函数之间所画图形的种类。

其可能是参数有 `GL_LINES`， `CL_POINTS`， `CL_TRIANGLE` 。。。

### `glVertex2f()`

是 glVertex*() 系列函数中的一个。其参数的值为 -1 ~ 1

## Feature

为了便于查看做出来的点位置，实现了一个网格背景。

```cpp
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
```
## 缺点

原算法假定斜率在 0～1 之间。

### Trick

这里我自己实现了一个斜率从 0 到 ∞ 的算法，但是由于原算法画出的“直线”在某些情况会存在差异，所以默认不使用。要尝试的话请手动取消`src/line.cpp`**第 33 行**注释。

测试时， `k = 4` 画出的直线没有问题

核心部分：

```cpp
#ifdef K
    ye = y;
#else
    ye = -0.5;
#endif

// codes & code

    #ifdef K
        /*
        斜率再 0～正无穷
         */
        // x y 应该同时改变
        y = (int)( ye + 0.5 );
    #else
        /**
        这里假设斜率在 0 ~ 1 之间
        */
        if (ye > 0) {
            y++;
            ye--;
        }
    #endif
```
