#ifndef RBX_BUILTIN_IMMEDIATES_HPP
#define RBX_BUILTIN_IMMEDIATES_HPP

#include "builtin/object.hpp"
#include "type_info.hpp"

namespace rubinius {
  class NilClass : public Object {
  public:
    static const object_type type = NilType;

    class Info : public TypeInfo {
    public:
      Info(object_type type) : TypeInfo(type) { }
      virtual void mark(OBJECT t, ObjectMark& mark);
    };
  };

  class TrueClass : public Object {
  public:
    static const object_type type = TrueType;

    class Info : public TypeInfo {
    public:
      Info(object_type type) : TypeInfo(type) { }
      virtual void mark(OBJECT t, ObjectMark& mark);
    };
  };

  class FalseClass : public Object {
  public:
    static const object_type type = FalseType;

    class Info : public TypeInfo {
    public:
      Info(object_type type) : TypeInfo(type) { }
      virtual void mark(OBJECT t, ObjectMark& mark);
    };
  };
}

#endif
