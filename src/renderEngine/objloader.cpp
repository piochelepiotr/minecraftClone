#include "objloader.h"
#include <fstream>
#include <iostream>
#include <boost/algorithm/string.hpp>

using namespace std;

OBJLoader::OBJLoader()
{

}


vector<map<pair<int,int>,int>> OBJLoader::splitEdges(const std::vector<Vertex> &vertexes, int & max_index, int max_ver)
{
    vector<map<pair<int,int>, int>> unique_vertexes;
    for(int i = 0; i < max_ver + 1; i++)
    {
        map<pair<int, int>, int> v;
        unique_vertexes.push_back(v);
    }
    for(auto & v : vertexes)
    {
        unique_vertexes[v.v()][make_pair(v.vt(), v.vn())] = 1;
    }
    assignIndexes(unique_vertexes, max_index);
    return unique_vertexes;
}

void OBJLoader::assignIndexes(std::vector<std::map<std::pair<int, int>, int> > &unique_vertexes, int & max_index)
{
    int index = 0;
    for(auto & vertexes : unique_vertexes)
    {
        for(auto & p : vertexes)
        {
            p.second = index;
            index++;
        }
    }
    max_index = index;
}

RawModel * OBJLoader::loadObjModel(string const& fileName, Loader *loader)
{
    ifstream file(fileName.c_str());
    if(!file)
    {
        cout << "Error : file " << fileName << " not found" << endl;
        return 0;
    }
    string line;
    vector<string> splited;
    vector<glm::vec3> vertices;
    vector<glm::vec2> textures;
    vector<glm::vec3> normals;

    float *verticesArray;
    float *texturesArray;
    float *normalsArray;
    int *indicesArray;

    while(getline(file, line))
    {
        boost::split(splited, line, [](char c) { return c == ' '; });
        if(splited.size() == 0) continue;
        if(splited[0] == "v")
        {
            vertices.push_back(glm::vec3(strtof(splited[1].c_str(), 0), strtof(splited[2].c_str(), 0), strtof(splited[3].c_str(), 0)));
        }
        else if(splited[0] == "vn")
        {
            normals.push_back(glm::vec3(strtof(splited[1].c_str(), 0), strtof(splited[2].c_str(), 0), strtof(splited[3].c_str(), 0)));
        }
        else if(splited[0] == "vt")
        {
            textures.push_back(glm::vec2(strtof(splited[1].c_str(), 0), strtof(splited[2].c_str(), 0)));

        }
        else if(splited[0] == "f")
        {
            break;
        }
    }
    vector<Vertex> vertexes;
    int max_ver = 0;
    while(true)
    {
        boost::split(splited, line, [](char c) { return c == ' '; });
        if(splited[0] != "f")
        {
            break;
        }

        vertexes.push_back(Vertex(splited[1]));
        if(vertexes.back().v() > max_ver) max_ver = vertexes.back().v();
        vertexes.push_back(Vertex(splited[2]));
        if(vertexes.back().v() > max_ver) max_ver = vertexes.back().v();
        vertexes.push_back(Vertex(splited[3]));
        if(vertexes.back().v() > max_ver) max_ver = vertexes.back().v();
        if(!getline(file, line))
        {
            break;
        }
    }
    file.close();
    int max_index = 0;
    vector<map<pair<int,int>,int>> unique_vertexes = splitEdges(vertexes, max_index, max_ver);
    int size_indexes = vertexes.size();
    int size = max_index;
    verticesArray = new float[max_index*3];
    texturesArray = new float[max_index*2];
    normalsArray = new float[max_index*3];
    indicesArray = new int[size_indexes];
    int i = 0;
    for(auto & v : vertexes)
    {
        indicesArray[i] = unique_vertexes[v.v()][make_pair(v.vt(), v.vn())];
        i++;
    }
    for(uint i = 0; i < unique_vertexes.size(); i++)
    {
        for(auto & p : unique_vertexes[i])
        {
            int ind = p.second;
            int v = i, vt = p.first.first, vn = p.first.second;
            verticesArray[3*ind]   = vertices[v].x;
            verticesArray[3*ind+1] = vertices[v].y;
            verticesArray[3*ind+2] = vertices[v].z;
            texturesArray[2*ind]   = textures[vt].x;
            texturesArray[2*ind+1] = 1 - textures[vt].y;
            normalsArray[3*ind]    = normals[vn].x;
            normalsArray[3*ind+1]  = normals[vn].y;
            normalsArray[3*ind+2]  = normals[vn].z;
        }
    }
    RawModel *model = loader->loadToVao(verticesArray, size*3, texturesArray, size*2,
                                       indicesArray, size_indexes, normalsArray, size*3);
    return model;
}

void OBJLoader::processVertex(std::string const& vertex, std::vector<int> & indices,
                   std::vector<glm::vec2> & textures, std::vector<glm::vec3> & normals,
                   float *texturesArray, float *normalsArray)
{
    vector<string> splited;
    boost::split(splited, vertex, [](char c) { return c == '/'; });
    int indexVertex = stoi(splited[0]) - 1;
    glm::vec2 text = textures[stoi(splited[1])-1];
    glm::vec3 normal = normals[stoi(splited[2])-1];
    texturesArray[2*indexVertex] = text.x;
    texturesArray[2*indexVertex+1] = 1 - text.y;
    normalsArray[3*indexVertex] = normal.x;
    normalsArray[3*indexVertex+1] = normal.y;
    normalsArray[3*indexVertex+2] = normal.z;
    indices.push_back(indexVertex);
}
