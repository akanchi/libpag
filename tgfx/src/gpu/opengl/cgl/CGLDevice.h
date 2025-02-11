/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Tencent is pleased to support the open source community by making libpag available.
//
//  Copyright (C) 2021 THL A29 Limited, a Tencent company. All rights reserved.
//
//  Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file
//  except in compliance with the License. You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
//  unless required by applicable law or agreed to in writing, software distributed under the
//  license is distributed on an "as is" basis, without warranties or conditions of any kind,
//  either express or implied. see the license for the specific language governing permissions
//  and limitations under the license.
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <AppKit/AppKit.h>
#include "gpu/opengl/GLDevice.h"

namespace pag {
class CGLDevice : public GLDevice {
 public:
  /**
   * Returns an CGL device associated with current OpenGL context. Returns nullptr if there is no
   * current OpenGL context on the calling thread.
   */
  static std::shared_ptr<CGLDevice> Current();

  /**
   * Creates an CGL device with adopted CGL context.
   */
  static std::shared_ptr<CGLDevice> MakeAdopted(CGLContextObj cglContext);

  /**
   * Creates an offscreen CGL device with specified shared context.
   */
  static std::shared_ptr<CGLDevice> Make(CGLContextObj sharedContext = nullptr);

  ~CGLDevice() override;

  bool sharableWith(void* nativeHandle) const override;

  CGLContextObj cglContext() const;

  CVOpenGLTextureCacheRef getTextureCache();

  void releaseTexture(CVOpenGLTextureRef texture);

 protected:
  bool onMakeCurrent() override;
  void onClearCurrent() override;

 private:
  NSOpenGLContext* glContext = nil;
  CGLContextObj oldContext = nil;
  CVOpenGLTextureCacheRef textureCache = nil;

  static std::shared_ptr<CGLDevice> Wrap(CGLContextObj cglContext, bool isAdopted = false);

  CGLDevice(std::unique_ptr<Context> context, CGLContextObj cglContext);

  friend class CGLWindow;
};
}  // namespace pag
