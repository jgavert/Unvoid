/*
 * File:   Renderer.cpp
 * Author: juho
 *
 * Created on November 28, 2011, 1:15 PM
 */
#ifdef _WIN32
#include <GL\glew.h>
#else
#include <GL/glew.h>
#endif

#include "window.h"
#include "renderer.h"

Renderer::Renderer(Window& w, int width, int height):
  window(w), CurrentWidth(width), CurrentHeight(height)
{
  WindowHandle = 0;
  timeGLV = 0.f;
  FrameCount = 0;
  window.createWindow(CurrentWidth, CurrentHeight);

  //particleManager = ParticleManager(1000);
}

Renderer::~Renderer() {
}

void Renderer::checkForGLError(std::string info)
{
  GLenum ErrorCheckValue = glGetError();
  if (ErrorCheckValue != GL_NO_ERROR)
  {
    std::cerr << "GL_ERROR \"" << info << "\":";
    std::cerr << gluErrorString(ErrorCheckValue) << std::endl;
    //exit(-1);
  }
}

void Renderer::initialize()
{
  GLenum GlewInitResult;

  glewExperimental = GL_TRUE;
  GlewInitResult = glewInit();

  if (GLEW_OK != GlewInitResult) {
    std::cerr << "ERROR: %s" << glewGetErrorString(GlewInitResult) <<std::endl;
    exit(EXIT_FAILURE);
  }
  //SDL_GL_SetAttribute(GL_CONTEXT_, int value)
  std::cout << "OpenGL renderer: " << glGetString(GL_RENDERER) << std::endl;
  std::cout << "OpenGL vendor:   " << glGetString(GL_VENDOR) << std::endl;
  std::cout << "OpenGL Version:  " << glGetString(GL_VERSION) << std::endl;
  int majorVersion, minorVersion;
  glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
  glGetIntegerv(GL_MINOR_VERSION, &minorVersion);
  std::cout << "OpenGL Major:    " << majorVersion<< ", Minor: " << minorVersion << std::endl;
  glClearColor(0.3f, 0.1f, 0.5f, 0.0f);

  glEnable( GL_DEPTH_TEST );
  glDepthFunc(GL_LEQUAL);
  glEnable( GL_CULL_FACE);
  glCullFace(GL_BACK);
  glFrontFace(GL_CCW);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

  shaders.initialize();
  //GLint shaderProgram = shaders.get("Basic");
  viewMatrix = glGetUniformLocation( shaders.get("Basic"), "ViewMatrix" );
  projectionMatrix = glGetUniformLocation(shaders.get("Basic") , "ProjectionMatrix" );
  modelMatrix = glGetUniformLocation(shaders.get("Basic") , "ModelMatrix" );
  timeGLP = glGetUniformLocation( shaders.get("Basic"), "time");
  resolutionGLP = glGetUniformLocation( shaders.get("Basic"), "resolution");
  cameraPosGLP = glGetUniformLocation( shaders.get("Basic"), "cameraPos");

  tGLP = glGetUniformLocation( shaders.get("glsl"), "time");
  rGLP = glGetUniformLocation( shaders.get("glsl"), "resolution");
  positionGLP = glGetUniformLocation( shaders.get("glsl"), "position");
  lookGLP = glGetUniformLocation( shaders.get("glsl"), "direction");


  glUseProgram(0);
  //glm::vec2 res = glm::vec2(static_cast<float>(CurrentWidth),static_cast<float>(CurrentHeight));
  //glUniform2fv(resolutionGLP, 1, glm::value_ptr(res));
  //glUniform2fv(rGLP, 1, glm::value_ptr(res));

  projection = view = glm::mat4();
  view = glm::lookAt(
    glm::vec3( -5.0f, 0.0f, -1.0f ), //missä olen
    glm::vec3( 0.0f, 0.0f, 0.0f ), //minne katon
    glm::vec3( 0.0f, 1.0f, 0.0f )  //vektori ylöspäin kamerasta
  );
  position = glm::vec3( -5.0f, 0.0f, -1.0f);
  direction = glm::vec3(0.0f, 0.0f, 0.0f);
  projection = glm::perspective( 45.0f, static_cast<float>(CurrentWidth) / static_cast<float>(CurrentHeight), 0.01f, 1000.0f );

  //glUniformMatrix4fv( viewMatrix, 1, GL_FALSE, glm::value_ptr( view ) );
  //glUniformMatrix4fv( projectionMatrix, 1, GL_FALSE, glm::value_ptr( projection ) );
/*
  compVisProjection = glGetUniformLocation(shaders.programs.at(2), "ProjectionMatrix");
  compVisView = glGetUniformLocation(shaders.programs.at(2), "ViewMatrix");
  compVisTime = glGetUniformLocation(shaders.programs.at(2), "time" );
  compResolutionGLP = glGetUniformLocation(shaders.programs.at(2), "resolution");
  compCamPosLoc = glGetUniformLocation(shaders.programs.at(2), "camPos");
  particleManager.Initialize(shaders.ComProgramId);
*/
  fbo = FSQuad(CurrentHeight, CurrentWidth, shaders.get("PostProcess"));
  fbo.loadToGpu();
  vbo_glsl = FSQuad(CurrentHeight, CurrentWidth, shaders.get("glsl"));
  vbo_glsl.loadToGpu();
}

void Renderer::loadVBO(VBO data) {
  vbos.push_back(std::move(data));
  vbos.back().loadToGpu();
}


