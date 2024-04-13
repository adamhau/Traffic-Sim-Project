/* TRAFFIC LIGHT SIMULATION
   PROGRAMMED AND DESIGNED BY ADAM HAUGEN
*/

#include <simplecpp>

int const MAX_CARS = 3;
char input;
bool flag = true;
int loopVal = 0;

// Update variables to stagger cars
int xPos = 350, yPos = 650;

// Sets Traffic light to Green
void greenLight(Circle &light, int x)
{
    light.setColor(COLOR("Green"));
    if (x == 0)
        light.moveTo(300, 160);
    else
        light.moveTo(900, 760);
}

//Sets traffic light to Red
void redLight(Circle &light, int x)
{
    light.setColor(COLOR("Red"));
    if (x == 0)
        light.moveTo(300, 40);
    else
        light.moveTo(900, 640);
}

//sets traffic light to Yellow
void yellowLight(Circle &light, int x)
{
    light.setColor(COLOR("Yellow"));
    if (x == 0)
        light.moveTo(300, 100);
    else
        light.moveTo(900, 700);
}

main_program
{
    //boolean value for calling yellow light
    bool called = false;

    //Create window
    initCanvas("Traffic Light Sim", 1000, 1000);

    struct Car
    {
        Rectangle body;
    };

    //creates the intersection
    Rectangle ewRoad(500, 500, 1000, 200);
    ewRoad.setColor(COLOR("#8c8c8c"));
    ewRoad.setFill();
    Rectangle nwRoad(500, 500, 200, 1000);
    nwRoad.setColor(COLOR("#8c8c8c"));
    nwRoad.setFill();

    Car carArrayNS[MAX_CARS];
    Car carArrayEW[MAX_CARS];

    // N/S Traffic Light
    Rectangle r1(300, 100, 100, 200);
    r1.setColor(COLOR(255, 204, 0));
    r1.setFill();
    Circle b1(300, 40, 26);
    b1.setColor(COLOR("black"));
    b1.setFill();
    Circle b2(300, 100, 26);
    b2.setColor(COLOR("black"));
    b2.setFill();
    Circle b3(300, 160, 26);
    b3.setColor(COLOR("black"));
    b3.setFill();
    Circle c1(300, 40, 25);
    c1.setColor(COLOR("Red"));
    c1.setFill();

    Text t1(300, 220, "N/S Traffic Light");

    // E/W Traffic Light
    Rectangle r2(900, 700, 100, 200);
    Circle b4(900, 640, 26);
    b4.setColor(COLOR("black"));
    b4.setFill();
    Circle b5(900, 700, 26);
    b5.setColor(COLOR("black"));
    b5.setFill();
    Circle b6(900, 760, 26);
    b6.setColor(COLOR("black"));
    b6.setFill();
    r2.setColor(COLOR(255, 204, 0));
    r2.setFill();
    Circle c2(900, 640, 25);
    c2.setColor(COLOR("Red"));
    c2.setFill();

    Text t2(900, 820, "E/W Traffic Light");

    //initialize and stagger NS cars
    for (int i = 0; i < 3; i++)
    {
        carArrayNS[i].body = Rectangle(500, yPos, 50, 75);
        carArrayNS[i].body.setColor(COLOR("blue"));
        carArrayNS[i].body.setFill();
        carArrayNS[i].body.hide();
        yPos += 150;
    }

    // Initialize and stagger EW cars
    for (int i = 0; i < 3; i++)
    {
        carArrayEW[i].body = Rectangle(xPos, 500, 75, 50);
        carArrayEW[i].body.setColor(COLOR("green"));
        carArrayEW[i].body.setFill();
        carArrayEW[i].body.hide();
        xPos -= 150;
    }

   //main loop that asks user for input and simulates the intersection
    while (flag)
    {
        xPos = 350;
        yPos = 650;
        called = false; //reset yellow light flag

        //reset NS car locations to starting position
        for (int i = 0; i < 3; i++)
        {
            carArrayNS[i].body.moveTo(500, yPos);
            carArrayNS[i].body.hide();
            yPos += 150;
        }

        //reset EW car locations to starting position
        for (int i = 0; i < 3; i++)
        {
            carArrayEW[i].body.moveTo(xPos, 500);
            carArrayEW[i].body.hide();
            xPos -= 150;
        }

        // Ask for traffic density
        cout << "Enter the traffic density: (h = heavy, m = medium, l = light): ";
        cin >> input;

        switch (input)
        {
        //heavy traffic
        case 'h':
            //show all vehicles
            carArrayNS[0].body.show();
            carArrayNS[1].body.show();
            carArrayNS[2].body.show();
            carArrayEW[0].body.show();
            carArrayEW[1].body.show();
            carArrayEW[2].body.show();

            //set light to green
            wait(1);
            greenLight(c1, 0);
            wait(0.5);

            //moves NS Cars, when last car gets across road, change light to yellow.
            while (carArrayNS[2].body.getY() >= -35)
            {
                carArrayNS[0].body.move(0, -15);
                carArrayNS[1].body.move(0, -15);
                carArrayNS[2].body.move(0, -15);
                if (carArrayNS[2].body.getY() <= 300 && !called)
                {
                    yellowLight(c1, 0);
                    called = true;
                }
                wait(0.1);
            }
            //when final car leaves screen, light turns red
            redLight(c1, 0);
            wait(1);
            greenLight(c2, 1);
            called = false;
            wait(0.5);

            //moves EW Cars, when last car gets across road, change light to yellow.
            while (carArrayEW[2].body.getX() <= 1035)
            {
                carArrayEW[0].body.move(15, 0);
                carArrayEW[1].body.move(15, 0);
                carArrayEW[2].body.move(15, 0);
                if (carArrayEW[2].body.getX() >= 700 && !called)
                {
                    yellowLight(c2, 1);
                    called = true;
                }
                wait(0.1);
            }
            redLight(c2, 1);
            wait(1);
            break;
           
        //medium traffic, same functionality as heavy with one less car
        case 'm':
            carArrayNS[0].body.show();
            carArrayNS[1].body.show();
            carArrayEW[0].body.show();
            carArrayEW[1].body.show();
            wait(1);
            greenLight(c1, 0);
            wait(0.5);

            while (carArrayNS[1].body.getY() >= -35)
            {
                carArrayNS[0].body.move(0, -15);
                carArrayNS[1].body.move(0, -15);
                if (carArrayNS[1].body.getY() <= 300 && !called)
                {
                    yellowLight(c1, 0);
                    called = true;
                }
                wait(0.1);
            }
            redLight(c1, 0);
            wait(1);
            greenLight(c2, 1);
            called = false;
            wait(0.5);

            while (carArrayEW[1].body.getX() <= 1035)
            {
                carArrayEW[0].body.move(15, 0);
                carArrayEW[1].body.move(15, 0);
                if (carArrayEW[1].body.getX() >= 700 && !called)
                {
                    yellowLight(c2, 1);
                    called = true;
                }
                wait(0.1);
            }
            redLight(c2, 1);
            wait(1);
            break;
           
        //light traffic, same functionality as medium with one less car
        case 'l':
            carArrayNS[0].body.show();
            carArrayEW[0].body.show();
            wait(1);
            greenLight(c1, 0);
            wait(0.5);

            while (carArrayNS[0].body.getY() >= -35)
            {
                carArrayNS[0].body.move(0, -15);
                if (carArrayNS[0].body.getY() <= 300 && !called)
                {
                    yellowLight(c1, 0);
                    called = true;
                }
                wait(0.1);
            }
            redLight(c1, 0);
            wait(1);
            greenLight(c2, 1);
            called = false;
            wait(0.5);

            while (carArrayEW[0].body.getX() <= 1035)
            {
                carArrayEW[0].body.move(15, 0);
                if (carArrayEW[0].body.getX() >= 700 && !called)
                {
                    yellowLight(c2, 1);
                    called = true;
                }
                wait(0.1);
            }
            redLight(c2, 1);
            wait(1);
            break;

        case 'x':
            cout << "Exiting program" << endl;
            flag = false;
            break;
        default:
            cout << "Invalid input." << endl;
            flag = false;
            break;
        }
    }
}
