
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



#ifndef HDR_dbMAGReader
#define HDR_dbMAGReader

#include "dbPluginCommon.h"
#include "dbNamedLayerReader.h"
#include "dbLayout.h"
#include "dbMAG.h"
#include "dbMAGFormat.h"
#include "dbStreamLayers.h"
#include "dbPropertiesRepository.h"

#include "tlException.h"
#include "tlInternational.h"
#include "tlProgress.h"
#include "tlString.h"
#include "tlStream.h"

#include <map>
#include <set>

namespace db
{

/**
 *  @brief Generic base class of MAG reader exceptions
 */
class DB_PLUGIN_PUBLIC MAGReaderException
  : public ReaderException
{
public:
  MAGReaderException (const std::string &msg, size_t l, const std::string &file)
    : ReaderException (tl::sprintf (tl::to_string (tr ("%s (line=%ld, file=%s)")), msg, l, file))
  { }
};

/**
 *  @brief The MAG format stream reader
 */
class DB_PLUGIN_PUBLIC MAGReader
  : public NamedLayerReader,
    public MAGDiagnostics
{
public: 
  typedef std::vector<tl::Variant> property_value_list;

  /**
   *  @brief Construct a stream reader object
   *
   *  @param s The stream delegate from which to read stream data from
   */
  MAGReader (tl::InputStream &s);

  /**  
   *  @brief Destructor
   */
  ~MAGReader ();

  /** 
   *  @brief The basic read method 
   *
   *  This method will read the stream data and translate this to
   *  insert calls into the layout object. This will not do much
   *  on the layout object beside inserting the objects.
   *  A set of options can be specified with the LoadLayoutOptions
   *  object.
   *  The returned map will contain all layers, the passed
   *  ones and the newly created ones.
   *
   *  @param layout The layout object to write to
   *  @param map The LayerMap object
   *  @param create true, if new layers should be created
   *  @return The LayerMap object that tells where which layer was loaded
   */
  virtual const LayerMap &read (db::Layout &layout, const LoadLayoutOptions &options);

  /** 
   *  @brief The basic read method (without mapping)
   *
   *  This method will read the stream data and translate this to
   *  insert calls into the layout object. This will not do much
   *  on the layout object beside inserting the objects.
   *  This version will read all input layers and return a map
   *  which tells which MAG layer has been read into which logical
   *  layer.
   *
   *  @param layout The layout object to write to
   *  @return The LayerMap object
   */
  virtual const LayerMap &read (db::Layout &layout);

  /**
   *  @brief Format
   */
  virtual const char *format () const { return "MAG"; }

  /**
   *  @brief Issue an error with positional information
   *
   *  Reimplements MAGDiagnostics
   */
  virtual void error (const std::string &txt);

  /**
   *  @brief Issue a warning with positional information
   *
   *  Reimplements MAGDiagnostics
   */
  virtual void warn (const std::string &txt);

private:
  tl::TextInputStream m_stream;
  tl::AbsoluteProgress m_progress;
  double m_lambda, m_dbu;
  std::vector<std::string> m_lib_paths;

  void do_read (db::Layout &layout);
};

}

#endif

