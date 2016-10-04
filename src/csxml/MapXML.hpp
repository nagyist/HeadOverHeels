// Copyright (C) 2005-2007 Code Synthesis Tools CC
//
// This program was generated by CodeSynthesis XSD, an XML Schema to
// C++ data binding compiler
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
//
// In addition, as a special exception, Code Synthesis Tools CC gives
// permission to link this program with the Xerces-C++ library (or with
// modified versions of Xerces-C++ that use the same license as Xerces-C++),
// and distribute linked combinations including the two. You must obey
// the GNU General Public License version 2 in all respects for all of
// the code used other than Xerces-C++. If you modify this copy of the
// program, you may extend this exception to your version of the program,
// but you are not obligated to do so. If you do not wish to do so, delete
// this exception statement from your version
//
// Furthermore, Code Synthesis Tools CC makes a special exception for
// the Free/Libre and Open Source Software (FLOSS) which is described
// in the accompanying FLOSSE file
//

#ifndef MAP_XML_HPP
#define MAP_XML_HPP

#include <xsd/cxx/version.hxx>

#if (XSD_INT_VERSION != 3000000L)
#error XSD runtime version mismatch
#endif

#include <xsd/cxx/pre.hxx>

#ifndef XSD_USE_CHAR
#define XSD_USE_CHAR
#endif

#ifndef XSD_CXX_TREE_USE_CHAR
#define XSD_CXX_TREE_USE_CHAR
#endif

#include <xsd/cxx/tree/exceptions.hxx>
#include <xsd/cxx/tree/elements.hxx>
#include <xsd/cxx/tree/types.hxx>

#include <xsd/cxx/xml/error-handler.hxx>

#include <xsd/cxx/tree/parsing.hxx>

namespace xml_schema
{
  // anyType and anySimpleType
  //
  typedef ::xsd::cxx::tree::type type;
  typedef ::xsd::cxx::tree::simple_type<type> simple_type;

  // 8-bit
  //
  typedef signed char byte;
  typedef unsigned char unsigned_byte;

  // 16-bit
  //
  typedef short short_;
  typedef unsigned short unsigned_short;

  // 32-bit
  //
  typedef int int_;
  typedef unsigned int unsigned_int;

  // 64-bit
  //
  typedef long long long_;
  typedef unsigned long long unsigned_long;

  // Supposed to be arbitrary-length integral types
  //
  typedef long long integer;
  typedef integer non_positive_integer;
  typedef integer non_negative_integer;
  typedef integer positive_integer;
  typedef integer negative_integer;

  // Boolean
  //
  typedef bool boolean;

  // Floating-point types
  //
  typedef float float_;
  typedef double double_;
  typedef double decimal;

  // String types
  //
  typedef ::xsd::cxx::tree::string< char, simple_type > string;
  typedef ::xsd::cxx::tree::normalized_string< char, string > normalized_string;
  typedef ::xsd::cxx::tree::token< char, normalized_string > token;
  typedef ::xsd::cxx::tree::name< char, token > name;
  typedef ::xsd::cxx::tree::nmtoken< char, token > nmtoken;
  typedef ::xsd::cxx::tree::nmtokens< char, simple_type, nmtoken> nmtokens;
  typedef ::xsd::cxx::tree::ncname< char, name > ncname;
  typedef ::xsd::cxx::tree::language< char, token > language;

  // ID/IDREF
  //
  typedef ::xsd::cxx::tree::id< char, ncname > id;
  typedef ::xsd::cxx::tree::idref< type, char, ncname > idref;
  typedef ::xsd::cxx::tree::idrefs< char, simple_type, idref > idrefs;

  // URI
  //
  typedef ::xsd::cxx::tree::uri< char, simple_type > uri;

  // Qualified name
  //
  typedef ::xsd::cxx::tree::qname< char, simple_type, uri, ncname > qname;

