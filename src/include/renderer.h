#ifndef _renderer_h_
#define _renderer_h_

void cui_renderer_initFrame();
void cui_renderer_finalizeFrame();
void cui_renderer_preDrawFrame();

void cui_renderer_initImage();
void cui_renderer_finalizeImage();
void cui_renderer_preDrawImage();

unsigned int cui_renderer_getFrameProgram();
unsigned int cui_renderer_getImageProgram();

unsigned int cui_renderer_getFrameVao();
unsigned int cui_renderer_getImageVao();

#endif
