#include <SFML/Graphics.hpp>
#include <random>
#include <bits/stdc++.h>
using namespace std;
using namespace sf;

string IntegerNotation(int number){
    int ciphers = to_string(number).size() - 1;
    string str = to_string(number);
    str = str[0];
    str += ".";
    str += to_string(number)[1];
    str += " x 10^";
    str += to_string(ciphers);
    return str;
}

int main()
{
    random_device rd;
    default_random_engine generator(rd()); // rd() provides a random seed
    uniform_real_distribution<double> distribution(-1,1);
    
    ContextSettings settings;
    settings.antialiasingLevel = 8;
    RenderWindow window(VideoMode(500, 500), "PI", Style::Default, settings);
    
    Font font;
    if (!font.loadFromFile("arial.ttf"))
        cout<<"Error"<<endl;
       
    RectangleShape rectangle(Vector2f(400,400));
    rectangle.setPosition(50,50);
    rectangle.setOutlineThickness(1);
    rectangle.setOutlineColor(Color::Black);
    
    CircleShape circle(200);
    circle.setPointCount(50);
    circle.setPosition(50,50);
    circle.setOutlineThickness(1);
    circle.setOutlineColor(Color::Black);
    
    RectangleShape background(Vector2f(500, 25));
    background.setPosition(0,25/2);

    Text text;
    text.setFont(font);
    text.setFillColor(Color::Black);
    text.setCharacterSize(20);

    srand(time(NULL));
    long double in = 0, tot = 0, pi;
    double r1, r2, x, y;

    string pistr;
    int gap;

    bool condDraw = true;
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
            if (event.type == Event::Closed)
                window.close();

            VertexArray points;
            gap = (tot > pow(10,6))? 100000 : 10;
            while(gap--){

                r1 = distribution(generator);
                r2 = distribution(generator);
                x = 250 + r1*200;
                y = 250 + r2*200;

                Color color;
                tot += 1;
                
                if(sqrt(r1*r1 + r2*r2) < 1)
                    color = Color::Green, in += 1;
                else
                    color = Color::Red;
                
                Vertex point(Vector2f(x,y), color);

                points.append(point);
            }

            pi = 4*(in/tot);
            pistr = to_string(pi);


            text.setString("N:"+IntegerNotation((int)tot)+" PI: "+pistr);
            text.setPosition(250 - text.getLocalBounds().width/2, 25/2);
            


            if(condDraw == true){
                window.clear(Color::White);
                window.draw(rectangle);
                window.draw(circle);
                condDraw = false;
            }else{
                window.draw(points);
                window.draw(background);
                window.draw(text);
            }
                window.display();
    }   

    cout<<"Results of estimation.\n\nN:"<<IntegerNotation((int)tot)<<"\nPI:"<<pistr<<endl;
    return 0;
}