void Renderer::DestroyVBOs()
{
  GLenum ErrorCheckValue = glGetError();

  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindVertexArray(0);

  ErrorCheckValue = glGetError();
  if (ErrorCheckValue != GL_NO_ERROR)
  {
    std::cerr << "ERROR: Could not destroy the VBO: " << gluErrorString(ErrorCheckValue)<< std::endl;
    exit(-1);
  }
}
void Renderer::Cleanup(void)
{
  DestroyVBOs();
}

void Renderer::lookAt(float x, float y, float z, float tx, float ty, float tz)
{
  position = glm::vec3(x, y, z);
  direction = glm::vec3(tx,ty,tz);
  view = glm::lookAt(
    position, //missä olen
    direction, //minne katon
    glm::vec3( 0.0f, 1.0f, 0.0f )  //vektori ylöspäin kamerasta
  );
  //glUniform3fv(cameraPosGLP,1, glm::value_ptr(pos));
  //glUniformMatrix4fv( viewMatrix, 1, GL_FALSE, glm::value_ptr( view ) );

}

void Renderer::reloadShaders() {
  bool result = shaders.update();

  if (result) {
    viewMatrix = glGetUniformLocation( shaders.get("Basic"), "ViewMatrix" );
    projectionMatrix = glGetUniformLocation( shaders.get("Basic"), "ProjectionMatrix" );
    modelMatrix = glGetUniformLocation( shaders.get("Basic"), "ModelMatrix" );
    timeGLP = glGetUniformLocation( shaders.get("Basic"), "time");
    resolutionGLP = glGetUniformLocation( shaders.get("Basic"), "resolution");
    cameraPosGLP = glGetUniformLocation( shaders.get("Basic"), "cameraPos");

    tGLP = glGetUniformLocation( shaders.get("glsl"), "time");
    rGLP = glGetUniformLocation( shaders.get("glsl"), "resolution");
    positionGLP = glGetUniformLocation( shaders.get("glsl"), "position");
    lookGLP = glGetUniformLocation( shaders.get("glsl"), "direction");
  }
}

void Renderer::render(float time, bool pEnabled, bool fboEnabled, bool glsl)
{
  ++FrameCount;
  timeGLV += 0.02f*time;

  if (glsl) {
    vbo_glsl.drawToFBO();
    glUseProgram(shaders.get("glsl")); //Remember to activate program before...
    glClearColor(0.f, 0.f, 0.f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::vec2 res = glm::vec2(static_cast<float>(CurrentWidth),static_cast<float>(CurrentHeight));
    glUniform2fv(rGLP, 1, glm::value_ptr(res)); // ...adding any Uniforms
    glUniform1fv(tGLP, 1, &timeGLV);
    glUniform3fv(positionGLP, 1, glm::value_ptr(position));
    glUniform3fv(lookGLP, 1, glm::value_ptr(direction));

    glDisable(GL_BLEND);
    vbo_glsl.drawFBO(); //this call is too specific which is why above is done.
  } else {
    if (fboEnabled) {
      fbo.drawToFBO();
    }

    glClearColor(0.f, 0.f, 0.f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shaders.get("Basic"));
    glUniform1fv(timeGLP, 1, &timeGLV);
    glUniformMatrix4fv( viewMatrix, 1, GL_FALSE, glm::value_ptr( view ) );
    glUniformMatrix4fv( projectionMatrix, 1, GL_FALSE, glm::value_ptr( projection ) );
    glm::vec2 res = glm::vec2(static_cast<float>(CurrentWidth),static_cast<float>(CurrentHeight));
    glUniform2fv(resolutionGLP, 1, glm::value_ptr(res));
    glUniform3fv(cameraPosGLP,1, glm::value_ptr(position));



    for (auto &it: vbos) {
      it.modelMatrix = glm::rotate(
          vbos[0].modelMatrix,
          1.f*time,
          glm::vec3( 0.0f, 0.0f, 0.01 )
        );
      glUniformMatrix4fv( modelMatrix, 1, GL_FALSE, glm::value_ptr( it.modelMatrix ) );
      it.draw();
    }

    if (pEnabled){
      /*
      //std::cout << "time: " << time << std::endl;
      particleManager.Simulate(time, glm::vec4(15.f,0.f,0.f,0.f));
      glUseProgram(shaders.programs.at(2));
      glDepthMask(GL_FALSE);
      glEnable(GL_BLEND);
      //std::cout << timeGLV << std::endl;
      glUniform1fv(compVisTime, 1, &timeGLV);
      glUniformMatrix4fv( compVisView, 1, GL_FALSE, glm::value_ptr( view ) );
      glUniformMatrix4fv( compVisProjection, 1, GL_FALSE, glm::value_ptr( projection ) );
      glUniform4fv(compCamPosLoc, 1, glm::value_ptr( position) );

      glBindBuffer(GL_ARRAY_BUFFER, particleManager.getBufferID());
      glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), (GLvoid*)0);
      glEnableVertexAttribArray(0);
      glEnableClientState(GL_VERTEX_ARRAY);
      glDrawArrays(GL_POINTS, 0, particleManager.getParticleCount());
      glDisableClientState(GL_VERTEX_ARRAY);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      glDepthMask(GL_TRUE);
      */
    }

    if (fboEnabled) {
      glDisable(GL_BLEND);
      fbo.drawFBO();
    }
  }
  glUseProgram(0);

  window.swap_buffers();
}

long long Renderer::getFrames()
{
  return FrameCount;
}
