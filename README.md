# Read Me: Air War

[toc]

## 给Dev-C++配置OpenGL Utility Toolkit（GLUT）

> 2020年12月25日。

> OpenGL是Open Graphics Library。

> 最后参考的文章：https://blog.csdn.net/naocanmani/article/details/84109143。

### 安装glut

首先从OpenGL.org下载[glut的压缩包](https://www.opengl.org/resources/libraries/glut/glutdlls37beta.zip)。

然后复制其中部分文件：（可能需根据Dev-C++安装位置变通）

- 将 *.dll 复制到 C:\Windows\System32 和 C:\Windows\SysWOW64 ，
- 将 *.h 复制到 C:\Program Files (x86)\Dev-Cpp\MinGW64\x86_64-w64-mingw32\include\GL ，
- 将 *.lib 复制到 C:\Program Files (x86)\Dev-Cpp\MinGW64\x86_64-w64-mingw32\lib 。

### 新建项目

文件（Alt+F），新建（N），项目（P）；新项目，Multimedia，OpenGL，C项目。然后根据提示操作。

### 修改项目选项

项目选项（Ctrl+H），编译器、编译器：`TDM-GCC 4.9.2 32-bit Release`。（`64-bit Release`会炸）

> 如果一开始是64-bit，之后才改的，可能无法通过编译。此时删除所有Dev-C++生成的文件（只保留 *.dev, *.h, *.c 文件（带“private”的除外，它也要删除），其它文件都删除。），然后再打开项目（双击 *.dev ），一般会恢复正常。

项目选项，编译器、定制，C编译器、支持所有 ANSI C 标准：`Yes`。

项目选项，编译器、定制，代码生成、语言标准(-std)：`ISO C99`。

项目选项，参数、链接：

```
-lglut32
-lglu32
-lopengl32
-lwinmm
-lgdi32
```

## 版本说明

### 0.0

田老师发的代码。用 conio.h 的`kbhit()`与`getch()`来检测输入，用控制台字符画以及`system("cls");`来显示画面。

### 1.0

> 截至2020年12月25日。

偶然发现Dev-C++竟然支持图形，于是新建了默认OpenGL项目，在此基础上画出了飞机，还实现了移动。但OpenGL只包括图形，无法检测键盘输入等，没法继续做。

### 1.1

> 截至2020年12月25日。

换OpenGL为GLUT。

### 1.2

> 截至2021年1月3日。

键盘操作由修改位移改为力（修改速度），从而更符合物理，也不必长按键盘，绕过了键盘“重复延迟”的问题。

添加了子弹（bullet）和得分（score），其中得分相当于按空格的次数。

飞机驾驶简易手册：

|  按键   |                       功能                       |
| :-----: | :----------------------------------------------: |
|  w/i/↑  |          加速（方向取决于姿态而非速度）          |
|  s/k/↓  |  减速（具体效果取决于比坎星还离谱的空气动力学）  |
|  a/j/←  | 逆时针旋转，一般会间接导致左转，幅度过大可能失控 |
|  d/l/→  |         顺时针旋转，“逆时针旋转”的反方面         |
| (space) |     开火（方向取决于速度和姿态；有频率限制）     |

在项目信息中包含了版本信息。

### 1.3

> 截至2021年1月3日。

修复问题：

- `standardize_angle()`（extended_math.c）：下限差了个负号；虽然没什么影响，但还是改了。
- `move_plane()`（plane.c）：`Drag (rotate)`的`instability`没注意到 $1+\cos\delta$ 不是$\delta$的奇函数。这导致飞机顺时针旋转时，即使过快也不会失控，反而一直抖动。现在多乘了一个符号项。

功能变化：

- 增加靶（target）。
- 完善得分。

已知的问题：

- 同时按多个键时，结果与预期不同。
- 如果直接运行 *.exe ，无法正常退出：关闭（单击窗口右上角的叉号）窗口后，进程仍继续，需要手动在任务管理器里结束进程。若在Dev-C++中运行（F10），则可以”停止运行“（F6），无此问题。

