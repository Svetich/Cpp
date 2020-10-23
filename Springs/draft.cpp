#include <SFML/Graphics.hpp>	
 
using namespace sf; // подключаем пространство имён sf
 
int main()
{
	// Устанавливаем 8-ой уровень сглаживания
	ContextSettings settings;
	settings.antialiasingLevel = 8;
 
	// Объект, который, собственно, является главным окном приложения
	RenderWindow window(VideoMode(500, 300), "SFML Works!", Style::Default, settings);
 
	// Главный цикл приложения: выполняется, пока открыто окно
	while (window.isOpen())
	{
		// Обрабатываем очередь событий в цикле
		Event event;
		while (window.pollEvent(event))
		{
			// Пользователь нажал на «крестик» и хочет закрыть окно?
			if (event.type == Event::Closed)
				window.close(); // тогда закрываем его
		}
		// Установка цвета фона
		window.clear(Color(250, 220, 100, 0));
 
 
		// Линия с заданной толщиной
		RectangleShape line_with_thickness(Vector2f(130.f, 5.f));
		line_with_thickness.rotate(45.f); // поворачиваем её на 45 градусов
		line_with_thickness.setFillColor(Color(15, 180, 140)); // устанавливаем цвет линии
		line_with_thickness.move(250, 150); // перемещаем её в нижний ряд справа от прямоугольника
		window.draw(line_with_thickness); // отрисовка линии
 
		// Линия с нулевой толщиной. Создаём её в качестве массива вершин типа Vortex
		Vertex line_without_thickness[] =
		{
			Vertex(Vector2f(390.f, 240.f)), // координата первой вершины
			Vertex(Vector2f(470.f, 150.f)) // координата второй вершины
		};
		line_without_thickness->color = Color::Black; // устанавливаем цвет линии - чёрный
		window.draw(line_without_thickness, 2, Lines); // отрисовка линии
 
		// Отрисовка окна
		window.display();
	}
 
	return 0;
}