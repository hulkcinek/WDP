#include <iostream>
#include <vector>
#include <cmath>

class Vector {
private:
    double dx;
    double dy;
public:
    Vector(double dx, double dy) : dx(dx), dy(dy) {}

    int magnitude() const {
        return static_cast<int>(std::sqrt(dx * dx + dy * dy));
    }

    Vector multiply(int value) const {
        return Vector(dx * value, dy * value);
    }

    Vector divide(int value) const {
        return Vector(dx / value, dy / value);
    }

    Vector normalize() const {
        int mag = magnitude();
        return Vector(dx / mag, dy / mag);
    }

    Vector rotate_right() const {
        return Vector(dy, -dx);
    }

    Vector rotate_left() const {
        return Vector(-dy, dx);
    }

    Vector change_length_by(int value) const {
        int mag = magnitude();
        return this->
            divide(mag)
            .multiply(mag + value);
    }

    Vector rotate_45_left_and_standardize() const {
        Vector normalized = this->normalize();
        double x = normalized.dx;
        double y = normalized.dy;
        return Vector(x - y, x + y);
    }

    int getDx() const {
        return static_cast<int>(dx);
    }

    int getDy() const {
        return static_cast<int>(dy);
    }
 };

class Point {
private:
    int x;
    int y;
public:
    Point(int x, int y) : x(x), y(y) {}

    Point addVector(Vector vector) {
        return Point(x + vector.getDx(), y + vector.getDy());
    }

    std::string to_string() const {
        return std::to_string(x) + " " + std::to_string(y);
    }
};

std::vector<Point> points;

Vector generate_outer_side(int fragment_count) {
    Vector current_vector = Vector(2, 0);
    Point current_point = Point(0, 0);
    points.push_back(current_point);

    current_point = current_point.addVector(current_vector);
    points.push_back(current_point);

    for (int i = 1; i < fragment_count; i++) {
        if (i == fragment_count-1) {
            current_vector = current_vector.rotate_right().change_length_by(-1);
        } else {
            current_vector = current_vector.rotate_right().change_length_by(1);
        }
        current_point = current_point.addVector(current_vector);
        points.push_back(current_point);
    }
    return current_vector.rotate_right().normalize();
}

void generate_inner_side(Vector ending_direction) {
    std::vector<Point> inner_points;

    Point starting_point = points.back().addVector(ending_direction);
    inner_points.push_back(starting_point);

    Vector pointingToMiddle = ending_direction.rotate_45_left_and_standardize();
    for (int i = points.size() - 2; i > 0; i--) {
        Point outer_point = points.at(i);
        Point inner_point = outer_point.addVector(pointingToMiddle);
        pointingToMiddle = pointingToMiddle.rotate_left();
        inner_points.push_back(inner_point);
    }
    inner_points.push_back(Point(0, -1));

    points.insert(points.end(), inner_points.begin(), inner_points.end());
}

void print_points() {
    for (int i = 0; i < points.size(); i++) {
        std::cout << points[i].to_string() << " ";
    }
}

int main() {
    int fragmentCount;
    std::cin >> fragmentCount;

    Vector endingDirection = generate_outer_side(fragmentCount);
    generate_inner_side(endingDirection);

    print_points();
    return 0;
}
