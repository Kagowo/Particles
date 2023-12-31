#include "Particle.h"

//Constructor for particle
Particle::Particle(sf::RenderTarget& target, int numPoints, sf::Vector2i mouseClickPosition) : m_A(2, numPoints) //initializes matrix
{
    m_ttl = TTL;// Time to live
    m_numPoints = numPoints; //points on the particle
    m_radiansPerSec = ((float)rand() / RAND_MAX) * M_PI; //rotation speed
    m_cartesianPlane.setCenter(0,0); //setting the center of the cartesian plane
    m_cartesianPlane.setSize(target.getSize().x, -1.0 * target.getSize().y); //setting size cartesian plane
    m_centerCoordinate = target.mapPixelToCoords(mouseClickPosition, m_cartesianPlane); // maps the click positions on the cartesian plane
    m_vx = (rand() % 2 != 0 ? 1 : -1) * (rand() % 401 + 100); //horizontal velocity
    m_vy = rand() % 401 + 100; //vertical velocity
    m_color1 = sf::Color::White; //color
    m_color2 = Color(rand() % 256, rand() % 256, rand() % 256); //Random second color

    //Initializing the position of each particle
    float theta = 0.0f;
    float dTheta = 2.0f * M_PI / (numPoints - 1);

    for (int j = 0; j < numPoints; j++)
    {
        float r = (float)(rand() % 61 + 20);
        float dx = r * cos(theta);
        float dy = r * sin(theta);

        m_A(0, j) = m_centerCoordinate.x + dx;
        m_A(1, j) = m_centerCoordinate.y + dy;

        theta += dTheta;
    }
}

void Particle::draw(RenderTarget& target, RenderStates states) const
{
    VertexArray lines(TriangleFan, m_numPoints + 1); //Array for particle
    Vector2f center = static_cast<Vector2f>(target.mapCoordsToPixel(m_centerCoordinate, m_cartesianPlane)); 

    lines[0].position = center;//sets the center of the particle
    lines[0].color = m_color1;//sets its color

    for(int j = 1; j <= m_numPoints; j++)
    {        
        //Sets the poston and color for each particle
        lines[j].position = static_cast<Vector2f>(target.mapCoordsToPixel({m_A(0, j - 1), m_A(1, j - 1)}, m_cartesianPlane));
        lines[j].color = m_color2;
    }

    target.draw(lines); //draws particle

}


//updates the particle as time goes by
void Particle::update(float dt)
{
    m_ttl -= dt;//subtracting time to live
    rotate(dt * m_radiansPerSec); //rotation of particle
    scale(SCALE); //applies the scaling

    //sets the movement of the particle
    float dx = m_vx * dt;
    m_vy -= G * dt;
    float dy = m_vy * dt;

    translate(dx,dy);

}

//Moves the particle
void Particle::translate(double xShift, double yShift)
{
    TranslationMatrix T(xShift,yShift,m_A.getCols());
    m_A = T + m_A; //applies the shift to all the points

    //updates the center
    m_centerCoordinate.x += xShift;
    m_centerCoordinate.y += yShift;
}

//rotates the particle
void Particle::rotate(double theta)
{
    Vector2f temp = m_centerCoordinate; //temporarily saves the center
    translate(-m_centerCoordinate.x, -m_centerCoordinate.y); //moves the particle/rotates it
    RotationMatrix R(theta);//creates the new matrix
    m_A = R * m_A; //applies the rotation to the particle
    translate(temp.x, temp.y);

}

//Scales the particles size
void Particle::scale(double c)
{
    Vector2f temp = m_centerCoordinate;//Temp saving the center
    translate(-m_centerCoordinate.x, -m_centerCoordinate.y);//moving the particles center
    ScalingMatrix S = c; //Creates the new scaling matrix
    m_A = S*m_A;//applies the scaling
    translate(temp.x, temp.y);
}

//END

bool Particle::almostEqual(double a, double b, double eps)
{
	return fabs(a - b) < eps;
}