  // Binary
  //
  typedef ::xsd::cxx::tree::buffer< char > buffer;
  typedef ::xsd::cxx::tree::base64_binary< char, simple_type > base64_binary;
  typedef ::xsd::cxx::tree::hex_binary< char, simple_type > hex_binary;

  // Date/time
  //
  typedef ::xsd::cxx::tree::date< char, simple_type > date;
  typedef ::xsd::cxx::tree::date_time< char, simple_type > date_time;
  typedef ::xsd::cxx::tree::duration< char, simple_type > duration;
  typedef ::xsd::cxx::tree::day< char, simple_type > day;
  typedef ::xsd::cxx::tree::month< char, simple_type > month;
  typedef ::xsd::cxx::tree::month_day< char, simple_type > month_day;
  typedef ::xsd::cxx::tree::year< char, simple_type > year;
  typedef ::xsd::cxx::tree::year_month< char, simple_type > year_month;
  typedef ::xsd::cxx::tree::time< char, simple_type > time;

  // Entity
  //
  typedef ::xsd::cxx::tree::entity< char, ncname > entity;
  typedef ::xsd::cxx::tree::entities< char, simple_type, entity > entities;

  // Flags and properties
  //
  typedef ::xsd::cxx::tree::flags flags;
  typedef ::xsd::cxx::tree::properties< char > properties;

  // DOM user data key for back pointers to tree nodes
  //
#ifndef XSD_CXX_TREE_TREE_NODE_KEY_IN___XML_SCHEMA
#define XSD_CXX_TREE_TREE_NODE_KEY_IN___XML_SCHEMA

  const XMLCh* const tree_node_key = ::xsd::cxx::tree::user_data_keys::node;

#endif

  // Exceptions
  //
  typedef ::xsd::cxx::tree::exception< char > exception;
  typedef ::xsd::cxx::tree::parsing< char > parsing;
  typedef ::xsd::cxx::tree::expected_element< char > expected_element;
  typedef ::xsd::cxx::tree::unexpected_element< char > unexpected_element;
  typedef ::xsd::cxx::tree::expected_attribute< char > expected_attribute;
  typedef ::xsd::cxx::tree::unexpected_enumerator< char > unexpected_enumerator;
  typedef ::xsd::cxx::tree::expected_text_content< char > expected_text_content;
  typedef ::xsd::cxx::tree::no_type_info< char > no_type_info;
  typedef ::xsd::cxx::tree::not_derived< char > not_derived;
  typedef ::xsd::cxx::tree::duplicate_id< char > duplicate_id;
  typedef ::xsd::cxx::tree::serialization< char > serialization;
  typedef ::xsd::cxx::tree::no_namespace_mapping< char > no_namespace_mapping;
  typedef ::xsd::cxx::tree::no_prefix_mapping< char > no_prefix_mapping;
  typedef ::xsd::cxx::tree::xsi_already_in_use< char > xsi_already_in_use;
  typedef ::xsd::cxx::tree::bounds< char > bounds;

  // Parsing/serialization diagnostics
  //
  typedef ::xsd::cxx::tree::severity severity;
  typedef ::xsd::cxx::tree::error< char > error;
  typedef ::xsd::cxx::tree::diagnostics< char > diagnostics;
}

// Forward declarations
//
namespace mxml
{
  class MapXML;
  class room;
}


#include <memory>    // std::auto_ptr
#include <algorithm> // std::binary_search

#include <xsd/cxx/tree/exceptions.hxx>
#include <xsd/cxx/tree/elements.hxx>
#include <xsd/cxx/tree/containers.hxx>
#include <xsd/cxx/tree/list.hxx>

#include <xsd/cxx/xml/dom/parsing-header.hxx>

namespace mxml
{
  class MapXML: public ::xml_schema::type
  {
    public:
    // room
    //
    typedef ::mxml::room room_type;
    typedef ::xsd::cxx::tree::sequence< room_type > room_sequence;
    typedef room_sequence::iterator room_iterator;
    typedef room_sequence::const_iterator room_const_iterator;
    typedef ::xsd::cxx::tree::traits< room_type, char > room_traits;

