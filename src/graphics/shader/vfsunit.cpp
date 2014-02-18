#include "vfsunit.hpp"

void checkShaderCompileStatus(GLint ShaderID, std::string ShaderName)
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

void checkProgramLinkStatus(GLint ProgramID, std::string ProgramName)
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

void checkForGLError(std::string info)
{
  GLenum ErrorCheckValue = glGetError();
  if (ErrorCheckValue != GL_NO_ERROR)
  {
    std::cerr << "GL_ERROR \"" << info << "\":" << gluErrorString(ErrorCheckValue) << std::endl;
    //exit(-1);
  }
}

VFSUnit::VFSUnit(std::string programName, std::string VertexFile, std::string FragmentFile):name(programName), FragFile(FragmentFile), VertFile(VertexFile)
{
  fd = inotify_init();
  FD_ZERO( &watch_set );
  FD_SET( fd, &watch_set );
  wd = inotify_add_watch( fd, FragmentFile.c_str(), IN_MODIFY );
  req.tv_sec = (time_t)(0);
  req.tv_nsec = 1;
}

VFSUnit::~VFSUnit()
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
    //exit(-1);
  }
}
void VFSUnit::load()
{
  glUseProgram(0);
  checkForGLError("What!?");
  auto vertex = ShaderParser::process(VertFile);
  //std::cout << vertex << std::endl;
  const char *VertexShader = vertex.c_str();
  auto fragment = ShaderParser::process(FragFile);
  const char *FragmentShader = fragment.c_str();
  struct stat fileinfo;

  if(-1 != stat(VertFile.c_str(), &fileinfo))
    vert_mtime = fileinfo.st_mtime;

  if(-1 != stat(FragFile.c_str(), &fileinfo))
    frag_mtime = fileinfo.st_mtime;

  VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
  checkForGLError(name + ": Creating VertexShader");

  int length =  vertex.size();
  glShaderSource(VertexShaderId, 1, &VertexShader, &length);
  glCompileShader(VertexShaderId);
  checkShaderCompileStatus(VertexShaderId, name + ": VertexShader");

  FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
  checkForGLError(name + ": Creating FragmentShader");

  length = fragment.size();
  glShaderSource(FragmentShaderId, 1, &FragmentShader, &length);
  glCompileShader(FragmentShaderId);
  checkShaderCompileStatus(FragmentShaderId, name + ": Fragment");

  ProgramId = glCreateProgram();
  checkForGLError(name + ": Creating Program");

  glAttachShader(ProgramId, VertexShaderId);
  glAttachShader(ProgramId, FragmentShaderId);
  glLinkProgram(ProgramId);
  checkForGLError(name + ": Linking Program");
  checkProgramLinkStatus(ProgramId, name + ": Program LinkStatus");
}


GLuint VFSUnit::pid()
{
  return ProgramId;
}

void VFSUnit::reload()
{
  glUseProgram(0); // Just in case
  std::cout << name << ": Updating Shaders" << std::endl;
  auto vertex = ShaderParser::process(VertFile);
  //std::cout << vertex << std::endl;
  const char *VertexShader = vertex.c_str();
  auto fragment = ShaderParser::process(FragFile);
  const char *FragmentShader = fragment.c_str();

  checkForGLError(name + ": Random error before anything");
  glDetachShader(ProgramId, VertexShaderId);
  glDetachShader(ProgramId, FragmentShaderId);
  checkForGLError(name + ": Detaching Shaders");

  glShaderSource(VertexShaderId, 1, &VertexShader, NULL);
  glCompileShader(VertexShaderId);
  checkShaderCompileStatus(VertexShaderId, name + ": VertexShader");

  glShaderSource(FragmentShaderId, 1, &FragmentShader, NULL);
  glCompileShader(FragmentShaderId);
  checkShaderCompileStatus(VertexShaderId, name + ": FragmentShader");

  glAttachShader(ProgramId, VertexShaderId);
  glAttachShader(ProgramId, FragmentShaderId);
  glLinkProgram(ProgramId);
  checkForGLError(name + ": Linking Program");
  checkProgramLinkStatus(ProgramId, name + ": Program LinkStatus");
}

