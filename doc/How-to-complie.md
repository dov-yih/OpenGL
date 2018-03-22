# How to complie

# On Linux
you should shell cmd should like this:

```sh
g++ -o app app.cpp -lglut -lGLU -lGL
```

Ref Here: <https://www.opengl.org/discussion_boards/showthread.php/172614-undefined-reference-to-glutInit>

# Windows

## 安装GLUT工具包    

先下载 GLUT 。

Windows环境下安装GLUT的步骤：    
1. 将下载的压缩包解开，将得到5个文件
2. 以我的安装目录为例：    
  + “d:\Program Files\Microsoft Visual Studio\VC98\include\GL文件夹”。把解压得到的glut.h放到这个GL文件夹里。没有GL文件夹可以自己建一个，一般都有的。
  + “d:\Program Files\Microsoft Visual Studio\VC98\lib文件夹”。把解压得到的glut.lib和glut32.lib放到静态函数库所在文件夹，即lib文件夹。
  + 把解压得到的glut.dll和glut32.dll放到操作系统目录下面的system32文件夹内。（典型的位置为：C:\Windows\System32）这是非常重要的动态链接库设置！  

## 创建工程

步骤如下：    

1. 创建一个Win32 Console Application。（以我创建的为例，工程名为simpleGL）    
+ 链接OpenGL libraries:在Visual C++中先单击Project，再单击Settings，再找到Link单击，最后在Object/library modules 的最前面加上opengl32.lib Glut32.lib Glaux.lib glu32.lib 。    
+ 单击Project Settings中的C/C++标签，将Preprocessor definitions 中的_CONSOLE改为__WINDOWS。最后单击OK。   

现在，准备工作基本上完成了，可不要轻视这一步，如果你没有设置好在编译及运行过程中总会出错的。

对于VS2005可以如下设置：
1. 把 glut.h 复制到 VC 安装路径下的 PlatFormSDK\include\gl 文件夹
2. 把 glut32.lib 复制到 VC 安装路径下的 PlatFormSDK\lib 文件夹
3. 把 glut32.dll 复制到 Windows\System32 文件夹
4. 在 VC 中创建控制台应用程序，在选项中清除“使用预编译头”（以免影响可移植性）
5. 在 VC 中打开项目->属性对话框进行如下设置：
        将“配置”下拉框选则为“所有配置”<br>
        打开 “链接器--输入”项<br>
        在“附加依赖项”中增加:
```
OpenGL32.lib
glu32.lib
glut32.lib
```
>64位的系统应该将glut32.dll同时放入windows下的system32和SysWOW64下，才能找到glut32.dll
