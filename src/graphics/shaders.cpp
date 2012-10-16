#include "shaders.h"


Shaders::Shaders(void)
{
}


Shaders::~Shaders(void)
{
}

std::string Shaders::readShaderFile(std::string FileName)
{
  std::string ShaderString = "";
  std::ifstream shaderFile;
  shaderFile.open(FileName);
  while(!shaderFile.eof())
  {
    std::string tempholder;
    getline(shaderFile, tempholder);
    ShaderString += tempholder + "\n";
  }
  shaderFile.close();
  auto parsed = parseShaderForComments(ShaderString);
  return parsed;
}

// just so that shader files support easy commenting with '/*' and '*/'
std::string Shaders::parseShaderForComments(std::string unparsed)
{
  bool start = false;
  std::string parsed;
  for (unsigned i = 0; i<unparsed.length(); i++){
    if (unparsed[i] == '/')
      if (unparsed[i+1] == '*') {
        start = true;
        i+=1;
        continue;
      }


    if (unparsed[i] == '*')
      if (unparsed[i+1] == '/'){
        start = false;
        i+=1;
        continue;
      }
    if (start)
      continue;
    parsed += unparsed[i];
  }
  return parsed;

}

void Shaders::loadShaders(void)
{
  //debug for windows file management
  /*std::ofstream myfile("example.txt");
  if (myfile.is_open())
  {
    myfile << "This is a line." << std::endl;
    myfile << "This is another line." << std::endl;
    myfile.close();
  }*/
  //remove after clear
  //local directory is the one where you run the main from
  vertex = readShaderFile("shaders/simple.vertex");
  fragment = readShaderFile("shaders/simple.fragment");
}
GLint Shaders::createShaders(void)
{
  const GLchar *VertexShader = vertex.c_str();
  const GLchar *FragmentShader = fragment.c_str();
  GLenum ErrorCheckValue = glGetError();

  VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(VertexShaderId, 1, &VertexShader, NULL);
  glCompileShader(VertexShaderId);

 //did this fail
  int status;
  glGetShaderiv(VertexShaderId,  GL_COMPILE_STATUS, &status);
  int asdfg = 0;
  glGetShaderiv(VertexShaderId, GL_INFO_LOG_LENGTH, &asdfg);
  char* infoLog = (char*)malloc(sizeof(char)*1000);
  glGetShaderInfoLog(VertexShaderId, asdfg, &asdfg, infoLog);
    /*glGetShader(shaderID, GL_INFO_LOG_LENGTH, length); // length of log, needed for reading it back
      glGetShaderInfoLog(shaderID, length, infoLog); // read back info log*/
  FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(FragmentShaderId, 1, &FragmentShader, NULL);
  glCompileShader(FragmentShaderId);

  ProgramId = glCreateProgram();
  glAttachShader(ProgramId, VertexShaderId);
  glAttachShader(ProgramId, FragmentShaderId);
  glLinkProgram(ProgramId);
  //glUseProgram(ProgramId);

  ErrorCheckValue = glGetError();
  if (ErrorCheckValue != GL_NO_ERROR)
  {
    std::cerr << "ERROR6: Could not create the shaders: " << gluErrorString(ErrorCheckValue) << std::endl;
    exit(-1);
  }
  return ProgramId;
}

void Shaders::reload()
{
  glUseProgram(0);
  loadShaders();
  const GLchar *VertexShader = vertex.c_str();
  const GLchar *FragmentShader = fragment.c_str();

  glDetachShader(ProgramId, VertexShaderId);
  glDetachShader(ProgramId, FragmentShaderId);

  glShaderSource(VertexShaderId, 1, &VertexShader, NULL);
  glCompileShader(VertexShaderId);

  glShaderSource(FragmentShaderId, 1, &FragmentShader, NULL);
  glCompileShader(FragmentShaderId);

  glAttachShader(ProgramId, VertexShaderId);
  glAttachShader(ProgramId, FragmentShaderId);
  glLinkProgram(ProgramId);
  glUseProgram(ProgramId);
}

void Shaders::destroyShaders(void)
{
  GLenum ErrorCheckValue = glGetError();

  glUseProgram(0);

  glDetachShader(ProgramId, VertexShaderId);
  glDetachShader(ProgramId, FragmentShaderId);

  glDeleteShader(FragmentShaderId);
  glDeleteShader(VertexShaderId);

  glDeleteProgram(ProgramId);

  ErrorCheckValue = glGetError();
  if (ErrorCheckValue != GL_NO_ERROR)
  {
    std::cerr << "ERROR: Could not destroy the shaders: " << gluErrorString(ErrorCheckValue) << std::endl;
    exit(-1);
  }
}
