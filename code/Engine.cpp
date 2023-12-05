#include "Engine.h"

Engine::Engine()
{
    VideoMode::getDesktopMode();  
    RenderWindow m_Window(VideoMode::getDesktopMode(), "Particles", Style::Default);

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
                        if(m_particles.size() < 5)
                        {
                            m_particles.push_back(Particle(event.mouseButton.x,event.mouseButton.y));
                        }
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
    m_Window.clear();
    for(int x = 0; x < m_particles.size(); x++)
    {
        particle.draw();
    }
    m_Window.display();
}

void run()
{
    Clock clock;
    cout << "Starting Particle unit tests..." << endl;
    Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
    p.unitTests();
    cout << "Unit tests complete.  Starting engine..." << endl;
    Event event;
    while(m_Window.isOpen())
    {
        Time elapsed = clock.restart();
        float dt = elapsed.asSeconds();
        input();
        update(dt);
        draw();
    }
}