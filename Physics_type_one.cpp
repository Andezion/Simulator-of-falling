#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class ball
{
public:
    float radius; // ������ 
    float height; // ������ 
    float speed; // �������� 
    float e; // ��������� 

    float kinetic_energy = 0; // ������������ ������� ����
    float potencial_energy = 0; // ������������� ������� ���� 
    float initial_height; // ��������� ������
    float initial_speed; // ��������� �������� 

    CircleShape circle;

    bool where_to_move; // ���������� ��� ������������ ����������� ��������
    bool is_moving; // ���������� ��� ������������ �������� � ����� 

    ball(float n_radius, float n_height, float n_speed, float n_e) // ��� ����������� 
    {
        radius = n_radius; // ������ ������ ���� 

        height = n_height; // ������ ������� 
        initial_height = n_height; // ��������� ��������� ������

        speed = n_speed; // �������� �������� 
        initial_speed = speed; // �������� ���������

        e = n_e; // ���������� ��������� 

        where_to_move = false; // ��������� ����������� �������� ����
        is_moving = true; // ��������� �������� ���� 

        circle.setRadius(radius);
        circle.setFillColor(Color::Red);
        circle.setPosition(300, height);
    }

    void draw(RenderWindow& window) // ��������� 
    {
        window.draw(circle);
    }

    void path()
    {
        float gravity = 0.000098;

        if (initial_height < 20.0f)
        {
            is_moving = false;
            return;
        }
        if (is_moving)
        {
            if (where_to_move)
            {
                speed = speed - gravity;
                height -= speed;
                if (height <= initial_height)
                {
                    height = initial_height;
                    speed = 0;
                    where_to_move = false; // ������ ����������� �� ����
                }
            }
            else
            {
                speed = speed + gravity;
                height += speed;
                if (height >= 580.0f)
                {
                    height = 580.0f;

                    if (e * e == 1)
                    {
                        initial_height = initial_height;
                    }
                    else
                    {
                        initial_height = initial_height * e * e;
                    }
                    if (initial_height > 580.0f)
                    {
                        initial_height = 580.0f;
                    }

                    where_to_move = true; // ������ ����������� �� �����
                }
            }
        }

        circle.setPosition(circle.getPosition().x, height);
    }
};

void energy_law(float speed, float heigth)
{
    float potencial = 1 * heigth * 0.098;
    float kinetic = 1 * speed * speed / 2;
}

int main()
{
    RenderWindow window(VideoMode(900, 600), "Tested");

    ball test(10, 50, 0.0001, 1.3544);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Q))
            {
                window.close();
            }
        }

        test.path();

        window.clear();

        test.draw(window);

        window.display();
    }

    return 0;
}