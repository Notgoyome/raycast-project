//
// Created by Guillaume Tran on 08/05/2024.
//

#include "Object.hpp"
#include <utils/getClosest.h>

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
    std::shared_ptr<ray::IMaterial> currentMaterial = _material;
    // get max scale between x, y and z
    if (!file.is_open())
        throw std::runtime_error("Can't open file " + objPath + "\n");
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string type;
        ss >> type;
        if (type == "mtllib") {
            ss >> type;
            _materials = loadObjMaterials("config_files/" + type);
        }
        if (type == "usemtl") {
            ss >> type;
            if (_materials.find(type) != _materials.end())
                currentMaterial = _materials[type];
        }
        if (type == "v") {
            _points.push_back(PointMatrix(createPoint(ss), _transformMatrix));
        }
        if (type == "f") {
            std::string temp;
            std::vector<int> indices;
            while (ss >> temp) {
                indices.push_back(std::stoi(temp) - 1);
                ss.ignore(1);
            }
            for (int i = 0; i < static_cast<int>(indices.size()) - 2; i++) {
                std::shared_ptr<ObjTriangle> triangle = std::make_shared<ObjTriangle>();
                triangle->setPoint(_points[indices[0]], _points[indices[i + 1]], _points[indices[i + 2]]);
                triangle->initNormale();
                triangle->setMaterial(currentMaterial);
                _triangles.push_back(triangle);
            }
        }
        if (type == "vn") {
            Math::Vector3D normal;
            ss >> normal.X >> normal.Y >> normal.Z;
            _normals.push_back(normal);
        }
    }
}

Maybe<PosShapePair> ray::Object::hit(const ray::Ray &ray) const
{
    bool found = false;
    int index = 0;
    int current = 0;
    Math::Point3D hit;

    for (auto &triangle : _triangles) {
        auto maybeHit = triangle->hit(ray);
        if (maybeHit.has_value()) {
            if (found == false) {
                hit = maybeHit.value().first;
                current = index;
                found = true;
            } else {
                Math::Point3D closest = getClosest({hit, maybeHit.value().first}, ray.origin);

                if (closest == maybeHit.value().first) {
                    hit = maybeHit.value().first;
                    current = index;
                }
            }
        }
        index++;
    }
    if (found)
        return Maybe<std::pair<Math::Point3D,std::shared_ptr<ray::IShape>>>{
            std::make_pair(hit, _triangles[current])};
    return Maybe<std::pair<Math::Point3D, std::shared_ptr<ray::IShape>>>{};
}

Math::Vector3D ray::Object::getNormale(const Math::Point3D& point, const ray::Ray& camRay) const
{
    return _triangles[0]->getNormale(point, camRay);
}

ray::Ray ray::Object::getRefraction(
    __attribute__((unused))const std::shared_ptr<ray::IScene>& scene,
    Math::Point3D pos, Math::Vector3D dir) const
{
    return {pos + dir * 0.0001, dir};
}

extern "C" ray::INode *create(std::map<std::string, std::string> &attributes)
{
    if (attributes.find("path") == attributes.end())
        throw std::runtime_error("Object node must have a path attribute\n");
    ray::Object *object = new ray::Object();
    object->setPath(attributes.at("path"));
    return object;
}
