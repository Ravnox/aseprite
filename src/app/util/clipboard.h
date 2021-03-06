// Aseprite
// Copyright (C) 2001-2015  David Capello
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.

#ifndef APP_UTIL_CLIPBOARD_H_INCLUDED
#define APP_UTIL_CLIPBOARD_H_INCLUDED
#pragma once

#include "gfx/point.h"
#include "gfx/size.h"
#include "ui/base.h"

namespace doc {
  class Image;
  class Palette;
}

namespace app {
  class ContextReader;
  class ContextWriter;
  class DocumentRange;

  namespace clipboard {
    using namespace doc;

    enum ClipboardFormat {
      ClipboardNone,
      ClipboardImage,
      ClipboardDocumentRange,
    };

    // TODO Horrible API: refactor it.

    ClipboardFormat get_current_format();
    void get_document_range_info(Document** document, DocumentRange* range);

    void clear_content();
    void cut(ContextWriter& context);
    void copy(const ContextReader& context);
    void copy_range(const ContextReader& context, const DocumentRange& range);
    void copy_image(Image* image, Palette* palette, const gfx::Point& point);
    void paste();

    // Returns true and fills the specified "size"" with the image's
    // size in the clipboard, or return false in case that the clipboard
    // doesn't contain an image at all.
    bool get_image_size(gfx::Size& size);

  } // namespace clipboard
} // namespace app

#endif
