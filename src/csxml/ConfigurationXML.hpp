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

#ifndef CONFIGURATION_XML_HPP
#define CONFIGURATION_XML_HPP

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

#include <xsd/cxx/tree/parsing.hxx>

#include <xsd/cxx/tree/serialization.hxx>
#include <xsd/cxx/xml/dom/serialization-header.hxx>

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

  // Namespace information. Used in serialization functions
  //
  typedef ::xsd::cxx::xml::dom::namespace_info < char > namespace_info;
  typedef ::xsd::cxx::xml::dom::namespace_infomap < char > namespace_infomap;

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
namespace cxml
{
  class ConfigurationXML;
  class keyboard;
  class volume;
}


#include <memory>    // std::auto_ptr
#include <algorithm> // std::binary_search

#include <xsd/cxx/tree/exceptions.hxx>
#include <xsd/cxx/tree/elements.hxx>
#include <xsd/cxx/tree/containers.hxx>
#include <xsd/cxx/tree/list.hxx>

#include <xsd/cxx/xml/dom/parsing-header.hxx>

namespace cxml
{
  class ConfigurationXML: public ::xml_schema::type
  {
    public:
    // language
    //
    typedef ::xml_schema::string language_type;
    typedef ::xsd::cxx::tree::traits< language_type, char > language_traits;

    const language_type&
    language () const;

    language_type&
    language ();

    void
    language (const language_type& x);

    void
    language (::std::auto_ptr< language_type > p);

    // keyboard
    //
    typedef ::cxml::keyboard keyboard_type;
    typedef ::xsd::cxx::tree::traits< keyboard_type, char > keyboard_traits;

    const keyboard_type&
    keyboard () const;

    keyboard_type&
    keyboard ();

    void
    keyboard (const keyboard_type& x);

    void
    keyboard (::std::auto_ptr< keyboard_type > p);

    // volume
    //
    typedef ::cxml::volume volume_type;
    typedef ::xsd::cxx::tree::traits< volume_type, char > volume_traits;

    const volume_type&
    volume () const;

    volume_type&
    volume ();

    void
    volume (const volume_type& x);

    void
    volume (::std::auto_ptr< volume_type > p);

    // Constructors
    //
    ConfigurationXML (const language_type&,
                      const keyboard_type&,
                      const volume_type&);

    ConfigurationXML (const ::xercesc::DOMElement& e,
                      ::xml_schema::flags f = 0,
                      ::xml_schema::type* c = 0);

    ConfigurationXML (const ConfigurationXML& x,
                      ::xml_schema::flags f = 0,
                      ::xml_schema::type* c = 0);

    virtual ConfigurationXML*
    _clone (::xml_schema::flags f = 0,
            ::xml_schema::type* c = 0) const;

    // Implementation
    //
    protected:
    void
    parse (::xsd::cxx::xml::dom::parser< char >&,
           ::xml_schema::flags);

    private:
    ::xsd::cxx::tree::one< language_type > language_;
    ::xsd::cxx::tree::one< keyboard_type > keyboard_;
    ::xsd::cxx::tree::one< volume_type > volume_;
  };

  class keyboard: public ::xml_schema::type
  {
    public:
    // left
    //
    typedef ::xml_schema::int_ left_type;
    typedef ::xsd::cxx::tree::traits< left_type, char > left_traits;

    const left_type&
    left () const;

    left_type&
    left ();

    void
    left (const left_type& x);

    // right
    //
    typedef ::xml_schema::int_ right_type;
    typedef ::xsd::cxx::tree::traits< right_type, char > right_traits;

    const right_type&
    right () const;

    right_type&
    right ();

    void
    right (const right_type& x);

    // up
    //
    typedef ::xml_schema::int_ up_type;
    typedef ::xsd::cxx::tree::traits< up_type, char > up_traits;

    const up_type&
    up () const;

    up_type&
    up ();

    void
    up (const up_type& x);

    // down
    //
    typedef ::xml_schema::int_ down_type;
    typedef ::xsd::cxx::tree::traits< down_type, char > down_traits;

