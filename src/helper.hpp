#include <vector>
#include "Vector.hpp"

bool isInsideFigure(std::vector<Vector>& vertices, Vector& testVertex);

std::vector<Vector> getAvailablePositions(Vector& vertex, double sqLength, uint64_t epsilon);

bool isPositionAllowed(Vector& vertex, Vector& testVertex, double sqEdgeLength, uint64_t epsilon);

std::vector<Vector> getPositions(std::vector<double>& originalDistances, std::vector<Vector>& connectedVertices, uint16_t epsilon, std::vector<Vector>& holePoints);