    const room_sequence&
    room () const;

    room_sequence&
    room ();

    void
    room (const room_sequence& s);

    // Constructors
    //
    MapXML ();

    MapXML (const ::xercesc::DOMElement& e,
            ::xml_schema::flags f = 0,
            ::xml_schema::type* c = 0);

    MapXML (const MapXML& x,
            ::xml_schema::flags f = 0,
            ::xml_schema::type* c = 0);

    virtual MapXML*
    _clone (::xml_schema::flags f = 0,
            ::xml_schema::type* c = 0) const;

    // Implementation
    //
    protected:
    void
    parse (::xsd::cxx::xml::dom::parser< char >&,
           ::xml_schema::flags);

    private:
    room_sequence room_;
  };

  class room: public ::xml_schema::type
  {
    public:
    // north
    //
    typedef ::xml_schema::string north_type;
    typedef ::xsd::cxx::tree::optional< north_type > north_optional;
    typedef ::xsd::cxx::tree::traits< north_type, char > north_traits;

    const north_optional&
    north () const;

    north_optional&
    north ();

    void
    north (const north_type& x);

    void
    north (const north_optional& x);

    void
    north (::std::auto_ptr< north_type > p);

    // south
    //
    typedef ::xml_schema::string south_type;
    typedef ::xsd::cxx::tree::optional< south_type > south_optional;
    typedef ::xsd::cxx::tree::traits< south_type, char > south_traits;

    const south_optional&
    south () const;

    south_optional&
    south ();

    void
    south (const south_type& x);

    void
    south (const south_optional& x);

    void
    south (::std::auto_ptr< south_type > p);

    // east
    //
    typedef ::xml_schema::string east_type;
    typedef ::xsd::cxx::tree::optional< east_type > east_optional;
    typedef ::xsd::cxx::tree::traits< east_type, char > east_traits;

    const east_optional&
    east () const;

    east_optional&
    east ();

    void
    east (const east_type& x);

    void
    east (const east_optional& x);

    void
    east (::std::auto_ptr< east_type > p);

    // west
    //
    typedef ::xml_schema::string west_type;
    typedef ::xsd::cxx::tree::optional< west_type > west_optional;
    typedef ::xsd::cxx::tree::traits< west_type, char > west_traits;

    const west_optional&
    west () const;

    west_optional&
    west ();

    void
    west (const west_type& x);

    void
    west (const west_optional& x);

    void
    west (::std::auto_ptr< west_type > p);

    // north-east
    //
    typedef ::xml_schema::string north_east_type;
    typedef ::xsd::cxx::tree::optional< north_east_type > north_east_optional;
    typedef ::xsd::cxx::tree::traits< north_east_type, char > north_east_traits;

    const north_east_optional&
    north_east () const;

    north_east_optional&
    north_east ();

    void
    north_east (const north_east_type& x);

    void
    north_east (const north_east_optional& x);

    void
    north_east (::std::auto_ptr< north_east_type > p);

    // north-west
    //
    typedef ::xml_schema::string north_west_type;
    typedef ::xsd::cxx::tree::optional< north_west_type > north_west_optional;
    typedef ::xsd::cxx::tree::traits< north_west_type, char > north_west_traits;

    const north_west_optional&
    north_west () const;

    north_west_optional&
    north_west ();

    void
    north_west (const north_west_type& x);

    void
    north_west (const north_west_optional& x);

    void
    north_west (::std::auto_ptr< north_west_type > p);

    // south-east
    //
    typedef ::xml_schema::string south_east_type;
    typedef ::xsd::cxx::tree::optional< south_east_type > south_east_optional;
    typedef ::xsd::cxx::tree::traits< south_east_type, char > south_east_traits;

    const south_east_optional&
    south_east () const;

