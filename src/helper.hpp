#include <vector>
#include "Vector.hpp"

bool isInsideFigure(std::vector<Vector>& vertices, Vector& testVertex);

std::vector<Vector> getAvailablePositions(Vector& vertex, int64_t sqLength, uint64_t epsilon);

bool isPositionAllowed(Vector& vertex, Vector& testVertex, int64_t sqEdgeLength, uint64_t epsilon);

std::vector<Vector> getPositions(std::vector<double>& originalDistances, std::vector<Vector>& connectedVertices, uint64_t epsilon);
