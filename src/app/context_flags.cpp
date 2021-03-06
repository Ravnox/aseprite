// Aseprite
// Copyright (C) 2001-2015  David Capello
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "app/context_flags.h"

#include "app/context.h"
#include "app/document.h"
#include "doc/cel.h"
#include "doc/layer.h"
#include "doc/site.h"
#include "doc/sprite.h"

namespace app {

ContextFlags::ContextFlags()
{
  m_flags = 0;
}

void ContextFlags::update(Context* context)
{
  Site site = context->activeSite();
  Document* document = static_cast<Document*>(site.document());

  m_flags = 0;

  if (document) {
    m_flags |= HasActiveDocument;

    if (document->lock(Document::ReadLock, 0)) {
      m_flags |= ActiveDocumentIsReadable;

      if (document->isMaskVisible())
        m_flags |= HasVisibleMask;

      Sprite* sprite = site.sprite();
      if (sprite) {
        m_flags |= HasActiveSprite;

        if (sprite->backgroundLayer())
          m_flags |= HasBackgroundLayer;

        Layer* layer = site.layer();
        if (layer) {
          m_flags |= HasActiveLayer;

          if (layer->isBackground())
            m_flags |= ActiveLayerIsBackground;

          if (layer->isVisible())
            m_flags |= ActiveLayerIsVisible;

          if (layer->isEditable())
            m_flags |= ActiveLayerIsEditable;

          if (layer->isImage()) {
            m_flags |= ActiveLayerIsImage;

            Cel* cel = layer->cel(site.frame());
            if (cel) {
              m_flags |= HasActiveCel;

              if (cel->image())
                m_flags |= HasActiveImage;
            }
          }
        }
      }

      if (document->lockToWrite(0))
        m_flags |= ActiveDocumentIsWritable;

      document->unlock();
    }
  }
}

} // namespace app
