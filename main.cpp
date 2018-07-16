#include <SFML/Graphics.hpp>
#include <math.h>

sf::Image DrawLine(sf::Vector2<float> p0, sf::Vector2<float> p1) {
	sf::Image img;
	img.create(800, 600, sf::Color::Magenta);

	const bool steep = (fabs(p1.y - p0.y) > fabs(p1.x - p0.x));
	
	if (!steep) {
		std::swap(p0.x, p0.y);
		std::swap(p1.x, p1.y);
	}

	if (p0.x > p0.y)
		std::swap(p0, p1);

	const float dx = p1.x - p0.x;
	const float dy = fabs(p1.y - p0.y);

	float error = dx / 2.0f;
	const int ystep = (p0.y < p1.y) ? 1 : -1;
	int y = (int)p0.y;

	const int xMax = (int)p1.x;
	
	for(int x = (int)p0.x; x < xMax; x++){
		if(!steep) {
			img.setPixel(y, x, sf::Color::Red);
		}
		else {
			img.setPixel(x, y, sf::Color::Cyan);
		}
		
		error -= dy;
		if(error < 0) {
			y += ystep;
			error += dx; 
		}
	}
	return img;
}

int main()
{
	 // create the window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Bresenham Line Drawing");
	sf::Texture texture;
	sf::Image image; 
	float p0_x = 20;
	float p0_y = 30;
	float p1_x = 400;
	float p1_y = 500;

	sf::Vector2<float> v0(p0_x, p0_y);
	sf::Vector2<float> v1(p1_x, p1_y);

	image = DrawLine(v0, v1); 	

	texture.loadFromImage(image, sf::IntRect());

	// run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);
		
		// update sprite before drawing	
		sf::Sprite sprite(texture);

    	// draw everything here...
        window.draw(sprite);

        // end the current frame
        window.display();
    }

    return 0;
}