    south_east_optional&
    south_east ();

    void
    south_east (const south_east_type& x);

    void
    south_east (const south_east_optional& x);

    void
    south_east (::std::auto_ptr< south_east_type > p);

    // south-west
    //
    typedef ::xml_schema::string south_west_type;
    typedef ::xsd::cxx::tree::optional< south_west_type > south_west_optional;
    typedef ::xsd::cxx::tree::traits< south_west_type, char > south_west_traits;

    const south_west_optional&
    south_west () const;

    south_west_optional&
    south_west ();

    void
    south_west (const south_west_type& x);

    void
    south_west (const south_west_optional& x);

    void
    south_west (::std::auto_ptr< south_west_type > p);

    // east-north
    //
    typedef ::xml_schema::string east_north_type;
    typedef ::xsd::cxx::tree::optional< east_north_type > east_north_optional;
    typedef ::xsd::cxx::tree::traits< east_north_type, char > east_north_traits;

    const east_north_optional&
    east_north () const;

    east_north_optional&
    east_north ();

    void
    east_north (const east_north_type& x);

    void
    east_north (const east_north_optional& x);

    void
    east_north (::std::auto_ptr< east_north_type > p);

    // east-south
    //
    typedef ::xml_schema::string east_south_type;
    typedef ::xsd::cxx::tree::optional< east_south_type > east_south_optional;
    typedef ::xsd::cxx::tree::traits< east_south_type, char > east_south_traits;

    const east_south_optional&
    east_south () const;

    east_south_optional&
    east_south ();

    void
    east_south (const east_south_type& x);

    void
    east_south (const east_south_optional& x);

    void
    east_south (::std::auto_ptr< east_south_type > p);

    // west-north
    //
    typedef ::xml_schema::string west_north_type;
    typedef ::xsd::cxx::tree::optional< west_north_type > west_north_optional;
    typedef ::xsd::cxx::tree::traits< west_north_type, char > west_north_traits;

    const west_north_optional&
    west_north () const;

    west_north_optional&
    west_north ();

    void
    west_north (const west_north_type& x);

    void
    west_north (const west_north_optional& x);

    void
    west_north (::std::auto_ptr< west_north_type > p);

    // west-south
    //
    typedef ::xml_schema::string west_south_type;
    typedef ::xsd::cxx::tree::optional< west_south_type > west_south_optional;
    typedef ::xsd::cxx::tree::traits< west_south_type, char > west_south_traits;

    const west_south_optional&
    west_south () const;

    west_south_optional&
    west_south ();

    void
    west_south (const west_south_type& x);

    void
    west_south (const west_south_optional& x);

    void
    west_south (::std::auto_ptr< west_south_type > p);

    // floor
    //
    typedef ::xml_schema::string floor_type;
    typedef ::xsd::cxx::tree::optional< floor_type > floor_optional;
    typedef ::xsd::cxx::tree::traits< floor_type, char > floor_traits;

    const floor_optional&
    floor () const;

    floor_optional&
    floor ();

    void
    floor (const floor_type& x);

    void
    floor (const floor_optional& x);

    void
    floor (::std::auto_ptr< floor_type > p);

    // roof
    //
    typedef ::xml_schema::string roof_type;
    typedef ::xsd::cxx::tree::optional< roof_type > roof_optional;
    typedef ::xsd::cxx::tree::traits< roof_type, char > roof_traits;

    const roof_optional&
    roof () const;

    roof_optional&
    roof ();

    void
    roof (const roof_type& x);

    void
    roof (const roof_optional& x);

    void
    roof (::std::auto_ptr< roof_type > p);

    // teleport
    //
    typedef ::xml_schema::string teleport_type;
    typedef ::xsd::cxx::tree::optional< teleport_type > teleport_optional;
    typedef ::xsd::cxx::tree::traits< teleport_type, char > teleport_traits;

    const teleport_optional&
    teleport () const;

