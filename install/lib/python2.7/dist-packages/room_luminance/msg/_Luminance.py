# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from room_luminance/Luminance.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class Luminance(genpy.Message):
  _md5sum = "808071152779e2b1174c938d5216ce43"
  _type = "room_luminance/Luminance"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """int8 covered
int8 sudden_change
string room_light
float32 value
float32 perc_covered
"""
  __slots__ = ['covered','sudden_change','room_light','value','perc_covered']
  _slot_types = ['int8','int8','string','float32','float32']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       covered,sudden_change,room_light,value,perc_covered

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(Luminance, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.covered is None:
        self.covered = 0
      if self.sudden_change is None:
        self.sudden_change = 0
      if self.room_light is None:
        self.room_light = ''
      if self.value is None:
        self.value = 0.
      if self.perc_covered is None:
        self.perc_covered = 0.
    else:
      self.covered = 0
      self.sudden_change = 0
      self.room_light = ''
      self.value = 0.
      self.perc_covered = 0.

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      _x = self
      buff.write(_struct_2b.pack(_x.covered, _x.sudden_change))
      _x = self.room_light
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      if python3:
        buff.write(struct.pack('<I%sB'%length, length, *_x))
      else:
        buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_struct_2f.pack(_x.value, _x.perc_covered))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      end = 0
      _x = self
      start = end
      end += 2
      (_x.covered, _x.sudden_change,) = _struct_2b.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.room_light = str[start:end].decode('utf-8')
      else:
        self.room_light = str[start:end]
      _x = self
      start = end
      end += 8
      (_x.value, _x.perc_covered,) = _struct_2f.unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      _x = self
      buff.write(_struct_2b.pack(_x.covered, _x.sudden_change))
      _x = self.room_light
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      if python3:
        buff.write(struct.pack('<I%sB'%length, length, *_x))
      else:
        buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_struct_2f.pack(_x.value, _x.perc_covered))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      end = 0
      _x = self
      start = end
      end += 2
      (_x.covered, _x.sudden_change,) = _struct_2b.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.room_light = str[start:end].decode('utf-8')
      else:
        self.room_light = str[start:end]
      _x = self
      start = end
      end += 8
      (_x.value, _x.perc_covered,) = _struct_2f.unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_2f = struct.Struct("<2f")
_struct_2b = struct.Struct("<2b")