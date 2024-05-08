//
// Created by Guillaume Tran on 08/05/2024.
//

#include "Object.hpp"


void ray::Object::initValues()
{
    AShape::initValues();
    applyMatrix();
    parse(_objPath);
}

Math::Point3D createPoint(std::istringstream &ss)
{
    Math::Point3D point;
    ss >> point.X >> point.Y >> point.Z;
    return point;
}

Math::Point3D PointMatrix(const Math::Point3D &point, const Math::Matrix<4,4> &matrix)
{
    Math::Matrix<4, 1> pointMatrix;
    pointMatrix(0, 0) = point.X;
    pointMatrix(1, 0) = point.Y;
    pointMatrix(2, 0) = point.Z;
    pointMatrix(3, 0) = 1;
    Math::Matrix<4, 1> result = matrix * pointMatrix;
    return Math::Point3D(result(0, 0), result(1, 0), result(2, 0));
}

void ray::Object::parse(std::string objPath)
{
    std::ifstream file(objPath);
    std::string line;
    // get max scale between x, y and z
    if (!file.is_open())
        throw std::runtime_error("Can't open file " + objPath + "\n");
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string type;
        ss >> type;
        if (type == "v") {
            _points.push_back(createPoint(ss));
            _points.back() = PointMatrix(_points.back(), _transformMatrix);
        }
        if (type == "f") {
            int p1, p2, p3;
            ss >> p1 >> p2 >> p3;
            Triangle triangle;
            std::cout << "start" << std::endl;
            std::cout << "p1: " << p1 << " p2: " << p2 << " p3: " << p3 << std::endl;
            triangle.setPoint(_points[p1 - 1], _points[p2 - 1], _points[p3 - 1]);
            std::cout << _points[p1 - 1].X << " " << _points[p1 - 1].Y << " " << _points[p1 - 1].Z << std::endl;
            std::cout << _points[p2 - 1].X << " " << _points[p2 - 1].Y << " " << _points[p2 - 1].Z << std::endl;
            std::cout << _points[p3 - 1].X << " " << _points[p3 - 1].Y << " " << _points[p3 - 1].Z << std::endl;
            std::cout << "end" << std::endl;

            _triangles.push_back(triangle);
        }
        if (type == "vn") {
            Math::Vector3D normal;
            ss >> normal.X >> normal.Y >> normal.Z;
            _normals.push_back(normal);
        }
    }
//    for (auto &triangle : _triangles) {
//        std::cout << "Triangle:" << std::endl;
//        std::cout << triangle.getp1().X << " " << triangle.getp1().Y << " " << triangle.getp1().Z << std::endl;
//        std::cout << triangle.getp2().X << " " << triangle.getp2().Y << " " << triangle.getp2().Z << std::endl;
//        std::cout << triangle.getp3().X << " " << triangle.getp3().Y << " " << triangle.getp3().Z << std::endl;
//    }
   // exit(0);
}

Maybe<Math::Point3D> ray::Object::hit(const ray::Ray &ray) const
{
    Maybe<Math::Point3D> hit;
    int i = 0;

    for (auto &triangle : _triangles) {
        auto maybeHit = triangle.hit(ray);
        if (maybeHit.has_value()) {
            hit = maybeHit;
            _currentTriangleIndex = i;
        }
        i++;
    }
    return hit;
}

Math::Vector3D ray::Object::getNormale(const Math::Point3D& point, const ray::Ray& camRay) const
{
//    if ((int)_normals.size() > _currentTriangleIndex )
//        return _normals[_currentTriangleIndex];
    return _triangles[_currentTriangleIndex].getNormale(point, camRay);
    (void) point;
    (void) camRay;
    return Math::Vector3D();
}

extern "C" ray::INode *create(std::map<std::string, std::string> &attributes)
{
    if (attributes.find("path") == attributes.end())
        throw std::runtime_error("Object node must have a path attribute\n");
    ray::Object *object = new ray::Object();
    object->setPath(attributes.at("path"));
    return object;
}