#include <iostream>
#include <string>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;

// Helper to map string color to sf::Color
sf::Color getColorFromString(const std::string& color) {
    if (color == "Red") return sf::Color::Red;
    if (color == "Green") return sf::Color::Green;
    if (color == "Blue") return sf::Color::Blue;
    if (color == "Black") return sf::Color::Black;
    if (color == "White") return sf::Color::White;
    if (color == "Yellow") return sf::Color::Yellow;
    if (color == "Cyan") return sf::Color::Cyan;
    if (color == "Magenta") return sf::Color::Magenta;
    return sf::Color(128, 128, 128);
}

class Shape {
protected:
    int x, y;
    string color;

public:
    Shape(string color) {
        this->color = color;
        x = 0;
        y = 0;
    }

    virtual void get_area() const = 0;
    virtual void get_perimeter() const = 0;

    virtual void get_color() const {
        cout << "Color : " << color << endl;
    }

    virtual void get_shape() const = 0;

    virtual void translate(int dx, int dy) {
        x += dx;
        y += dy;
    }

    virtual void get_coordinates() const {
        cout << "Coordinates : (" << x << ", " << y << ")" << endl;
    }

    virtual void draw(sf::RenderWindow& window) const = 0;

    virtual ~Shape() {}
};

class Rectangle : public Shape {
protected:
    int length;
    int breadth;

public:
    Rectangle(int length, int breadth, string color) : Shape(color) {
        this->length = length;
        this->breadth = breadth;
    }

    void get_length() {
        cout << "Length : " << length << endl;
    }

    void get_breadth() {
        cout << "Breadth : " << breadth << endl;
    }

    void get_area() const override {
        cout << "Area : " << length * breadth << endl;
    }

    void get_perimeter() const override {
        cout << "Perimeter : " << 2 * (length + breadth) << endl;
    }

    void get_diagonal() {
        int diag = length * length + breadth * breadth;
        cout << "Diagonal : " << sqrt(float(diag)) << endl;
    }

    void is_square() {
        cout << (check_square() ? "Square hai" : "Square nai hai") << endl;
    }

    void get_shape() const override {
        cout << "Shape : " << 0 << endl;
    }

    void draw(sf::RenderWindow& window) const override {
        sf::RectangleShape rect(sf::Vector2f(length, breadth));
        rect.setPosition(x, y);
        rect.setFillColor(getColorFromString(color));
        window.draw(rect);
    }

private:
    bool check_square() {
        return length == breadth;
    }
};

class Square : public Rectangle {
public:
    Square(int side, string color) : Rectangle(side, side, color) {}

    void get_side() {
        cout << "Side : " << length << endl;
    }

    void get_shape() const override {
        cout << "Shape : " << 1 << endl;
    }

    void draw(sf::RenderWindow& window) const override {
        sf::RectangleShape sq(sf::Vector2f(length, length));
        sq.setPosition(x, y);
        sq.setFillColor(getColorFromString(color));
        window.draw(sq);
    }
};

class Ellipse : public Shape {
protected:
    int a, b;

public:
    Ellipse(int a, int b, string color) : Shape(color) {
        this->a = a;
        this->b = b;
    }

    void get_area() const override {
        cout << "Area : " << 3.141592653589793 * a * b << endl;
    }

    void get_perimeter() const override {
        double h = pow((a - b), 2) / double((a + b) * (a + b));
        double perimeter = 3.141592653589793 * (a + b) * (1 + (3 * h) / (10 + sqrt(4 - 3 * h)));
        cout << "Perimeter : " << perimeter << endl;
    }

    void get_axes() {
        cout << "Semi-major axis : " << a << ", Semi-minor axis : " << b << endl;
    }

    void get_shape() const override {
        cout << "Shape : " << 3 << endl;
    }

    void draw(sf::RenderWindow& window) const override {
        sf::CircleShape ellipse(50);
        ellipse.setScale(a / 50.0, b / 50.0);
        ellipse.setPosition(x, y);
        ellipse.setFillColor(getColorFromString(color));
        window.draw(ellipse);
    }
};

class Circle : public Ellipse {
    int radius;

public:
    Circle(int radius, string color) : Ellipse(radius, radius, color), radius(radius) {}

    void get_area() const override {
        cout << "Area : " << 3.141592653589793 * radius * radius << endl;
    }

    void get_perimeter() const override {
        cout << "Perimeter : " << 2 * 3.141592653589793 * radius << endl;
    }

    void get_shape() const override {
        cout << "Shape : " << 2 << endl;
    }

    void draw(sf::RenderWindow& window) const override {
        sf::CircleShape circ(radius);
        circ.setPosition(x, y);
        circ.setFillColor(getColorFromString(color));
        window.draw(circ);
    }
};

class Canvas {
private:
    vector<Shape*> shapes;

public:
    void addShape(Shape* s) {
        shapes.push_back(s);
    }

    void displayCanvas() {
        sf::RenderWindow window(sf::VideoMode(800, 600), "Canvas");

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear(sf::Color::White);

            for (Shape* s : shapes) {
                s->draw(window);
            }

            window.display();
        }
    }
};

int main() {
    try {
        Canvas canvas;

        Shape* r = new Rectangle(100, 60, "Red");
        r->translate(50, 50);
        canvas.addShape(r);

        Shape* s = new Square(80, "Blue");
        s->translate(200, 70);
        canvas.addShape(s);

        Shape* c = new Circle(50, "Green");
        c->translate(400, 90);
        canvas.addShape(c);

        Shape* e = new Ellipse(60, 40, "Magenta");
        e->translate(600, 120);
        canvas.addShape(e);

        canvas.displayCanvas();
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}
