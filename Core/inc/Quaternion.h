////////////////////////////////////////////////////////////
/** @file Quaternion.h
 *  @ingroup Maths
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 09/09/2013
 *
 *  Defines the Quaternion class.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APRO_QUATERNION_H
#define APRO_QUATERNION_H

#include "Platform.h"

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class Quaternion
     *  @ingroup Maths
     *  @brief Represents a rotation or an orientation of a 3D
     *  object in space.
     *
     *  @see http://en.wikipedia.org/wiki/Quaternion
    **/
    ////////////////////////////////////////////////////////////
    class Quaternion
    {
    public:

        Real m_x; ///< The factor of i.
        Real m_y; ///< The factor of j.
        Real m_z; ///< The factor of k.
        Real m_w; ///< The scalar part, also referred as 'r'.

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Default constructor.
         *
         *  This constructor doesn't initialize anything so value
         *  x, y, z and w are not guarenteed to be 0.
        **/
        ////////////////////////////////////////////////////////////
        Quaternion() {}

        ////////////////////////////////////////////////////////////
        /** @brief Constructs a quaternion with each members.
         *  @note Quaternion is not normalized, this has to be done
         *  manually.
        **/
        ////////////////////////////////////////////////////////////
        Quaternion(Real x, Real y, Real z, Real w);

        ////////////////////////////////////////////////////////////
        /** @brief Constructs a quaternion with each members contained
         *  in a C-style array.
         *  @note Quaternion is not normalized, this has to be done
         *  manually.
        **/
        ////////////////////////////////////////////////////////////
        Quaternion(const Real* data);

        ////////////////////////////////////////////////////////////
        /** @brief Constructs a quaternion by specifying a rotation
         *  axis and the amount of rotation to be performed about that
         *  axis.
         *
         *  @param rotationAxis : The normalized rotation axis to rotate
         *  about.
         *  @param rotationAngleRadians : The angle to rotate by, in
         *  radians. For example, Pi/4.f equals to 45 degrees, Pi/2.f
         *  is 90 degrees, and Pi is 180 degrees.
        **/
        ////////////////////////////////////////////////////////////
        Quaternion(const Vector3& rotationAxis, Real rotationAngle);

        ////////////////////////////////////////////////////////////
        /** @brief Constructs a quaternion from 3 orthonomal
         *  axes.
         *
         *  This axes must be orthogonals, and normalized.
        **/
        ////////////////////////////////////////////////////////////
        Quaternion(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis);

        ////////////////////////////////////////////////////////////
        /** @brief Constructs a quaternion from 3 orthonomal
         *  axes.
         *
         *  These axes must be orthogonals, and normalized.
         *
         *  @param axes : A pointer to an array of 3 vectors.
        **/
        ////////////////////////////////////////////////////////////
        Quaternion(const Vector3* axes);

        ////////////////////////////////////////////////////////////
        /** @brief Constructs a quaternion from a 3x3 rotation Matrix.
        **/
        ////////////////////////////////////////////////////////////
        Quaternion(const Matrix3x3& rotationMatrix);

        ////////////////////////////////////////////////////////////
        /** @brief Constructs a quaternion from a 3x4 rotation Matrix.
        **/
        ////////////////////////////////////////////////////////////
        Quaternion(const Matrix3x4& rotationMatrix);

        ////////////////////////////////////////////////////////////
        /** @brief Constructs a quaternion from a 4x4 rotation Matrix.
        **/
        ////////////////////////////////////////////////////////////
        Quaternion(const Matrix4x4& rotationMatrix);

        ////////////////////////////////////////////////////////////
        /** @brief Constructs a quaternion by copying given one.
        **/
        ////////////////////////////////////////////////////////////
        Quaternion(const Quaternion& other);

        ////////////////////////////////////////////////////////////
        /** @brief Destructs the quaternion.
        **/
        ////////////////////////////////////////////////////////////
        ~Quaternion() {}

    public: // Access and others

        ////////////////////////////////////////////////////////////
        /** @brief Returns the factor of i of this quaternion.
        **/
        ////////////////////////////////////////////////////////////
        Real& getX() { return m_x; }
        const Real& getX() const { return m_x; }

        ////////////////////////////////////////////////////////////
        /** @brief Returns the factor of j of this quaternion.
        **/
        ////////////////////////////////////////////////////////////
        Real& getY() { return m_y; }
        const Real& getY() const { return m_y; }

        ////////////////////////////////////////////////////////////
        /** @brief Returns the factor of k of this quaternion.
        **/
        ////////////////////////////////////////////////////////////
        Real& getZ() { return m_z; }
        const Real& getZ() const { return m_z; }

        ////////////////////////////////////////////////////////////
        /** @brief Returns the scalar part of this quaternion.
        **/
        ////////////////////////////////////////////////////////////
        Real& getW() { return m_w; }
        const Real& getW() const { return m_z; }

        ////////////////////////////////////////////////////////////
        /** @brief Returns the local +X axis in the post-transformed
         *  coordinate space.
         *
         *  This is the same as transforming the vector (1,0,0) by
         *  this quaternion.
         *
         *  @return The X orthonormal axis defining the quaternion.
         *  @see localY(), localZ()
        **/
        ////////////////////////////////////////////////////////////
        Vector3 localX() const;

        ////////////////////////////////////////////////////////////
        /** @brief Returns the local +Y axis in the post-transformed
         *  coordinate space.
         *
         *  This is the same as transforming the vector (0,1,0) by
         *  this quaternion.
         *
         *  @return The Y orthonormal axis defining the quaternion.
         *  @see localX(), localZ()
        **/
        ////////////////////////////////////////////////////////////
        Vector3 localY() const;

        ////////////////////////////////////////////////////////////
        /** @brief Returns the local +Z axis in the post-transformed
         *  coordinate space.
         *
         *  This is the same as transforming the vector (0,0,1) by
         *  this quaternion.
         *
         *  @return The Z orthonormal axis defining the quaternion.
         *  @see localX(), localY()
        **/
        ////////////////////////////////////////////////////////////
        Vector3 localZ() const;

        ////////////////////////////////////////////////////////////
        /** @brief Calculate the local roll element of this quaternion.
         *
         *  @param reprojectAxis : By default the method returns the
         *  'intuitive' result that is, if you projected the local Y of
         *  the quaternion onto the X and Y axes, the angle between them
         *  is returned. If set to false though, the result is the actual
         *  yaw that will be used to implement the quaternion, which is the
         *  shortest possible path to get to the same orientation and may
         *  involve less axial rotation.
         *
         *  @note The co-domain of the returned value is from -180 to 180
         *  degrees.
         *
         *  @see getPitch(), getYaw()
        **/
        ////////////////////////////////////////////////////////////
        Radian getRoll(bool reprojectAxis = true) const;

        ////////////////////////////////////////////////////////////
        /** @brief Calculate the local roll element of this quaternion.
         *
         *  @param reprojectAxis : By default the method returns the
         *  'intuitive' result that is, if you projected the local Z of
         *  the quaternion onto the X and Y axes, the angle between them
         *  is returned. If set to false though, the result is the actual
         *  yaw that will be used to implement the quaternion, which is the
         *  shortest possible path to get to the same orientation and may
         *  involve less axial rotation.
         *
         *  @note The co-domain of the returned value is from -180 to 180
         *  degrees.
         *
         *  @see getRoll(), getYaw()
        **/
        ////////////////////////////////////////////////////////////
        Radian getPitch(bool reprojectAxis = true) const;

        ////////////////////////////////////////////////////////////
        /** @brief Calculate the local roll element of this quaternion.
         *
         *  @param reprojectAxis : By default the method returns the
         *  'intuitive' result that is, if you projected the local Y of
         *  the quaternion onto the X and Z axes, the angle between them
         *  is returned. If set to false though, the result is the actual
         *  yaw that will be used to implement the quaternion, which is the
         *  shortest possible path to get to the same orientation and may
         *  involve less axial rotation.
         *
         *  @note The co-domain of the returned value is from -180 to 180
         *  degrees.
         *
         *  @see getRoll(), getPitch()
        **/
        ////////////////////////////////////////////////////////////
        Radian getYaw(bool reprojectAxis = true) const;

        ////////////////////////////////////////////////////////////
        /** @brief Returns the axis of rotation of this quaternion.
        **/
        ////////////////////////////////////////////////////////////
        Vector3 getAxis() const;

        ////////////////////////////////////////////////////////////
        /** @brief Returns the angle of rotation of this quaternion,
         *  in radians.
        **/
        ////////////////////////////////////////////////////////////
        Radian getAngle() const;

        ////////////////////////////////////////////////////////////
        /** @brief Returns the lenght of the 4 quaternion entries.
        **/
        ////////////////////////////////////////////////////////////
        Real lenght() const;

        ////////////////////////////////////////////////////////////
        /** @brief Returns the squared lenght of the 4 quaternion
         *  entries.
        **/
        ////////////////////////////////////////////////////////////
        Real squaredLenght() const;

        ////////////////////////////////////////////////////////////
        /** @brief Returns the dot product of this quaternion.
        **/
        ////////////////////////////////////////////////////////////
        Real dot(const Quaternion& other) const;

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Normalize this quaternion, in-place and returns
         *  the old lenght.
         *
         *  @see inverseAndNormalize(), normalized()
        **/
        ////////////////////////////////////////////////////////////
        Real normalize();

        ////////////////////////////////////////////////////////////
        /** @brief Returns a normalized copy of this quaternion.
         *
         *  @see inverseAndNormalize(), normalize()
        **/
        ////////////////////////////////////////////////////////////
        Quaternion normalized() const;

        ////////////////////////////////////////////////////////////
        /** @brief Inverse this quaternion.
         *
         *  @see inverseAndNormalize(), inversed()
        **/
        ////////////////////////////////////////////////////////////
        void inverse() { conjugate(); }

        ////////////////////////////////////////////////////////////
        /** @brief Returns an inversed copy of this quaternion.
         *
         *  @see inverseAndNormalize(), inverse()
        **/
        ////////////////////////////////////////////////////////////
        Quaternion inversed() const { return conjugated(); }

        ////////////////////////////////////////////////////////////
        /** @brief Computes the conjugate of this quaternion.
         *
         *  @see conjugated()
        **/
        ////////////////////////////////////////////////////////////
        void conjugate();

        ////////////////////////////////////////////////////////////
        /** @brief Returns the conjugate of this quaternion.
         *
         *  @see conjugate()
        **/
        ////////////////////////////////////////////////////////////
        Quaternion conjugated() const;

        ////////////////////////////////////////////////////////////
        /** @brief Inverse and normalize this quaternion.
         *
         *  @see inversedAndNormalized()
        **/
        ////////////////////////////////////////////////////////////
        Real inverseAndNormalize();

        ////////////////////////////////////////////////////////////
        /** @brief Return the inversed and normalized copy of this
         *  quaternion.
         *
         *  @see inversedAndNormalized()
        **/
        ////////////////////////////////////////////////////////////
        Quaternion inversedAndNormalized() const;

    public: // Set

        ////////////////////////////////////////////////////////////
        /** @brief Sets this quaternion by specifying the axis about
         *  which the rotation is performed, and the angle of rotation.
         *
         *  @param axis : The axis of the rotation. This vector must be
         *  normalized.
         *  @param angle : The rotation angle in Radians.
        **/
        ////////////////////////////////////////////////////////////
        void setFromAxisAngle(const Vector3& axis, const Radian& angle);

        ////////////////////////////////////////////////////////////
        /** @brief Returns the rotation axis and angle of this quaternion.
         *
         *  @param axis : [out] The axis of the rotation. This vector is
         *  returned normalized.
         *  @param angle : [out] The rotation angle in Radians.
        **/
        ////////////////////////////////////////////////////////////
        void toAxisAngle(Vector3& axis, Radian& angle) const;

        ////////////////////////////////////////////////////////////
        /** @brief Constructs the quaternion using 3 axes.
         *
         *  This axes must be orthonormal.
        **/
        ////////////////////////////////////////////////////////////
        void setFromAxes(const Vector3* axes);

        ////////////////////////////////////////////////////////////
        /** @brief Constructs the quaternion using 3 axes.
         *
         *  This axes must be orthonormal.
        **/
        ////////////////////////////////////////////////////////////
        void setFromAxes(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis);

        ////////////////////////////////////////////////////////////
        /** @brief Returns the 3 orthonormal axes defining the quaternion.
        **/
        ////////////////////////////////////////////////////////////
        void toAxes(Vector3* axes) const;

        ////////////////////////////////////////////////////////////
        /** @brief Returns the 3 orthonormal axes defining the quaternion.
        **/
        ////////////////////////////////////////////////////////////
        void toAxes(Vector3& xAxis, Vector3& yAxis, Vector3& zAxis) const;

        ////////////////////////////////////////////////////////////
        /** @brief Set this quaternion to represent the same rotation
         *  as the given matrix.
        **/
        ////////////////////////////////////////////////////////////
        void setFromRotationMatrix(const Matrix3x3& m);

        ////////////////////////////////////////////////////////////
        /** @brief Set this quaternion to represent the same rotation
         *  as the given matrix.
        **/
        ////////////////////////////////////////////////////////////
        void setFromRotationMatrix(const Matrix3x4& m);

        ////////////////////////////////////////////////////////////
        /** @brief Set this quaternion to represent the same rotation
         *  as the given matrix.
        **/
        ////////////////////////////////////////////////////////////
        void setFromRotationMatrix(const Matrix4x4& m);

        ////////////////////////////////////////////////////////////
        /** @brief Construct a 3x3 rotation Matrix from this quaternion.
        **/
        ////////////////////////////////////////////////////////////
        void toRotationMatrix(Matrix3x3& m) const;

        ////////////////////////////////////////////////////////////
        /** @brief Construct a 3x4 rotation Matrix from this quaternion.
        **/
        ////////////////////////////////////////////////////////////
        void toRotationMatrix(Matrix3x4& m) const;

        ////////////////////////////////////////////////////////////
        /** @brief Construct a 4x4 rotation Matrix from this quaternion.
        **/
        ////////////////////////////////////////////////////////////
        void toRotationMatrix(Matrix4x4& m) const;

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Returns a pointer to the first entry (m_x).
        **/
        ////////////////////////////////////////////////////////////
        Real* ptr() { return &m_x; }

        ////////////////////////////////////////////////////////////
        /** @brief Returns a pointer to the first entry (m_x).
        **/
        ////////////////////////////////////////////////////////////
        const Real* ptr() { return &m_x; }

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Tell if this quaternion is normalized.
        **/
        ////////////////////////////////////////////////////////////
        bool isNormalized(Real epsilon = 1e-3f) const;

        ////////////////////////////////////////////////////////////
        /** @brief Tell if this quaternion is invertible.
        **/
        ////////////////////////////////////////////////////////////
        bool isInvertible(Real epsilon = 1e-3f) const;

        ////////////////////////////////////////////////////////////
        /** @brief Tell if this quaternion is finite.
        **/
        ////////////////////////////////////////////////////////////
        bool isFinite() const;

        ////////////////////////////////////////////////////////////
        /** @brief Tell if this quaternion is equals to the other given.
        **/
        ////////////////////////////////////////////////////////////
        bool equals(const Quaternion& other, Real epsilon = 1e-3f) const;

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Returns a negated copy of this quaternion.
        **/
        ////////////////////////////////////////////////////////////
        Quaternion negated() const;
        Quaternion operator - () const
        {
            return negated();
        }

        ////////////////////////////////////////////////////////////
        /** @brief Add this quaternion to given one.
        **/
        ////////////////////////////////////////////////////////////
        Quaternion& add(const Quaternion& other);
        Quaternion& operator += (const Quaternion& other)
        {
            return add(other);
        }

        ////////////////////////////////////////////////////////////
        /** @brief Add a copy this quaternion to given one.
        **/
        ////////////////////////////////////////////////////////////
        Quaternion added(const Quaternion& other) const;
        Quaternion operator + (const Quaternion& other) const
        {
            return added(other);
        }

        ////////////////////////////////////////////////////////////
        /** @brief Substract this quaternion to given one.
        **/
        ////////////////////////////////////////////////////////////
        Quaternion& substract(const Quaternion& other);
        Quaternion& operator -= (const Quaternion& other)
        {
            return substract(other);
        }

        ////////////////////////////////////////////////////////////
        /** @brief Substract a copy of this quaternion to given one.
        **/
        ////////////////////////////////////////////////////////////
        Quaternion substracted(const Quaternion& other) const;
        Quaternion operator - (const Quaternion& other) const
        {
            return substracted(other);
        }

        ////////////////////////////////////////////////////////////
        /** @brief Multiply this quaternion with given one.
        **/
        ////////////////////////////////////////////////////////////
        Quaternion& multiply(const Quaternion& other);
        Quaternion& operator *= (const Quaternion& other)
        {
            return multiply(other);
        }

        ////////////////////////////////////////////////////////////
        /** @brief Multiply a copy of this quaternion with given one.
        **/
        ////////////////////////////////////////////////////////////
        Quaternion multiplied(const Quaternion& other) const;
        Quaternion operator * (const Quaternion& other) const
        {
            return multiplied(other);
        }

        ////////////////////////////////////////////////////////////
        /** @brief Multiply this quaternion with a scalar.
        **/
        ////////////////////////////////////////////////////////////
        Quaternion& multiply(const Real& scalar);
        Quaternion& operator *= (const Real& scalar)
        {
            return multiply(scalar);
        }

        ////////////////////////////////////////////////////////////
        /** @brief Multiply a copy of this quaternion with a scalar.
        **/
        ////////////////////////////////////////////////////////////
        Quaternion multiplied(const Real& scalar) const;
        Quaternion operator * (const Real& scalar) const
        {
            return multiplied(scalar);
        }
        APRO_DLL friend Quaternion operator * (const Real& scalar, const Quaternion& other)
        {
            return other * scalar;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Divide a copy of this quaternion with a quaternion.
         *
         *  Division "a / b" results in a quaternion that rotates the
         *  orientation b to coincide with the orientation a.
        **/
        ////////////////////////////////////////////////////////////
        Quaternion divided(const Quaternion& r) const;
        Quaternion operator / (const Quaternion& q) const
        {
            return divided(q);
        }


    public:

        ////////////////////////////////////////////////////////////
        /** @brief Returns a copy of this vector rotated by this
         *  quaternion.
        **/
        ////////////////////////////////////////////////////////////
        Vector3 transformed(const Real& x, const Real& y, const Real& z) const;

        ////////////////////////////////////////////////////////////
        /** @brief Returns a copy of this vector rotated by this
         *  quaternion.
        **/
        ////////////////////////////////////////////////////////////
        Vector3 transformed(const Vector3& other) const;
        Vector3 operator * (const Vector3& other) const
        {
            return transformed(other);
        }

        ////////////////////////////////////////////////////////////
        /** @brief Rotate given vector by this quaternion.
        **/
        ////////////////////////////////////////////////////////////
        void transform(Vector3& vec) const;

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Linearly interpolates between this and the Quaternion
         *  target.
         *
         *  @param target : The target Quaternion.
         *  @param t : The interpolation weight, in range [0, 1].
         *
         *  @return (b, 0) returns this Quaternion, (b, 1) returns b.
        **/
        ////////////////////////////////////////////////////////////
        Quaternion linearInterpolate(const Quaternion& target, Real t) const;
        static Quaternion LinearInterpolation(const Quaternion& source, const Quaternion& target, Real t)
        {
            return source.linearInterpolate(target, t);
        }

        ////////////////////////////////////////////////////////////
        /** @brief Spherically interpolates between this and the Quaternion
         *  target.
         *
         *  @param target : The target Quaternion.
         *  @param t : The interpolation weight, in range [0, 1].
         *
         *  @return (b, 0) returns this Quaternion, (b, 1) returns b.
        **/
        ////////////////////////////////////////////////////////////
        Quaternion sphericalInterpolate(const Quaternion& target, Real t, bool shortestPath = false) const;
        static Quaternion SphericalInterpolation(const Quaternion& source, const Quaternion& target, Real t, bool shortestPath = false)
        {
            return source.sphericalInterpolate(target, t, shortestPath);
        }

        ////////////////////////////////////////////////////////////
        /** @brief Returns the 'from' vector rotated towards the 'to'
         *  vector by the given normalized time parameter.
         *
         *  This function slerps the given 'from' vector towards the
         *  'to' vector.
         *
         *  @param from : A normalized direction vector specifying the
         *  direction of rotation at t=0.
		 *  @param to : A normalized direction vector specifying the
		 *  direction of rotation at t=1.
		 *  @param t : The interpolation time parameter, in the range
		 *  [0,1]. Input values outside this range are silently clamped
		 *  to the [0, 1] interval.
		 *
		 *  @return A spherical linear interpolation of the vector 'from'
		 *  towards the vector 'to'.
        **/
        ////////////////////////////////////////////////////////////
        static Vector3 SlerpVector(const Vector3& from, const Vector3& to, Real t);

        ////////////////////////////////////////////////////////////
        /** @brief Returns the 'from' vector rotated towards the 'to'
         *  vector by the given absolute angle, in radians.
         *
         *  This function slerps the given 'from' vector towards the
         *  'to' vector.
         *
         *  @param from : A normalized direction vector specifying the
         *  direction of rotation at t=0.
		 *  @param to : A normalized direction vector specifying the
		 *  direction of rotation at t=1.
		 *  @param a : The maximum angle to rotate the 'from' vector by,
		 *  in the range [0, pi]. If the angle between 'from' and 'to' is
		 *  smaller than this angle, then the vector 'to' is returned.
		 *  Input values outside this range are silently clamped to the
		 *  [0, pi] interval.
		 *
		 *  @return A spherical linear interpolation of the vector 'from'
		 *  towards the vector 'to'.
        **/
        ////////////////////////////////////////////////////////////
        static Vector3 SlerpVectorAbs(const Vector3& from, const Vector3& to, Radian a);

        ////////////////////////////////////////////////////////////
        /** @brief Performs Normalised linear interpolation between
         *  two quaternions, and returns the result.
        **/
        ////////////////////////////////////////////////////////////
        Quaternion normalizedInterpolate(const Quaternion& target, Real t, bool shortestPath = false) const;
        static Quaternion NormalizedInterpolation(const Quaternion& source, const Quaternion& target, Real t, bool shortestPath = false)
        {
            return source.normalizedInterpolate(target, t, shortestPath);
        }

        ////////////////////////////////////////////////////////////
        /** @brief Returns the angle between two quaternions.
        **/
        ////////////////////////////////////////////////////////////
        Radian angleBetween(const Quaternion& target) const;

        ////////////////////////////////////////////////////////////
        /** @brief Returns the axis of rotation to get from this orientation
         *  to target orientation (the shortest route).
        **/
        ////////////////////////////////////////////////////////////
        Vector3 axisFromTo(const Quaternion& target) const;

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Creates a LookAt quaternion.
         *
         *  A LookAt quaternion is a quaternion that orients an object
         *  to face towards a specified target direction.
         *
         *  @param localForward : Specifies the forward direction in
         *  the local space of the object. This is the direction the model
         *  is facing at in its own local/object space, often +X (1,0,0),
         *  +Y (0,1,0) or +Z (0,0,1). The vector to pass in here depends on
         *  the conventions you or your modeling software is using, and it
         *  is best pick one convention for all your objects, and be consistent.
         *  This input parameter must be a normalized vector.
         *
         *  @param targetDirection : Specifies the desired world space
         *  direction the object should look at. This function will compute
         *  a quaternion which will rotate the localForward vector to orient
         *  towards this targetDirection vector. This input parameter must
         *  be a normalized vector.
         *
         *  @param localUp : Specifies the up direction in the local space of
         *  the object. This is the up direction the model was authored in,
         *  often +Y (0,1,0) or +Z (0,0,1). The vector to pass in here depends
         *  on the conventions you or your modeling software is using, and it
         *  is best to pick one convention for all your objects, and be consistent.
         *  This input parameter must be a normalized vector. This vector must
         *  be perpendicular to the vector localForward, i.e.
         *  localForward.Dot(localUp) == 0.
         *
         *  @param worldUp : Specifies the global up direction of the scene in
         *  world space. Simply rotating one vector to coincide with another
         *  (localForward->targetDirection) would cause the up direction of the
         *  resulting orientation to drift (e.g. the model could be looking at its
         *  target its head slanted sideways). To keep the up direction straight,
         *  this function orients the localUp direction of the model to point towards
         *  the specified worldUp direction (as closely as possible). The worldUp
         *  and targetDirection vectors cannot be collinear, but they do not need
         *  to be perpendicular either.
         *
         *  @return A quaternion that maps the given local space forward direction
         *  vector to point towards the given target direction, and the given local
         *  up direction towards the given target world up direction. For the returned
         *  quaternion Q it holds that M * localForward = targetDirection, and M * localUp
         *  lies in the plane spanned by the vectors targetDirection and worldUp.
        **/
        ////////////////////////////////////////////////////////////
        static Quaternion LookAt(const Vector3& localForward, const Vector3& targetDirection, const Vector3& localUp, const Vector3& worldUp);

        ////////////////////////////////////////////////////////////
        /** @brief Creates a new quaternion that rotates about the positive
         *  X axis by the given angle.
        **/
        ////////////////////////////////////////////////////////////
        static Quaternion RotateX(Radian a);

        ////////////////////////////////////////////////////////////
        /** @brief Creates a new quaternion that rotates about the positive
         *  Y axis by the given angle.
        **/
        ////////////////////////////////////////////////////////////
        static Quaternion RotateY(Radian a);

        ////////////////////////////////////////////////////////////
        /** @brief Creates a new quaternion that rotates about the positive
         *  Z axis by the given angle.
        **/
        ////////////////////////////////////////////////////////////
        static Quaternion RotateZ(Radian a);

        ////////////////////////////////////////////////////////////
        /** @brief Creates a new Quat that rotates about the given axis
         *  by the given angle.
        **/
        ////////////////////////////////////////////////////////////
        static Quaternion RotateAxisAngle(const Vector3& axis, Radian angle);

        ////////////////////////////////////////////////////////////
        /** @brief Creates a new quaternion that rotates sourceDirection
         *  vector (in world space) to coincide with the targetDirection
         *  vector (in world space).
         *
         *  Rotation is performed around the origin. The vectors sourceDirection
         *  and targetDirection are assumed to be normalized.
         *
         *  @note There are multiple such rotations. This function returns
         *  the rotation that has the shortest angle (when decomposed to
         *  axis-angle notation).
        **/
        ////////////////////////////////////////////////////////////
        static Quaternion RotateFromTo(const Vector3& sourceDirection, const Vector3& targetDirection);

        ////////////////////////////////////////////////////////////
        /** Creates a new quaternion that
         *  1. rotates sourceDirection vector to coincide with the
         *  targetDirection vector, and then
	     *  2. rotates sourceDirection2 (which was transformed by 1.) to
	     *  targetDirection2, but keeping the constraint that sourceDirection
	     *  must look at targetDirection.
        **/
        ////////////////////////////////////////////////////////////
        static Quaternion RotateFromTo(const Vector3 &sourceDirection, const Vector3 &targetDirection, const Vector3 &sourceDirection2, const Vector3 &targetDirection2)
		{
		    return LookAt(sourceDirection, targetDirection, sourceDirection2, targetDirection2);
		}

		static const Quaternion identity;
		static const Quaternion nan;

    };
}

#endif // APRO_QUATERNION_H
