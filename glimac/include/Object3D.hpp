#ifndef OBJECT3D_HPP
#define OBJECT3D_HPP

namespace glimac
{

class Object3D
{
public:
  virtual GLint getSizeOfVertex() = 0;
  virtual GLenum getPrimitive() = 0;


};

} // namespace glimac

#endif // OBJECT3D_HPP
