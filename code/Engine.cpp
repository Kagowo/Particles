#include "Engine.h"

Engine::Engine()
{
    VideoMode::getDesktopMode();  
    RenderWindow m_Window(vm, "Particles", Style::Default);

}

void run()
{

    cout << "Starting Particle unit tests..." << endl;
    Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
    p.unitTests();
    cout << "Unit tests complete.  Starting engine..." << endl;
    Event event;
    while(m_Window.isOpen())
    {
        input();
        update(dtAsSeconds);
        draw();
    }
}

void input()
{
    while(m_Window.pollEvent(event))
    {
       if (event.type == Event::Closed)
            {
                m_Window.close();
            }
            if (event.type == Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    std::cout << "the left button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                }
            }

            if (event.type == Event::MouseMoved)
            {

            }
            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                m_Window.close();
            }
        
    }


}

void update(float dtAsSeconds)
{

}

void draw()
{

}
