// This is a chopped Pong example from SFML examples

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <filesystem>

#include <vector>
#include <iostream>

using namespace std;
namespace fs = std::filesystem;



void returnHueValue(vector<double> &rgb, float Hue) {
    double hue;
    double sat;
    double maxVal;
    double minVal;

    maxVal = *max_element(rgb.begin(), rgb.end());
    minVal = *min_element(rgb.begin(), rgb.end());

    double difference = maxVal - minVal;



    double red, green, blue;
    red = rgb.at(0);
    green = rgb.at(1);
    blue = rgb.at(2);

    if (difference == 0) {
        hue = 0;
    }
    else if (red == maxVal) {
        hue = fmod(((60 * ((green - blue) / difference)) + 360), 360.0);
    }
    else if (green = maxVal) {
        hue = fmod(((60 * ((blue - red) / difference)) + 120), 360.0);
    }
    else if (blue = maxVal) {
        hue = fmod(((60 * ((red - green) / difference)) + 240), 360.0);
    }

    Hue = (hue);
        
}

void sort() {


}


int main()
{
    std::srand(static_cast<unsigned int>(std::time(NULL)));

    // example folder to load images
    constexpr char* image_folder = "../unsorted"; //"C:/Users/Gregor/Desktop/CaPS_cw1/test_images";
    std::vector<std::string> imageFilenames;    
    vector<pair<float, string>> image;
    //load images and save file names
    for (auto& p : fs::directory_iterator(image_folder)) {
        imageFilenames.push_back(p.path().u8string());
        //save image as pair with meadian hue
        image.push_back(pair(1000.0f, p.path().u8string()));
    }   

    // Define some constants
    const float pi = 3.14159f;
    const int gameWidth = 800;
    const int gameHeight = 600;

    int imageIndex = 0;

    // Create the window of the application
    sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight, 32), "Image Fever",
                            sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    // Load an image to begin with
    sf::Texture texture;
    if (!texture.loadFromFile(imageFilenames[imageIndex]))
        return EXIT_FAILURE;
    sf::Sprite sprite (texture);
    // Center sprite so that the sprite is in the middle of the window
    sprite.setScale(sf::Vector2f(1.0f,1.0f));    
    sprite.setPosition(sf::Vector2f(0, (gameHeight / 2) - (sprite.getGlobalBounds().height / 2)));
    

    sf::Clock clock;
    while (window.isOpen())
    {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Window closed or escape key pressed: exit
            if ((event.type == sf::Event::Closed) ||
               ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
            {
                window.close();
                break;
            }
            
            // Window size changed, adjust view appropriately
            if (event.type == sf::Event::Resized)
            {
                sf::View view;
                view.setSize(gameWidth, gameHeight);
                view.setCenter(gameWidth/2.f, gameHeight/2.f);
                window.setView(view);
            }

            // Arrow key handling!
            if (event.type == sf::Event::KeyPressed)
            {
                // adjust the image index
                if (event.key.code == sf::Keyboard::Key::Left)
                    imageIndex = (imageIndex + imageFilenames.size() - 1) % imageFilenames.size();
                else if (event.key.code == sf::Keyboard::Key::Right)
                    imageIndex = (imageIndex + 1) % imageFilenames.size();
                // ... and load the appropriate texture, and put it in the sprite
                if (texture.loadFromFile(imageFilenames[imageIndex]))
                {
                    sprite = sf::Sprite(texture);
                    sprite.setScale(sf::Vector2f(1.0f, 1.0f));
                    sprite.setPosition(sf::Vector2f(0, (gameHeight / 2) - (sprite.getGlobalBounds().height / 2)));
                }
            }

            // get rgb values from image
            double red, green, blue;
            // go through the image to get rgb for each pixel in it
            // for every image in the file
            for (int p = 0; p < imageFilenames.size(); p++) {
                sf::Texture imageTex;
                imageTex.loadFromFile(image[p].second);
                int px = imageTex.getSize().x;
                int py = imageTex.getSize().y;
                int imageSize = px * py;
                    //for every pixel in the image
                    for (int i = 0; i < px; i++) {
                        for (int j = 0; i < py; j++) {
                            // calculate the hue of the pixel
                            
                            returnHueValue(imageTex)

                        }
                        //add all hue values up and divide by the number of pixels in image to get median hue of image
                    }
                // sort the images by hue value (cold to hot)
                /* if image hue is less than current image*/
            }
            
           
            
            //calculates hue value for a pixel
            
            cin >> red >> green >> blue;
            vector<double> rgb;
            rgb.push_back(red / 255.0);
            rgb.push_back(green / 255.0);
            rgb.push_back(blue / 255.0);
            double hsv[3];

            cout << "The RGB Values are " << endl;
            for (int i = 0; i < rgb.size(); i++)
                cout << rgb.at(i) * 255.0 << ' ';
            cout << endl;
            returnHSVvalues(rgb, hsv);
            cout << "The HSV Values are " << endl;
            for (int i = 0; i < 3; i++)
                cout << hsv[i] << " ";



        }

        // Clear the window
        window.clear(sf::Color(50, 200, 50));
        // draw the sprite
        window.draw(sprite);
        // Display things on screen
        window.display();
    }

    return EXIT_SUCCESS;
}