    const down_type&
    down () const;

    down_type&
    down ();

    void
    down (const down_type& x);

    // take
    //
    typedef ::xml_schema::int_ take_type;
    typedef ::xsd::cxx::tree::traits< take_type, char > take_traits;

    const take_type&
    take () const;

    take_type&
    take ();

    void
    take (const take_type& x);

    // jump
    //
    typedef ::xml_schema::int_ jump_type;
    typedef ::xsd::cxx::tree::traits< jump_type, char > jump_traits;

    const jump_type&
    jump () const;

    jump_type&
    jump ();

    void
    jump (const jump_type& x);

    // shoot
    //
    typedef ::xml_schema::int_ shoot_type;
    typedef ::xsd::cxx::tree::traits< shoot_type, char > shoot_traits;

    const shoot_type&
    shoot () const;

    shoot_type&
    shoot ();

    void
    shoot (const shoot_type& x);

    // takeandjump
    //
    typedef ::xml_schema::int_ takeandjump_type;
    typedef ::xsd::cxx::tree::traits< takeandjump_type, char > takeandjump_traits;

    const takeandjump_type&
    takeandjump () const;

    takeandjump_type&
    takeandjump ();

    void
    takeandjump (const takeandjump_type& x);

    // swap
    //
    typedef ::xml_schema::int_ swap_type;
    typedef ::xsd::cxx::tree::traits< swap_type, char > swap_traits;

    const swap_type&
    swap () const;

    swap_type&
    swap ();

    void
    swap (const swap_type& x);

    // halt
    //
    typedef ::xml_schema::int_ halt_type;
    typedef ::xsd::cxx::tree::traits< halt_type, char > halt_traits;

    const halt_type&
    halt () const;

    halt_type&
    halt ();

    void
    halt (const halt_type& x);

    // Constructors
    //
    keyboard (const left_type&,
              const right_type&,
              const up_type&,
              const down_type&,
              const take_type&,
              const jump_type&,
              const shoot_type&,
              const takeandjump_type&,
              const swap_type&,
              const halt_type&);

    keyboard (const ::xercesc::DOMElement& e,
              ::xml_schema::flags f = 0,
              ::xml_schema::type* c = 0);

    keyboard (const keyboard& x,
              ::xml_schema::flags f = 0,
              ::xml_schema::type* c = 0);

    virtual keyboard*
    _clone (::xml_schema::flags f = 0,
            ::xml_schema::type* c = 0) const;

    // Implementation
    //
    protected:
    void
    parse (::xsd::cxx::xml::dom::parser< char >&,
           ::xml_schema::flags);

    private:
    ::xsd::cxx::tree::one< left_type > left_;
    ::xsd::cxx::tree::one< right_type > right_;
    ::xsd::cxx::tree::one< up_type > up_;
    ::xsd::cxx::tree::one< down_type > down_;
    ::xsd::cxx::tree::one< take_type > take_;
    ::xsd::cxx::tree::one< jump_type > jump_;
    ::xsd::cxx::tree::one< shoot_type > shoot_;
    ::xsd::cxx::tree::one< takeandjump_type > takeandjump_;
    ::xsd::cxx::tree::one< swap_type > swap_;
    ::xsd::cxx::tree::one< halt_type > halt_;
  };

  class volume: public ::xml_schema::type
  {
    public:
    // fx
    //
    typedef ::xml_schema::int_ fx_type;
    typedef ::xsd::cxx::tree::traits< fx_type, char > fx_traits;

    const fx_type&
    fx () const;

    fx_type&
    fx ();

    void
    fx (const fx_type& x);

    // music
    //
    typedef ::xml_schema::int_ music_type;
    typedef ::xsd::cxx::tree::traits< music_type, char > music_traits;

    const music_type&
    music () const;

    music_type&
    music ();

    void
    music (const music_type& x);

    // Constructors
    //
    volume (const fx_type&,
            const music_type&);

    volume (const ::xercesc::DOMElement& e,
            ::xml_schema::flags f = 0,
            ::xml_schema::type* c = 0);

