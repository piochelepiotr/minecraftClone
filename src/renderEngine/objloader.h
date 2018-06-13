#ifndef OBJLOADER_H
#define OBJLOADER_H

#include "renderEngine/loader.h"
#include "models/rawModel.h"
#include <string>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <map>
#include <utility>
#include <toolbox/vertex.h>

class OBJLoader
{
public:
    OBJLoader();
    static RawModel *loadObjModel(std::string const& fileName, Loader *loader);
private:
    static std::vector<std::map<std::pair<int,int>,int> > splitEdges(std::vector<Vertex> const& vertexes, int & max_index, int max_ver);
    static void assignIndexes(std::vector<std::map<std::pair<int, int>, int> > &unique_vertexes, int & max_index);
    static void processVertex(std::string const& vertex, std::vector<int> & indices,
                       std::vector<glm::vec2> & textures, std::vector<glm::vec3> & normals,
                       float *texturesArray, float *normalsArray);
};

#endif // OBJLOADER_H
