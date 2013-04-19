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
  //remove after clear
  //local directory is the one where you run the main from
  vertex = readShaderFile("shaders/simple.vertex");
  fragment = readShaderFile("shaders/simple.fragment");
  compute = readShaderFile("shaders/simple.compute");
}

void Shaders::checkShaderCompileStatus(GLint ShaderID, std::string ShaderName)
{
  int rvalue;
  glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &rvalue);
  if (!rvalue) {
	  std::cerr << "Error in compiling " << ShaderName << " shader." << std::endl;
    GLsizei length;
    glGetShaderiv(ShaderID, GL_INFO_LOG_LENGTH, &length);
    GLchar* log = (GLchar*)malloc(sizeof(GLchar)*length);
	  glGetShaderInfoLog(ShaderID, length, &length, log);
	  std::cerr << "Compiler log:" << std::endl << log << std::endl;
  } 
}

void Shaders::checkProgramLinkStatus(GLint ProgramID, std::string ProgramName)
{
  int rvalue;
  glGetProgramiv(ProgramID, GL_LINK_STATUS, &rvalue);
  if (!rvalue) {
	  std::cerr << "Error in linking " << ProgramName << " program." << std::endl;
    GLsizei length;
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &length);
    GLchar* log = (GLchar*)malloc(sizeof(GLchar)*length);
	  glGetProgramInfoLog(ProgramID, length, &length, log);
	  std::cerr << "Compiler log:" << std::endl << log << std::endl;
  } 
}

void Shaders::checkForGLError(std::string info)
{
  GLenum ErrorCheckValue = glGetError();
  if (ErrorCheckValue != GL_NO_ERROR)
  {
    std::cerr << "GL_ERROR \"" << info << "\":" << gluErrorString(ErrorCheckValue) << std::endl;
    //exit(-1);
  }
}

GLint Shaders::createShaders(void)
{
	glUseProgram(0);
  checkForGLError("What!?");
  const char *VertexShader = vertex.c_str();
  const char *FragmentShader = fragment.c_str();
  const char *ComputeShader = compute.c_str();

  VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
  checkForGLError("Creating VertexShader");

  int length =  vertex.size();
  glShaderSource(VertexShaderId, 1, &VertexShader, &length);
  glCompileShader(VertexShaderId);
  checkShaderCompileStatus(VertexShaderId, "Vertex");

  FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
  checkForGLError("Creating FragmentShader");

  length =  fragment.size();
  glShaderSource(FragmentShaderId, 1, &FragmentShader, &length);
  glCompileShader(FragmentShaderId);
  checkShaderCompileStatus(FragmentShaderId, "Fragment");

  ProgramId = glCreateProgram();
  checkForGLError("Creating Program");

  glAttachShader(ProgramId, VertexShaderId);
  glAttachShader(ProgramId, FragmentShaderId);
  glLinkProgram(ProgramId);
  checkForGLError("Linking Program Basic");
  checkProgramLinkStatus(ProgramId, "Basic");


  //computeshader stuff --------------------------------------------------

  ComputeShaderId = glCreateShader(GL_COMPUTE_SHADER);
  checkForGLError("Creating ComputeShader");

  length =  compute.size();
  glShaderSource(ComputeShaderId, 1, &ComputeShader, &length);
  glCompileShader(ComputeShaderId);
  checkShaderCompileStatus(ComputeShaderId, "Compute");

  ComProgramId = glCreateProgram();
  checkForGLError("Creating ComputeShaderProgram");

  glAttachShader(ComProgramId, ComputeShaderId);
  glLinkProgram(ComProgramId);
  checkForGLError("Linking ComProgramId");
  checkProgramLinkStatus(ProgramId, "ComProgramId");

//--------------------------------------------------------------------

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
  checkShaderCompileStatus(VertexShaderId, "VertexShaderId");

  glShaderSource(FragmentShaderId, 1, &FragmentShader, NULL);
  glCompileShader(FragmentShaderId);
  checkShaderCompileStatus(FragmentShaderId, "FragmentShaderId");

  glAttachShader(ProgramId, VertexShaderId);
  glAttachShader(ProgramId, FragmentShaderId);
  glLinkProgram(ProgramId);
  checkProgramLinkStatus(ProgramId, "ComProgramId");
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
