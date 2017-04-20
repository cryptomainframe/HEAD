// Generated by gencpp from file performances/SpeechOnResponse.msg
// DO NOT EDIT!


#ifndef PERFORMANCES_MESSAGE_SPEECHONRESPONSE_H
#define PERFORMANCES_MESSAGE_SPEECHONRESPONSE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace performances
{
template <class ContainerAllocator>
struct SpeechOnResponse_
{
  typedef SpeechOnResponse_<ContainerAllocator> Type;

  SpeechOnResponse_()
    : success(false)  {
    }
  SpeechOnResponse_(const ContainerAllocator& _alloc)
    : success(false)  {
  (void)_alloc;
    }



   typedef uint8_t _success_type;
  _success_type success;




  typedef boost::shared_ptr< ::performances::SpeechOnResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::performances::SpeechOnResponse_<ContainerAllocator> const> ConstPtr;

}; // struct SpeechOnResponse_

typedef ::performances::SpeechOnResponse_<std::allocator<void> > SpeechOnResponse;

typedef boost::shared_ptr< ::performances::SpeechOnResponse > SpeechOnResponsePtr;
typedef boost::shared_ptr< ::performances::SpeechOnResponse const> SpeechOnResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::performances::SpeechOnResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::performances::SpeechOnResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace performances

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'performances': ['/home/icog-labs/hansonrobotics/HEAD/src/performances/msg'], 'std_msgs': ['/opt/ros/indigo/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::performances::SpeechOnResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::performances::SpeechOnResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::performances::SpeechOnResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::performances::SpeechOnResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::performances::SpeechOnResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::performances::SpeechOnResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::performances::SpeechOnResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "358e233cde0c8a8bcfea4ce193f8fc15";
  }

  static const char* value(const ::performances::SpeechOnResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x358e233cde0c8a8bULL;
  static const uint64_t static_value2 = 0xcfea4ce193f8fc15ULL;
};

template<class ContainerAllocator>
struct DataType< ::performances::SpeechOnResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "performances/SpeechOnResponse";
  }

  static const char* value(const ::performances::SpeechOnResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::performances::SpeechOnResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "bool success\n\
";
  }

  static const char* value(const ::performances::SpeechOnResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::performances::SpeechOnResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.success);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct SpeechOnResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::performances::SpeechOnResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::performances::SpeechOnResponse_<ContainerAllocator>& v)
  {
    s << indent << "success: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.success);
  }
};

} // namespace message_operations
} // namespace ros

#endif // PERFORMANCES_MESSAGE_SPEECHONRESPONSE_H