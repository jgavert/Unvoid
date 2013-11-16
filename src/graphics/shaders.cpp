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
  shaderSources = std::vector<std::string>();
  vertex = readShaderFile("shaders/simple.vertex");
  fragment = readShaderFile("shaders/simple.fragment");
  compute = readShaderFile("shaders/simple.compute");
  shaderSources.push_back(readShaderFile("shaders/compute.vertex"));
  shaderSources.push_back(readShaderFile("shaders/compute.fragment"));
  shaderSources.push_back(readShaderFile("shaders/compute.geometry"));
  shaderSources.push_back(readShaderFile("shaders/postprocess.vertex"));
  shaderSources.push_back(readShaderFile("shaders/postprocess.fragment"));

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
  shaders = std::vector<GLint>();
  programs = std::vector<GLint>();
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
  programs.push_back(ProgramId);
  checkForGLError("Linking Program Basic");
  checkProgramLinkStatus(ProgramId, "Basic");


  //computeshader stuff --------------------------------------------------
  /*
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
  programs.push_back(ComProgramId);
  checkForGLError("Linking ComProgramId");
  checkProgramLinkStatus(ProgramId, "ComProgramId");

  //visualasation of particles
  int compVertex = glCreateShader(GL_VERTEX_SHADER);
  shaders.push_back(compVertex);
  checkForGLError("Creating GL_VERTEX_SHADER");
  int compFragment = glCreateShader(GL_FRAGMENT_SHADER);
  shaders.push_back(compFragment);
  checkForGLError("Creating GL_FRAGMENT_SHADER");
  int compGeometry = glCreateShader(GL_GEOMETRY_SHADER);
  shaders.push_back(compGeometry);
  checkForGLError("Creating GL_GEOMETRY_SHADER");

  VertexShader = shaderSources.at(0).c_str();
  FragmentShader = shaderSources.at(1).c_str();
  const char* GeometryShader = shaderSources.at(2).c_str();

  length =  shaderSources.at(0).size();
  glShaderSource(compVertex, 1, &VertexShader, &length);
  glCompileShader(compVertex);
  checkShaderCompileStatus(compVertex, "ComputeVertex");

  length =  shaderSources.at(2).size();
  glShaderSource(compGeometry, 1, &GeometryShader, &length);
  glCompileShader(compGeometry);
  checkShaderCompileStatus(compGeometry, "GeometryShader");

  length =  shaderSources.at(1).size();
  glShaderSource(compFragment, 1, &FragmentShader, &length);
  glCompileShader(compFragment);
  checkShaderCompileStatus(compFragment, "ComputeFragment");


  int computevisualprogram = glCreateProgram();
  checkForGLError("Creating computevisualprogram");

  glAttachShader(computevisualprogram, compVertex);
  glAttachShader(computevisualprogram, compGeometry);
  glAttachShader(computevisualprogram, compFragment);
  glLinkProgram(computevisualprogram);
  programs.push_back(computevisualprogram);
  checkForGLError("Linking Program VisualCompute");
  checkProgramLinkStatus(computevisualprogram, "VisualCompute");
*/
//--------------------------------------------------------------------

//---------   POSTPROCESS -------------------------------------------
  VertexShader = shaderSources.at(3).c_str();
  FragmentShader = shaderSources.at(4).c_str();

  int postVertex = glCreateShader(GL_VERTEX_SHADER);
  shaders.push_back(postVertex);
  checkForGLError("Creating GL_VERTEX_SHADER");
  int postFragment = glCreateShader(GL_FRAGMENT_SHADER);
  shaders.push_back(postFragment);
  checkForGLError("Creating GL_FRAGMENT_SHADER");


  length =  shaderSources.at(3).size();
  glShaderSource(postVertex, 1, &VertexShader, &length);
  glCompileShader(postVertex);
  checkShaderCompileStatus(postVertex, "PostprocessVertex");

  length =  shaderSources.at(4).size();
  glShaderSource(postFragment, 1, &FragmentShader, &length);
  glCompileShader(postFragment);
  checkShaderCompileStatus(postFragment, "PostprocessFragment");


  int PostProcessProgram = glCreateProgram();
  checkForGLError("Creating postProcessprogram");

  glAttachShader(PostProcessProgram, postVertex);
  glAttachShader(PostProcessProgram, postFragment);
  glLinkProgram(PostProcessProgram);
  programs.push_back(PostProcessProgram);
  checkForGLError("Linking Program PostProcess");
  checkProgramLinkStatus(PostProcessProgram, "PostProcess");
//-------------------------------------------------------------------
  return ProgramId;
}

void Shaders::reload()
{
  checkForGLError("whaaat1");
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

  // particle shader reload
    VertexShader = shaderSources.at(0).c_str();
  FragmentShader = shaderSources.at(1).c_str();
  const char* GeometryShader = shaderSources.at(2).c_str();

  glDetachShader(programs.at(2), shaders.at(0));
  glDetachShader(programs.at(2), shaders.at(1));
  glDetachShader(programs.at(2), shaders.at(2));
  checkForGLError("Linking Program VisualCompute0");

  int length =  shaderSources.at(0).size();
  glShaderSource(shaders.at(0), 1, &VertexShader, &length);
  glCompileShader(shaders.at(0));
  checkShaderCompileStatus(shaders.at(0), "ComputeVertex");
  checkForGLError("Linking Program VisualCompute1");

  length =  shaderSources.at(2).size();
  glShaderSource(shaders.at(2), 1, &GeometryShader, &length);
  glCompileShader(shaders.at(2));
  checkShaderCompileStatus(shaders.at(2), "ComputeGeometry");
  checkForGLError("Linking Program VisualCompute2");

  length =  shaderSources.at(1).size();
  glShaderSource(shaders.at(1), 1, &FragmentShader, &length);
  glCompileShader(shaders.at(1));
  checkShaderCompileStatus(shaders.at(1), "ComputeFragment");
  checkForGLError("Linking Program VisualCompute3");


  glAttachShader(programs.at(2), shaders.at(0));
  glAttachShader(programs.at(2), shaders.at(2));
  glAttachShader(programs.at(2), shaders.at(1));
  glLinkProgram(programs.at(2));
  checkForGLError("Linking Program VisualCompute");
  checkProgramLinkStatus(programs.at(2), "VisualCompute");

  // postprocess shader reload
    VertexShader = shaderSources.at(3).c_str();
  FragmentShader = shaderSources.at(4).c_str();

  glDetachShader(programs.at(3), shaders.at(3));
  checkForGLError("Linking Program PostProcess1");
  glDetachShader(programs.at(3), shaders.at(4));
  checkForGLError("Linking Program PostProcess2");

  length =  shaderSources.at(3).size();
  glShaderSource(shaders.at(3), 1, &VertexShader, &length);
  glCompileShader(shaders.at(3));
  checkShaderCompileStatus(shaders.at(3), "PostprocessVertex");

  length =  shaderSources.at(4).size();
  glShaderSource(shaders.at(4), 1, &FragmentShader, &length);
  glCompileShader(shaders.at(4));
  checkShaderCompileStatus(shaders.at(4), "PostprocessFragment");


  checkForGLError("Linking Program PostProcess2");
  glAttachShader(programs.at(3), shaders.at(3));
  glAttachShader(programs.at(3), shaders.at(4));
  glLinkProgram(programs.at(3));
  checkForGLError("Linking Program PostProcess");
  checkProgramLinkStatus(programs.at(3), "PostProcess");
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
