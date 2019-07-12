* Any time you have a pointer to some derived type, but need a pointer to the base object, c++ automaticallt makes that conversion
* for anything we want to be aopplicable to all derived types, we should add it to the base class
* If we do not add the implementation of a certain function or variable from the base class, then it is automatically Inherited from the base class
    * INHERITANCE
* If we make an array of type shape, but we want to call a specific shape’s implementation of a shape funtion, the compiler does converion for us
    * Will convert the shape pointer to they right derived shape class
* Cannot access derived class specific functions or datamembers that do not exist in the base class
    * Ex, when we make a array of shapes, we cannot access the radius of each item beacuse not every item has a radius
* If a compiler has to make a desicion about which implementaion to use, it default uses the base class implementation
* //Pass items by reference or by pointer because you loose info if you pass by value
* derived classes can have virtual function
* if we forget to declare the implementation of virtual functions in the derived classes, then the class becomes a abstract class
* Trying to delete a derived object from a base pointer is undefined behavior if the deconstructor is not virtual
* If a class is designed as a base class, declare its deconstuctor as virtual and implement it!!
; //end of notes



class Shape
{
  public:
    Shape(double x, double y);
    virtual ~Shape(); //cannot make a destructor pure virtual, results in a link error
    void move(double xnew, double ynew);
    virtual void draw() const = 0;
    virtual ~Shape();
    double x() const;
    double y() const;
    ...
  private:
    double m_x;
    double m_y;
};

class Circle : public Shape
{
  public:
    Circle(double r, double x, double y);
    virtual void draw() const;
    ...
  private:
    double m_r;
};

class Rectangle : public Shape
{
  public:
    Rectangle(double x, double y, double dx, double dy);
    virtual void draw() const;
    virtual double diag() const;
    ...
  private:
    double m_dx;
    double m_dy;
};

Shape::Shape(double x, double y)
 : m_x(x), m_y(y)
{}

void Shape::move(double xnew, double ynew)
{
    m_x = xnew;
    m_y = ynew;
}

Shape::~Shape()
{} //have to declare the desconstructor because the base classes decontructor is virtual
//we declared it so we have to implement it

double Shape::x() const
{
    return m_x;
}

double Shape::y() const
{
    return m_y;
}

Circle::Circle(double r, double x, double y)
 : Shape(x, y), m_r(r)
{
    if (r < 0)
        //... error: radius must be non-negative ...
}

void Circle::draw() const
{
  //... draw a circle of radius m_r centered at (x(), y()) ...
}

Rectangle::Rectangle(double x, double y, double dx, double dy)
 : Shape(x, y), m_dx(dx), m_dy(dy)
{}

void Rectangle::draw() const
{
  // ... draw a line from (x(), y()) to (x()+m_dx, y()) ...
  // ... draw a line from (x()+m_dx, y()) to (x()+m_dx, y()+m_dy) ...
  // ... draw a line from (x()+m_dx, y()+m_dy) to (x(), y()+m_dy) ...
  // ... draw a line from (x(), y()+m_dy) to (x(), y()) ...
}

double Rectangle::diag() const
{
    return std::sqrt(m_dx*m_dx + m_dy*m_dy);
}


class Polygon: public Shape
{
public:
  ...
  ~Polygon(); //Base classes destructor needs to be virtual, otherwise it tries to use Shape's destructor
private:
  ...
  Node* head;
}
