#include "Engine.h"

Engine::Engine()
{
    m_Window.create(VideoMode::getDesktopMode(), "Particles");
}

void Engine::run()
{
    srand(time(0));
    Clock clock;
    cout << "Starting Particle unit tests..." << endl;
    Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
    p.unitTests();
    cout << "Unit tests complete.  Starting engine..." << endl;
    
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
                        int nParticles = 5;
                        for(int x = 0; x < nParticles; x++)
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
    for(vector<Particle>::iterator it = m_particles.begin(); it != m_particles.end();)
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
   for (auto& p : m_particles)
    {
        m_Window.draw(p);
    }
    m_Window.display();
}