    volume (const volume& x,
            ::xml_schema::flags f = 0,
            ::xml_schema::type* c = 0);

    virtual volume*
    _clone (::xml_schema::flags f = 0,
            ::xml_schema::type* c = 0) const;

    // Implementation
    //
    protected:
    void
    parse (::xsd::cxx::xml::dom::parser< char >&,
           ::xml_schema::flags);

    private:
    ::xsd::cxx::tree::one< fx_type > fx_;
    ::xsd::cxx::tree::one< music_type > music_;
  };
}

#include <iosfwd>

#include <xercesc/dom/DOMDocument.hpp>

# include <xercesc/dom/DOMLSInput.hpp>

namespace cxml
{
  // Parse a URI or a local file
  //

  ::std::auto_ptr< ::cxml::ConfigurationXML >
  configuration (const ::std::string& uri,
                 ::xml_schema::flags f = 0,
                 const ::xml_schema::properties& p = ::xml_schema::properties ());

  // Parse std::istream
  //

  ::std::auto_ptr< ::cxml::ConfigurationXML >
  configuration (::std::istream& is,
                 ::xml_schema::flags f = 0,
                 const ::xml_schema::properties& p = ::xml_schema::properties ());

  ::std::auto_ptr< ::cxml::ConfigurationXML >
  configuration (::std::istream& is,
                 const ::std::string& id,
                 ::xml_schema::flags f = 0,
                 const ::xml_schema::properties& p = ::xml_schema::properties ());

  // Parse xercesc::DOMLSInput
  //

  ::std::auto_ptr< ::cxml::ConfigurationXML >
  configuration (const ::xercesc::DOMLSInput& is,
                 ::xml_schema::flags f = 0,
                 const ::xml_schema::properties& p = ::xml_schema::properties ());

  // Parse xercesc::DOMDocument
  //

  ::std::auto_ptr< ::cxml::ConfigurationXML >
  configuration (const ::xercesc::DOMDocument& d,
                 ::xml_schema::flags f = 0,
                 const ::xml_schema::properties& p = ::xml_schema::properties ());

  ::std::auto_ptr< ::cxml::ConfigurationXML >
  configuration (::xercesc::DOMDocument* d,
                 ::xml_schema::flags f = 0,
                 const ::xml_schema::properties& p = ::xml_schema::properties ());
}

#include <iosfwd>

#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/framework/XMLFormatter.hpp>

#include <xsd/cxx/xml/dom/auto-ptr.hxx>

namespace cxml
{
  // Serialize to std::ostream
  //

  void
  configuration (::std::ostream& os,
                 const ::cxml::ConfigurationXML& x,
                 const ::xml_schema::namespace_infomap& m,
                 const ::std::string& e = "UTF-8",
                 ::xml_schema::flags f = 0);

  // Serialize to xercesc::XMLFormatTarget
  //

  void
  configuration (::xercesc::XMLFormatTarget& ft,
                 const ::cxml::ConfigurationXML& x,
                 const ::xml_schema::namespace_infomap& m,
                 const ::std::string& e = "UTF-8",
                 ::xml_schema::flags f = 0);

  // Serialize to an existing xercesc::DOMDocument
  //

  void
  configuration (::xercesc::DOMDocument& d,
                 const ::cxml::ConfigurationXML& x,
                 ::xml_schema::flags f = 0);

  // Serialize to a new xercesc::DOMDocument
  //

  ::xsd::cxx::xml::dom::auto_ptr< ::xercesc::DOMDocument >
  configuration (const ::cxml::ConfigurationXML& x,
                 const ::xml_schema::namespace_infomap& m,
                 ::xml_schema::flags f = 0);

  void
  operator<< (::xercesc::DOMElement&, const ConfigurationXML&);

  void
  operator<< (::xercesc::DOMElement&, const keyboard&);

  void
  operator<< (::xercesc::DOMElement&, const volume&);
}

#include <xsd/cxx/post.hxx>

#endif // CONFIGURATION_XML_HPP
