#include "Engine.h"

Engine::Engine()
{
    m_Window.create(VideoMode::getDesktopMode(), "Particles"); //Opening the window
}

void Engine::run()
{
    srand(time(0)); //seed points in the particle
    Clock clock; //Measure elapsed time
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
    for(vector<Particle>::iterator it = m_particles.begin(); it != m_particles.end();) //Iterating through the particle list
    {
        if(it->getTTL() > 0.0) //checking if particle should still be live
        {
            it->update(dtAsSeconds); //updating particle
            it++; //moving to next particle
        }
        else
        {
            it = m_particles.erase(it);//Erasing particle if its TTL is zero
        }
    }
}

void Engine::draw()
{
    m_Window.clear(); //Clear window
   for (auto& p : m_particles) //Iterates through particles
    {
        m_Window.draw(p);//draws particles
    }
    m_Window.display();//Displays the window
}