    teleport_optional&
    teleport ();

    void
    teleport (const teleport_type& x);

    void
    teleport (const teleport_optional& x);

    void
    teleport (::std::auto_ptr< teleport_type > p);

    // teleport2
    //
    typedef ::xml_schema::string teleport2_type;
    typedef ::xsd::cxx::tree::optional< teleport2_type > teleport2_optional;
    typedef ::xsd::cxx::tree::traits< teleport2_type, char > teleport2_traits;

    const teleport2_optional&
    teleport2 () const;

    teleport2_optional&
    teleport2 ();

    void
    teleport2 (const teleport2_type& x);

    void
    teleport2 (const teleport2_optional& x);

    void
    teleport2 (::std::auto_ptr< teleport2_type > p);

    // file
    //
    typedef ::xml_schema::string file_type;
    typedef ::xsd::cxx::tree::traits< file_type, char > file_traits;

    const file_type&
    file () const;

    file_type&
    file ();

    void
    file (const file_type& x);

    void
    file (::std::auto_ptr< file_type > p);

    // Constructors
    //
    room (const file_type&);

    room (const ::xercesc::DOMElement& e,
          ::xml_schema::flags f = 0,
          ::xml_schema::type* c = 0);

    room (const room& x,
          ::xml_schema::flags f = 0,
          ::xml_schema::type* c = 0);

    virtual room*
    _clone (::xml_schema::flags f = 0,
            ::xml_schema::type* c = 0) const;

    // Implementation
    //
    protected:
    void
    parse (::xsd::cxx::xml::dom::parser< char >&,
           ::xml_schema::flags);

    private:
    north_optional north_;
    south_optional south_;
    east_optional east_;
    west_optional west_;
    north_east_optional north_east_;
    north_west_optional north_west_;
    south_east_optional south_east_;
    south_west_optional south_west_;
    east_north_optional east_north_;
    east_south_optional east_south_;
    west_north_optional west_north_;
    west_south_optional west_south_;
    floor_optional floor_;
    roof_optional roof_;
    teleport_optional teleport_;
    teleport2_optional teleport2_;
    ::xsd::cxx::tree::one< file_type > file_;
  };
}

#include <iosfwd>

#include <xercesc/dom/DOMDocument.hpp>

# include <xercesc/dom/DOMLSInput.hpp>

namespace mxml
{
  // Parse a URI or a local file
  //

  ::std::auto_ptr< ::mxml::MapXML >
  map (const ::std::string& uri,
       ::xml_schema::flags f = 0,
       const ::xml_schema::properties& p = ::xml_schema::properties ());

  // Parse std::istream
  //

  ::std::auto_ptr< ::mxml::MapXML >
  map (::std::istream& is,
       ::xml_schema::flags f = 0,
       const ::xml_schema::properties& p = ::xml_schema::properties ());

  ::std::auto_ptr< ::mxml::MapXML >
  map (::std::istream& is,
       const ::std::string& id,
       ::xml_schema::flags f = 0,
       const ::xml_schema::properties& p = ::xml_schema::properties ());

  // Parse xercesc::DOMLSInput
  //

  ::std::auto_ptr< ::mxml::MapXML >
  map (const ::xercesc::DOMLSInput& is,
       ::xml_schema::flags f = 0,
       const ::xml_schema::properties& p = ::xml_schema::properties ());

  // Parse xercesc::DOMDocument
  //

  ::std::auto_ptr< ::mxml::MapXML >
  map (const ::xercesc::DOMDocument& d,
       ::xml_schema::flags f = 0,
       const ::xml_schema::properties& p = ::xml_schema::properties ());

  ::std::auto_ptr< ::mxml::MapXML >
  map (::xercesc::DOMDocument* d,
       ::xml_schema::flags f = 0,
       const ::xml_schema::properties& p = ::xml_schema::properties ());
}

#include <xsd/cxx/post.hxx>

#endif // MAP_XML_HPP
