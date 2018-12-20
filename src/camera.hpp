#ifndef CAMERA_HPP
	#define CAMERA_HPP

	// Forward declarations:
		class Point3D;
		class Vector3D;

	class Camera {
		public:
			Point3D* location;
			Vector3D *direction;
			float angle_x, angle_y;	// How narrow or wide the view port is (for example to make a 360 degree camera)
			float zoom;
			float focus;
			float perspective;	// flat or deep
			void rotate(float angle_x, float angle_y, float angle_z);
			void set_focus(float focus);
			void set_zoom(float zoom);
			Camera();
			~Camera();
	};

#endif // CAMERA_HPP
