#include "Graphics/Mesh.h"

#include <vector>
#include <cmath>
#include <stdexcept>



struct SphereMesh
{
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
};

inline SphereMesh GenerateSphere(float radius = 1.0f, unsigned int rings = 8, unsigned int sectors = 8)
{
    if (rings == 0 || sectors == 0)
        throw std::invalid_argument("GenerateSphere(): rings and sectors must be greater than zero");

    SphereMesh mesh;

    constexpr float PI = 3.14159265358979323846f;

    mesh.vertices.reserve((rings + 1) * (sectors + 1));

    for (unsigned int ring = 0; ring <= rings; ++ring)
    {
        // 0 -> PI
        const float phi = PI * static_cast<float>(ring) / rings;

        const float y = std::cos(phi);
        const float sinPhi = std::sin(phi);

        for (unsigned int sector = 0; sector <= sectors; ++sector)
        {
            // 0 -> 2PI
            const float theta = 2.0f * PI * static_cast<float>(sector) / sectors;

            const float x = sinPhi * std::cos(theta);
            const float z = sinPhi * std::sin(theta);

            glm::vec3 normal(x, y, z);
            glm::vec3 position = normal * radius;

            glm::vec2 uv(static_cast<float>(sector) / sectors, static_cast<float>(ring) / rings);

            mesh.vertices.push_back(
                Vertex{
                    position,
                    glm::vec3(1.0f, 1.0f, 1.0f), // color
                    normal,
                    uv
                }
            );
        }
    }

    // Generate triangles
    for (unsigned int ring = 0; ring < rings; ++ring)
    {
        for (unsigned int sector = 0; sector < sectors; ++sector)
        {
            const unsigned int current = ring * (sectors + 1) + sector;

            const unsigned int next = current + sectors + 1;

            mesh.indices.push_back(current);
            mesh.indices.push_back(next);
            mesh.indices.push_back(current + 1);

            mesh.indices.push_back(current + 1);
            mesh.indices.push_back(next);
            mesh.indices.push_back(next + 1);
        }
    }

    return mesh;
}