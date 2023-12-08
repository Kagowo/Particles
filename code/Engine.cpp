#include "Engine.h"

Engine::Engine()
{
    VideoMode::getDesktopMode();  
    RenderWindow m_Window(VideoMode::getDesktopMode(), "Particles", Style::Default);

}

void Engine::run()
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

void Engine::input()
{
    Event event;
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
                            int numPoints = rand() % 26 + 25;
                            Particle particle(m_Window, numPoints, { event.mouseButton.x, event.mouseButton.y });
                            m_particles.push_back(particle);
                        }
                    }
            }
            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                m_Window.close();
            }
        
    }


}

void Engine::update(float dtAsSeconds)
{
    for(auto it = m_particles.begin(); it != m_particles.end();)
    {
        if(it->getTTL() > 0.0)
        {
            it->update(dtAsSeconds);
            it++;
        }
        else
        {
            it = m_particles.erase(it);
        }
    }
}

void Engine::draw()
{
    m_Window.clear();
   for (const auto& particle : m_particles)
    {
        m_Window.draw(particle);
    }
    m_Window.display();
}