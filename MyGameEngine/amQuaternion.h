#pragma once
#include "amMatrix4x4.h"
#include "amVectorMath.h"

struct amQuaternion : public amVec3 { 
		float w;

		/// Just a little utility to populate a amQuaternion
		inline void load( float _w, float _x, float _y, float _z ) {
			w = _w; x = _x; y = _y; z = _z; 
		}

		/// This is the unit quaterion by definition 
		inline amQuaternion( ){
			load(1.0f,0.0f,0.0f,0.0f);
		}


		inline amQuaternion(float _w, float _x,  float _y, float _z){
			load(_w,_x,_y,_z);
		}

		/// This is the constructor for a rotation  quartinion 
		/// The w component is degrees and n is the axis of rotations 
		inline amQuaternion( float angle, const amVec3& n){
			angle *= DEGREES_TO_RADIANS; ///
			load(cos(angle/2.0f), sin(angle/2.0f)*n.x, sin(angle/2.0f)*n.y, sin(angle/2.0f)*n.z );
		}

		
		/// A copy constructor
		inline amQuaternion( const amQuaternion& q ) { 
			load(q.w, q.x, q.y, q.z); 
		}

		/// An assignment operator   
		inline amQuaternion& operator = (const amQuaternion& q){
			load(q.w, q.x, q.y, q.z); 
			return *this;
		}

		/// Take the negative of a amQuaternion
		inline const amQuaternion operator - () const  { 
			return amQuaternion(-w, -x, -y, -z ); 
		}  

		/// Multiply a two amQuaternions - using the right-hand rule  
		inline const amQuaternion operator * (const amQuaternion& q) const {
			amVec3 ijk(w*q + q.w * (*this) + amVectorMath::CalcCrossProduct(*this, q));
			return amQuaternion(w * q.w - amVectorMath::CalcDotProduct(*this, q), ijk.x, ijk.y, ijk.z);
		}
		
		inline const amQuaternion conjugate() const {
			return amQuaternion( w, -x, -y, -z ); 
		}

		inline amVec3 rotate(const amVec3& v){
			/// This is the standard way q*v*q^-1
			///return amVec3( (*this) * v * (*this).conjugate());

			/// I read a paper that shows this way to be faster and it works! 
			amVec3 v2 = amVectorMath::CalcCrossProduct(*this, v);
			return v + v2 * (2.0f * w) + amVectorMath::CalcCrossProduct(*this, v2) * 2.0f;
		}


		inline  amMatrix4x4 toMatrix(){
			/// This is the fastest way I know...
			return amMatrix4x4(	(1.0f - 2.0f*y*y - 2.0f*z*z), (2.0f*x*y + 2.0f * z*w),      (2.0f*x*z - 2.0f*y*w),        0.0f,
							(2.0f*x*y - 2.0f*z*w),        (1.0f - 2.0f*x*x - 2.0f*z*z), (2*y*z + 2*x*w),              0.0f,
							(2.0f*x*z + 2.0f*y*w),        (2.0f*y*z - 2*x*w),           (1.0f - 2.0f*x*x - 2.0f*y*y), 0.0f,
							 0.0f,                         0.0f,                         0.0f,                        1.0f);

			 /// ... but this is the coolest . My way is just a bit faster on single processor machines
			 /// but this method is faster on parallel multicore machines.
			 /*Matrix m1(  w,   z,  -y,  x,
                          -z,   w,   x,  y,
                           y,  -x,   w,  z,
                          -x,  -y,  -z,  w);

			 Matrix m2(  w,   z, -y, -x,
						-z,   w,  x, -y,
						 y,  -x,  w, -z,
						-x,   y,  z,  w);
			  return m1 * m2;*/
		}


		/// To work this out you can multipy the three angles as amQuaternions together. 
		/// q = q(yaw) * q(pitch) * q(yaw) the result is as follows
		inline const amQuaternion fromEuler(float _yaw, float _pitch, float _roll){
			float cosYaw = cos(0.5f *_yaw * DEGREES_TO_RADIANS);
			float cosPitch = cos(0.5f * _pitch * DEGREES_TO_RADIANS);
			float cosRoll = cos(0.5f  *_roll * DEGREES_TO_RADIANS);
			float sinYaw = sin(0.5f *_yaw * DEGREES_TO_RADIANS);
			float sinPitch = sin(0.5f * _pitch * DEGREES_TO_RADIANS);
			float sinRoll = sin(0.5f  *_roll * DEGREES_TO_RADIANS);
			return amQuaternion(	
				(cosYaw * cosPitch * cosRoll) + (sinYaw * sinPitch * sinRoll),
				(cosYaw * cosPitch * sinRoll) - (sinYaw * sinPitch * cosRoll),
				(cosYaw * sinPitch * cosRoll) + (sinYaw * cosPitch * sinRoll),
				(sinYaw * cosPitch * cosRoll) - (cosYaw * sinPitch * sinRoll));
		}

		
		inline void print() { 
			printf("%f %f %f %f\n", w,x,y,z);		  
		}

};
