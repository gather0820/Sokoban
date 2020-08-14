# 1. Instructions

1. Assignment A

I have passed Assignment A during the term.

![](https://github.com/gather0820/C101/blob/master/AssignmentA.png?raw=true)

In assignment A, I have a camera to roam, and the mouse can control the moving angle of view. In Shader Function,read the external vertex shader and fragment shader and create the program . In draw Function,bundle the obtained material and model information according to a certain combination, and finally draw the model by the draw array method . The OBJ model is loaded by reading Obj coordinate, Texture coordinates and Normal coordinates. You can also turn wireframe mode on or off. And lights make objects more three-dimensional.

------



2. Visual Studio & C++

2.1 Open Visual Studio Installer

2.2 Change Visual Studio Community 2019-Windows​ t​o  :white_check_mark:C++, than click change.

3. Set "Include" and "Library"

3.1 Open "Sokoban_v1.0" property pages

![](https://github.com/gather0820/C101/blob/master/Properties.png?raw=true)

3.2 Set `VC++ Directories`->`Include Directories` and `Library Directories`

![](https://github.com/gather0820/C101/blob/master/set%20gl&lib.png?raw=true)

Include Directories: `.\gl;$(IncludePath)`

Library Directories: `.\lib;$(LibraryPath)`

3.3 Set `C/C++` -> `General` -> `Additional Include Directories`

![](https://github.com/gather0820/C101/blob/master/setgl.png?raw=true)

Additional Include Directories: `.\gl;%(AdditionalIncludeDirectories)`

3.4 Set `Linker` -> `General` -> `Additional Library Directories`

![](https://github.com/gather0820/C101/blob/master/setlib.png?raw=true)

Additional Library Directories: `.\lib;%(AdditionalLibraryDirectories)`



# 2.Code

1. MAP

这段代码的作用是读取地图`map.txt`，存储读取到内存中。

```C++
void sokoban::initMap(const char * fileName)
{
	ifstream infile(fileName);
	for (int k = 0; k < m_currentState; k++)
	{
		infile >> m_row;
		infile >> m_col;
		infile >> m_boxNum;

		for (int i = 0; i < m_row; i++)
			for (int j = 0; j < m_col; j++)
				infile >> Map[i][j];

		for (int i = 0; i < m_boxNum; i++)
		{
			infile >> m_boxPosition[i].x;
			infile >> m_boxPosition[i].y;
		}
		infile >> m_peoplePosition.x;
		infile >> m_peoplePosition.y;
	}
	infile.close();
	initBox();
}
```



2. BMP

这段代码的作用是加载位图。打开指针并打开文件，通过iglaux函数，获取到位图的数据的指针并返回。

```C++
AUX_RGBImageRec * sokoban::initBmpData(const char * Filename)
{
	FILE *File = NULL;									 
	if (!Filename)	return NULL;
	File = fopen(Filename, "r");		
	
	if (File)											
	{
		fclose(File);									
		return auxDIBImageLoad(Filename);				
	}
	return NULL;
}
```



3. 终点的判断

以向下移动为例。获取人物当前位置坐标后，判断在该坐标下，Y轴负方向一个单位长度坐标所对应的枚举值。若枚举值为2则表示当前任务向下移动到终点位置。

```C++
bool sokoban::moveDown(void)
{
	int curx = m_peopleDPosition.x;
	int cury = m_peoplePosition.y;
	m_peoplePosition.y -= 1;
	if (Map[curx][cury - 1] == MAP_DEST && isBox(curx, cury - 1))
		m_reachBox -= 1;
	if (isBox(curx, cury - 1))
	{
		Point_S *temp = GetBoxPosition(curx, cury - 1);
		temp->y -= 1;
		if (Map[curx][cury - 2] == MAP_DEST)
			m_reachBox += 1;
	}
	return TRUE;
}
```

4. BOX

判断当前坐标是否是箱子，如果是箱子，则将i和j的值存储在Point_S结构体所定义的数组中，分别作为x坐标和y坐标的值。

```C++
bool sokoban::isBox(int i, int j)
{
	for (int k = 0; k<m_boxNum; k++)
	{
		if (m_boxPosition[k].x == i && m_boxPosition[k].y == j)
			return TRUE;
	}
	return FALSE;
}
```

5. Video Report

Please click the link to open: https://youtu.be/i8mLVEF6kpo