#include<iostream>
#include<string>
#include<math.h>

using namespace std;

class Shape{
protected : 
    int x, y;
    string color;
public :
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
    virtual ~Shape(){}
};

class Rectangle : public Shape{
protected :
    int length;
    int breadth;
    // string color;
public :
    Rectangle(int length, int breadth, string color) : Shape(color) {
        this->length = length;
        this->breadth = breadth;
        // this->color = color;
    }
    void get_length() {
        cout << "Length : " << length << endl;
    }
    void get_breadth() {
        cout << "Breadth : " << breadth << endl;
    }
    // void get_color() {
    //     cout << "Color : " << color << endl; 
    // }
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
        cout << (check_square() ? ("Square hai") : ("Square nai hai")) << endl;
    }
    void get_shape() const override {
        cout << "Shape : " << 0 << endl;
    }
private:
    bool check_square() {
        return length == breadth;
    }
};

class Square : public Rectangle {
public :
    Square(int side, string color) : Rectangle(side, side, color) {};
    void get_side() {
        cout << "Side : " << length << endl;
    }
    void get_shape() const override {
        cout << "Shape : " << 1 << endl;
    }
};

// class Circle : public Shape {
// protected :
//     int radius;
// public :
//     Circle(int radius, string color) : Shape(color) {
//         this->radius = radius;
//     }
//     void get_area() const override {
//         cout << "Area : " << 3.141592653589793 * radius * radius << endl;
//     }
//     void get_perimeter() const override {
//         cout << "Perimeter : " << 2 * 3.141592653589793 * radius << endl;
//     }
// };

class Ellipse : public Shape {
protected : 
    int a;
    int b;
public : 
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
        cout << "Semi-major axis : " << a << ", " << "Semi-minor axis : " << b << endl;
    }
    void get_shape() const override {
        cout << "Shape : " << 3 << endl;
    }
};

class Circle : public Ellipse {
protected :
    int radius;
public :
    Circle(int radius, string color) : Ellipse(radius, radius, color) {
    }
    void get_area() const override {
        cout << "Area : " << 3.141592653589793 * radius * radius << endl;
    }
    void get_perimeter() const override {
        cout << "Perimeter : " << 2 * 3.141592653589793 * radius << endl;
    }
    void get_shape() const override {
        cout << "Shape : " << 2 << endl;
    }
};


int main() {
    try {
        // Rectangle r1(4, 5, "red");
        Shape* s1 = new Rectangle(4, 5, "Red");
        s1->get_area();
        s1->get_color();
        s1->get_shape();
        s1->get_coordinates();
        s1->translate(5, 7);
        s1->get_coordinates();
        Rectangle* r1 = dynamic_cast<Rectangle*>(s1);
        r1->get_length();
        r1->get_breadth();
        r1->get_perimeter();
        r1->get_area();
        r1->get_color();
        r1->get_diagonal();
        r1->is_square();
        r1->get_shape();
        Shape* s2 = new Rectangle(10, 10, "Black");
        s2->get_shape();
        Rectangle* r2 = dynamic_cast<Rectangle*>(s2);
        r2->is_square(); 
        Shape* s3 = new Square(5, "Blue");
        s3->get_shape();
        s3->translate(-3, 4);
        s3->get_coordinates();
        Square* sq = dynamic_cast<Square*>(s3);
        sq->get_side();
        sq->get_perimeter();
        sq->get_area();
        sq->get_diagonal();
        sq->get_color();
        Shape* s4 = new Circle(3, "Green");
        s4->get_shape();
        Circle* c1 = dynamic_cast<Circle*>(s4);
        c1->get_color();
        c1->get_perimeter();
        c1->get_area();
        Shape* s5 = new Ellipse(4, 5, "Burgundy");
        s5->get_shape();
        s5->translate(2, 2);
        s5->translate(5, 4);
        s5->get_coordinates();
        Ellipse* e1 = dynamic_cast<Ellipse*>(s5);
        e1->get_color();
        e1->get_perimeter();
        e1->get_area();
        e1->get_axes();
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
    }
    return 0;
}