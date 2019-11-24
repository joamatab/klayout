
/*

  KLayout Layout Viewer
  Copyright (C) 2006-2019 Matthias Koefferlein

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

*/



#ifndef HDR_dbMAGWriter
#define HDR_dbMAGWriter

#include "dbPluginCommon.h"
#include "dbWriter.h"
#include "dbMAG.h"
#include "dbMAGFormat.h"
#include "dbSaveLayoutOptions.h"
#include "tlProgress.h"

namespace tl
{
  class OutputStream;
}

namespace db
{

class Layout;
class SaveLayoutOptions;

/**
 *  @brief A MAG writer abstraction
 */
class DB_PLUGIN_PUBLIC MAGWriter
  : public db::WriterBase
{
public:
  /**
   *  @brief Instantiate the writer
   */
  MAGWriter ();

  /**
   *  @brief Write the layout object
   */
  void write (db::Layout &layout, tl::OutputStream &stream, const db::SaveLayoutOptions &options);

private:
  struct endl_tag { };

  tl::OutputStream *mp_stream;
  MAGWriterOptions m_options;
  tl::AbsoluteProgress m_progress;
  endl_tag endl;
  db::LayerProperties m_layer;
  bool m_needs_emit;
  
  MAGWriter &operator<<(const char *s);
  MAGWriter &operator<<(const std::string &s);
  MAGWriter &operator<<(endl_tag);

  template<class X> MAGWriter &operator<<(const X &x)
  {
    return (*this << tl::to_string(x));
  }

  void write_texts (const db::Layout &layout, const db::Cell &cell, unsigned int layer, double tl_scale);
  void write_polygons (const db::Layout &layout, const db::Cell &cell, unsigned int layer, double tl_scale);
  void write_polygon (const db::Polygon &polygon, double tl_scale);
  void write_boxes (const db::Layout &layout, const db::Cell &cell, unsigned int layer, double tl_scale);
  void write_paths (const db::Layout &layout, const db::Cell &cell, unsigned int layer, double tl_scale);
  void write_edges (const db::Layout &layout, const db::Cell &cell, unsigned int layer, double tl_scale);
  const char *xy_sep () const;

  void emit_layer();
};

} // namespace db

#endif

