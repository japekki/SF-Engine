#ifndef CAMERA_HPP
	#define CAMERA_HPP

	#include "geom.hpp"

	class Camera {
		public:
			Coordinate3D location;
			Vector3D *direction;
			float angle_x, angle_y;	// How narrow or wide the view port is (for example to make a 360 degree camera)
			float zoom;
			float focus;
			float perspective;	// flat or deep
			void rotate(float angle_x, float angle_y, float angle_z);
			Camera();
			~Camera();
	};

#endif // CAMERA_HPP