void Particle::unitTests()
{
    int score = 0;

    cout << "Testing RotationMatrix constructor...";
    double theta = M_PI / 4.0;
    RotationMatrix r(M_PI / 4);
    if (r.getRows() == 2 && r.getCols() == 2 && almostEqual(r(0, 0), cos(theta))
        && almostEqual(r(0, 1), -sin(theta))
        && almostEqual(r(1, 0), sin(theta))
        && almostEqual(r(1, 1), cos(theta)))
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }

    cout << "Testing ScalingMatrix constructor...";
    ScalingMatrix s(1.5);
    if (s.getRows() == 2 && s.getCols() == 2
        && almostEqual(s(0, 0), 1.5)
        && almostEqual(s(0, 1), 0)
        && almostEqual(s(1, 0), 0)
        && almostEqual(s(1, 1), 1.5))
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }

    cout << "Testing TranslationMatrix constructor...";
    TranslationMatrix t(5, -5, 3);
    if (t.getRows() == 2 && t.getCols() == 3
        && almostEqual(t(0, 0), 5)
        && almostEqual(t(1, 0), -5)
        && almostEqual(t(0, 1), 5)
        && almostEqual(t(1, 1), -5)
        && almostEqual(t(0, 2), 5)
        && almostEqual(t(1, 2), -5))
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }

    
    cout << "Testing Particles..." << endl;
    cout << "Testing Particle mapping to Cartesian origin..." << endl;
    if (m_centerCoordinate.x != 0 || m_centerCoordinate.y != 0)
    {
        cout << "Failed.  Expected (0,0).  Received: (" << m_centerCoordinate.x << "," << m_centerCoordinate.y << ")" << endl;
    }
    else
    {
        cout << "Passed.  +1" << endl;
        score++;
    }

    cout << "Applying one rotation of 90 degrees about the origin..." << endl;
    Matrix initialCoords = m_A;
    rotate(M_PI / 2.0);
    bool rotationPassed = true;
    for (int j = 0; j < initialCoords.getCols(); j++)
    {
        if (!almostEqual(m_A(0, j), -initialCoords(1, j)) || !almostEqual(m_A(1, j), initialCoords(0, j)))
        {
            cout << "Failed mapping: ";
            cout << "(" << initialCoords(0, j) << ", " << initialCoords(1, j) << ") ==> (" << m_A(0, j) << ", " << m_A(1, j) << ")" << endl;
            rotationPassed = false;
        }
    }
    if (rotationPassed)
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }

    cout << "Applying a scale of 0.5..." << endl;
    initialCoords = m_A;
    scale(0.5);
    bool scalePassed = true;
    for (int j = 0; j < initialCoords.getCols(); j++)
    {
        if (!almostEqual(m_A(0, j), 0.5 * initialCoords(0,j)) || !almostEqual(m_A(1, j), 0.5 * initialCoords(1, j)))
        {
            cout << "Failed mapping: ";
            cout << "(" << initialCoords(0, j) << ", " << initialCoords(1, j) << ") ==> (" << m_A(0, j) << ", " << m_A(1, j) << ")" << endl;
            scalePassed = false;
        }
    }
    if (scalePassed)
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }

    cout << "Applying a translation of (10, 5)..." << endl;
    initialCoords = m_A;
    translate(10, 5);
    bool translatePassed = true;
    for (int j = 0; j < initialCoords.getCols(); j++)
    {
        if (!almostEqual(m_A(0, j), 10 + initialCoords(0, j)) || !almostEqual(m_A(1, j), 5 + initialCoords(1, j)))
        {
            cout << "Failed mapping: ";
            cout << "(" << initialCoords(0, j) << ", " << initialCoords(1, j) << ") ==> (" << m_A(0, j) << ", " << m_A(1, j) << ")" << endl;
            translatePassed = false;
        }
    }
    if (translatePassed)
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }

    cout << "Score: " << score << " / 7" << endl;
}