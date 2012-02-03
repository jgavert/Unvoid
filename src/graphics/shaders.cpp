#include <string>
#include <cstdlib>
#include <sstream>
#include "shaders.h"


shaders::shaders(void)
{
}


shaders::~shaders(void)
{
}

string readShaderFile(string FileName)
{
string ShaderString = "";
ifstream shaderFile;
shaderFile.open(FileName);
    while(!shaderFile.eof())
    {
        string tempholder;
        getline(shaderFile, tempholder);
        ShaderString.append(tempholder);
        ShaderString.append("\n");
    }
shaderFile.close();

return ShaderString;
}

shaders::loadShaders(void)
{

}
