#include <conio.h>
#include <windows.h>
#include <vector>
#include <iostream>
#include <string>


using namespace std;

class shape {
public:
	virtual void show(HDC hdc) {}
	virtual void show_info() {}
};

class point : shape {
public:
	int x, y;

	COLORREF color;
	point(int x, int y, COLORREF c = RGB(255, 255, 255)) : x(x), y(y), color(c) {}
	void show(HDC hdc) override
	{
		SetPixel(hdc, x, y, color);
	}
	void show_info() {
		std::cout << "This is poitn" << std::endl;
		std::cout << "Coordinate " << "X" << this->x << " Y" << this->y << std::endl;
		std::cout << "Color " << color << std::endl;
	}
	

};
class polygon : shape {

	COLORREF color, background_color;
	bool filled;
	POINT pt[3];
public:
	polygon(int x1, int y1, int x2, int y2, int x3, int y3, COLORREF c, bool filled, COLORREF bc) {
		this->filled = filled;
		color = c;
		background_color = bc;
		pt[0].x = x1;
		pt[0].y = y1;
		pt[1].x = x2;
		pt[1].y = y2;
		pt[2].x = x3;
		pt[2].y = y3;
	}
	void show(HDC hdc) {
		SelectObject(hdc, GetStockObject(DC_PEN)); // выбор стандартного пера
		SetDCPenColor(hdc, color); // установка цвета контура фигуры
		SetDCBrushColor(hdc, background_color); // установка цвета закраски
		if (filled)
		{
			SelectObject(hdc, GetStockObject(DC_BRUSH)); // выбор стандартной кисти
		}
		else
		{
			SelectObject(hdc, GetStockObject(NULL_BRUSH)); // отключение закраски
		}
		Polygon(hdc, pt, 3);
	}
	void show_info() {
		std::cout << "This is line" << std::endl;
		std::cout << "First point " << "X:" << pt[0].x << "Y:" << pt[0].y << std::endl;
		std::cout << "Second point " << "X:" << pt[1].x << "Y:" << pt[1].y << std::endl;
		std::cout << "Third point " << "X:" << pt[2].x << "Y:" << pt[2].y << std::endl;
		std::cout << "Color " << color << std::endl;
		if (filled) {
			std::cout << "Background color" << background_color << std::endl;
		}
	}
};
class line : shape {
	point start_point, end_point;
	COLORREF color;
public:
	line(int x1, int y1, int x2, int y2, COLORREF c) : start_point(x1, y1), end_point(x2, y2), color(c) {}
	void show(HDC hdc) {
		SelectObject(hdc, GetStockObject(DC_PEN));
		SetDCPenColor(hdc, color);
		MoveToEx(hdc, start_point.x, start_point.y, NULL);
		LineTo(hdc, end_point.x, end_point.y);
	}
	
};
class rectangle : shape {
	point top_left, bottom_right;
	COLORREF color, background_color;
	bool filled;
public:
	rectangle(int x1, int y1, int x2, int y2, COLORREF c, bool filled = false, COLORREF bc = 0) : top_left(x1, y1), bottom_right(x2, y2), color(c), background_color(bc), filled(filled) {}
	void show(HDC hdc) {
		SelectObject(hdc, GetStockObject(DC_PEN)); // выбор стандартного пера
		SetDCPenColor(hdc, color); // установка цвета контура фигуры
		SetDCBrushColor(hdc, background_color); // установка цвета закраски
		if (filled)
		{
			SelectObject(hdc, GetStockObject(DC_BRUSH)); // выбор стандартной кисти
		}
		else
		{
			SelectObject(hdc, GetStockObject(NULL_BRUSH)); // отключение закраски
		}
		Rectangle(hdc, top_left.x, top_left.y, bottom_right.x, bottom_right.y);
	}
	
};
class ellipse : shape {

	point top_left, bottom_right;
	COLORREF color, background_color;
	bool filled;
public:
	ellipse(int x1, int y1, int x2, int y2, COLORREF c, bool filled = false, COLORREF bc = 0)
		: top_left(x1, y1), bottom_right(x2, y2), color(c), background_color(bc), filled(filled) {}
	void show(HDC hdc) {
		SelectObject(hdc, GetStockObject(DC_PEN)); // выбор стандартного пера
		SetDCPenColor(hdc, color); // установка цвета контура фигуры
		SetDCBrushColor(hdc, background_color); // установка цвета закраски
		if (filled)
		{
			SelectObject(hdc, GetStockObject(DC_BRUSH)); // выбор стандартной кисти
		}
		else
		{
			SelectObject(hdc, GetStockObject(NULL_BRUSH)); // отключение закраски
		}
		Ellipse(hdc, top_left.x, top_left.y, bottom_right.x, bottom_right.y);
	}
	
};
class canvas
{
	vector<shape*> figures;
	HWND hWnd;
	HDC hdc;

public:
	canvas()
	{
		hWnd = GetConsoleWindow();
		hdc = GetDC(hWnd);
	}
	~canvas()
	{
		ReleaseDC(hWnd, hdc);
	}
	

	void show_shape_info(int index) {
		figures[index]->show_info();
	}

	void add(shape* s)
	{
		figures.push_back(s);
		
	}
	void clear()
	{
		figures.clear();
	}

	void show() {
		for (size_t i = 0; i < figures.size(); i++)
			figures[i]->show(hdc);
	}

	void delete_figure(int index) {
		if (index != figures.size() - 1) {
			figures[index] = figures.back();
		}
		figures.resize(figures.size() - 1);
	
	}
};