#include "entity.hpp"

#ifdef __cplusplus
	#include <cstdlib>
#else
	#include <stdlib.h>
#endif

#include <iostream>
#include <fstream>
#include <sstream>

#include <math.h>
#include "graph.hpp"
#include "options.hpp"

#include <string>

using namespace std;

Entity::Entity() {
	location.x = 0;
	location.y = 0;
	location.z = 0;
	direction.x = 0;
	direction.y = 0;
	direction.z = 0;
	rotation.x = 0.0;
	rotation.y = 0.0;
	rotation.z = 0;
	balance.a = 0;
	balance.b = 0;
	balance.c = 0;
	balance.d = 0;
	balance.e = 0;
	balance.f = 0;
	balance.g = 0;
	polygonshadestyle = POLYGON_SHADESTYLE_NODRAW;

	//#ifdef WITH_OPENGL
	//    ingpu = false;
	//#endif
}

Entity::~Entity() {
	//delete [] vertexarray;
}

void Entity::movecenter() {
	location.x += direction.x;
	location.y += direction.y;
	location.z += direction.z;
}

void Entity::translatevertexarray() {
	vertex3d_struct tmp;
	for (int i = 0; i<vertex3darray.size(); i++) {
		tmp = vertex3darray.at(i);
		tmp.x = tmp.x - location.x;
		tmp.y = tmp.y - location.y;
		tmp.z = tmp.z - location.z;
		vertex3darray.at(i) = tmp;
	}
}

void Entity::scale(float scale_x, float scale_y, float scale_z) {
	for (int i = 0; i < vertex3darray.size(); i++)
	{
		vertex3d_struct tmp;
		tmp = vertex3darray.at(i);
		tmp.x = tmp.x * scale_x;
		tmp.y = tmp.y * scale_y;
		tmp.z = tmp.z * scale_z;
		vertex3darray.at(i) = tmp;
	}
}

void Entity::scale(float scale_) {
	scale(scale_, scale_, scale_);
}

void Entity::rotatecenter() {
	float new_x, new_y, new_z;
	// Z-akselin suhteen:
	//x' = x*cos q - y*sin q
	//y' = x*sin q + y*cos q
	//z' = z
	new_x = location.x * cos(rotation.z) - location.y * sin(rotation.z);
	new_y = location.x * sin(rotation.z) + location.y * cos(rotation.z);
	location.x = new_x;
	location.y = new_y;

	// X-akselin suhteen:
	//y' = y*cos q - z*sin q
	//z' = y*sin q + z*cos q
	//x' = x
	new_y = location.y * cos(rotation.x) - location.z * sin(rotation.x);
	new_z = location.y * sin(rotation.x) + location.z * cos(rotation.x);
	location.y = new_y;
	location.z = new_z;

	// Y-akselin suhteen:
	//z' = z*cos q - x*sin q
	//x' = z*sin q + x*cos q
	//y' = y
	new_z = location.z * cos(rotation.y) - location.x * sin(rotation.y);
	new_x = location.z * sin(rotation.y) + location.x * cos(rotation.y);
	location.y = new_y;
	location.x = new_x;
}

void Entity::rotatevertexarray(float angle_x, float angle_y, float angle_z) {
	for (int i = 0; i < vertex3darray.size(); i++)
	{
		Point piste(vertex3darray.at(i).x, vertex3darray.at(i).y, vertex3darray.at(i).z);
		piste.rotate(angle_x, angle_y, angle_z);
		vertex3darray.at(i).x = piste.x;
		vertex3darray.at(i).y = piste.y;
		vertex3darray.at(i).z = piste.z;
	}
}

void Entity::rotatevertexarray() {
	vertex3d_struct tempvert;
	for (int i = 0; i < vertex3darray.size(); i++)
	{
		Point piste(vertex3darray.at(i).x, vertex3darray.at(i).y, vertex3darray.at(i).z);
		piste.rotate(rotation.x, rotation.y, rotation.z);
		tempvert.x = piste.x;
		tempvert.y = piste.y;
		tempvert.z = piste.z;
		vertex3darray.at(i).x=tempvert.x;
		vertex3darray.at(i).y=tempvert.y;
		vertex3darray.at(i).z=tempvert.z;
	}
}

boundingbox Entity::getboundingbox() {
	boundingbox result;
	for (int i=0; i<vertex3darray.size(); i++)
	{
		vertex3d_struct tmpvertex = vertex3darray.at(i);
		if (result.x_min > tmpvertex.x) { result.x_min = tmpvertex.x; }
		if (result.x_max < tmpvertex.x) { result.x_max = tmpvertex.x; }
		if (result.y_min > tmpvertex.y) { result.y_min = tmpvertex.y; }
		if (result.y_max < tmpvertex.y) { result.y_max = tmpvertex.y; }
		if (result.z_min > tmpvertex.z) { result.z_min = tmpvertex.z; }
		if (result.z_max < tmpvertex.z) { result.z_max = tmpvertex.z; }
		result.size_x = fabs(result.x_max - result.x_min);
		result.size_y = fabs(result.y_max - result.y_min);
		result.size_z = fabs(result.z_max - result.z_min);
	}
	return result;
}

/*
#ifdef WITH_OPENGL
void Entity::togpu(){
	if (gpuvertexbuffer)
	{
		//pass the vertex pointer:
		glVertexPointer( 3,   //3 components per vertex (x,y,z)
			GL_FLOAT,
			sizeof(Vertex3d),
			&vertex3darray[0]);
		//pass the color pointer
		glColorPointer(  3,   //3 components per vertex (r,g,b)
			GL_FLOAT,
			sizeof(Vertex3d),
			&vertex3darray[0].r);  //Pointer to the first color
	}
	else
	{
		glBegin(GL_TRIANGLES);
		for (int i = 0; i < vertex3darray.size(); i++)
		{
			glColor3f( vertex3darray.at(i).r, vertex3darray.at(i).g, vertex3darray.at(i).b );
			glVertex3f( vertex3darray.at(i).x, vertex3darray.at(i).y, vertex3darray.at(i).z );
		}
		glEnd();


		int faces = 10;
		for (int i=0; i<faces; i++){
		glColor3f( 1.0f, 0.0f, 0.0f);
		glVertex3f( sin(PI/(faces/2)*i), cos(PI/(faces/2)*i), 0.0f);
		glColor3f( 0.0f, 1.0f, 0.0f);
		glVertex3f( sin((PI/(faces/2)*(i+1))), cos(PI/(faces/2)*(i+1)), 0.0f);
		glColor3f( 0.0f, 0.0f, 0.5);
		glVertex3f( 0.0f, 0.0f, 0.0);

		glColor3f( 1.0f, 0.0f, 0.0f);
		glVertex3f( sin(PI/(faces/2)*i), cos(PI/(faces/2)*i), 0.0f);
		glColor3f( 0.0f, 1.0f, 0.0f);
		glVertex3f( sin(PI/(faces/2)*(i+1)), cos(PI/(faces/2)*(i+1)), 0.0f);
		glColor3f( 0.0f, 0.0f, 0.5);
		glVertex3f( 0.0f, 0.0f, -1.0f);
		}

	//glBegin(GL_TRIANGLES);
	//glColor3f(1.0f, 0.0f, 0.0f);
	//glVertex3f(kolmio.a.x, kolmio.a.y, kolmio.a.z);
	//glColor3f(1.0f, 0.0f, 0.0f);
	//glVertex3f(kolmio.b.x, kolmio.b.y, kolmio.b.z);
	//glColor3f(1.0f, 0.0f, 0.0f);
	//glVertex3f(kolmio.c.x, kolmio.c.y, kolmio.c.z);
	//glEnd();

	}
	ingpu = true;
}

*/

void Entity::resize3dvertexarray(int n) {
	vertex3darray.resize(n);
}

void Entity::draw2d_wireframe() {
   for (int i=0; i<vertex3darray.size()-1; i++)
	{
			draw_line(round(vertex3darray.at(i).x), round(vertex3darray.at(i).y),
					  round(vertex3darray.at(i+1).x), round(vertex3darray.at(i+1).y),
					  1, colorOrange, surface);
	}
}


void Entity::draw2d_polygon() {
	/*
	#ifdef WITH_OPENGL
		// Points:
		// glDrawArrays(GL_POINTS,0,NumVertices);

		// Wireframe: GL_LINES
		//  GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_TRIANGLES, GL_QUAD_STRIP, GL_QUADS, GL_POLYGON

		// Triangles:
		glDrawElements( GL_TRIANGLES,   // mode
						sizeof(vertex3darray),                 // count, ie. how many indices
						GL_UNSIGNED_INT,            // type of the index array
						&vertex3darray);
	#else
	*/

		for (int i=0; i<vertex3darray.size()/3; i++) {
			vertex3d_struct tmp_vert;
			triangle2d tmp_tri;

			tmp_vert = vertex3darray.at(3*i);
			tmp_tri.a.x = tmp_vert.x;
			tmp_tri.a.y = tmp_vert.y;
			tmp_tri.a.r = tmp_vert.r;
			tmp_tri.a.g = tmp_vert.g;
			tmp_tri.a.b = tmp_vert.b;

			tmp_vert = vertex3darray.at(3*i+1);
			tmp_tri.b.x = tmp_vert.x;
			tmp_tri.b.y = tmp_vert.y;
			tmp_tri.b.r = tmp_vert.r;
			tmp_tri.b.g = tmp_vert.g;
			tmp_tri.b.b = tmp_vert.b;

			tmp_vert = vertex3darray.at(3*i+2);
			tmp_tri.c.x = tmp_vert.x;
			tmp_tri.c.y = tmp_vert.y;
			tmp_tri.c.r = tmp_vert.r;
			tmp_tri.c.g = tmp_vert.g;
			tmp_tri.c.b = tmp_vert.b;

			//tmp_tri.color = color;
			draw2d_triangle(tmp_tri, polygonshadestyle, true, surface);
		}

}


#ifdef DEBUGMSG
void Entity::printvertexarray()
// FOR DEBUG PURPOSES
{
	for (int i=0; i<vertex3darray.size(); i++) {
		vertex3d_struct tmp;
		tmp = vertex3darray.at(i);
		printf("x: %f y: %f z: %f r: %f g: %f b: %f\n", tmp.x, tmp.y, tmp.z, tmp.r, tmp.g, tmp.b);
	}
}
#endif


void Entity::draw3d_polygon() {
	/*
	#ifdef WITH_OPENGL
		// Points:
		// glDrawArrays(GL_POINTS,0,NumVertices);

		// Wireframe: GL_LINES
		//  GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_TRIANGLES, GL_QUAD_STRIP, GL_QUADS, GL_POLYGON

		// Triangles:
	if (gpuvertexbuffer)
	{
		glDrawElements( GL_TRIANGLES,   // mode
						sizeof(vertex3darray),                 // count, ie. how many indices
						GL_UNSIGNED_INT,            // type of the index array
						&vertex3darray);
	}
	else
	{
		//togpu();
		glBegin(GL_TRIANGLES);
		for (int i=0; i<face3darray.size(); i=i+3) {
			vertex3d_struct tmp_vert;
			triangle3d tmp_tri;
			tmp_tri.color = color;

			tmp_vert = vertex3darray.at( face3darray.at(i) );
						tmp_vert.r = tmp_vert.r;
						tmp_vert.g = tmp_vert.g;
						tmp_vert.b = tmp_vert.b;
			glColor3f  ( tmp_vert.r, tmp_vert.g, tmp_vert.b);
			glVertex3f ( tmp_vert.x, tmp_vert.y, tmp_vert.z);

			tmp_vert = vertex3darray.at( face3darray.at(i+1) );
						tmp_vert.r = tmp_vert.r;
						tmp_vert.g = tmp_vert.g;
						tmp_vert.b = tmp_vert.b;
			glColor3f  ( tmp_vert.r, tmp_vert.g, tmp_vert.b);
			glVertex3f ( tmp_vert.x, tmp_vert.y, tmp_vert.z);

			tmp_vert = vertex3darray.at( face3darray.at(i+2) );
						tmp_vert.r = tmp_vert.r;
						tmp_vert.g = tmp_vert.g;
						tmp_vert.b = tmp_vert.b;
			glColor3f  ( tmp_vert.r, tmp_vert.g, tmp_vert.b);
			glVertex3f ( tmp_vert.x, tmp_vert.y, tmp_vert.z);

			//draw3d_triangle(/tmp_tri, polygonshadestyle, surface);
		}
		glEnd();
	}
	#else
	*/
		for (int i=0; i<face3darray.size(); i=i+3) {
			vertex3d_struct tmp_vert;
			Triangle3d tmp_tri;
			tmp_tri.shadestyle = polygonshadestyle;

			tmp_vert = vertex3darray.at( face3darray.at(i) );
			tmp_tri.a.x = tmp_vert.x;
			tmp_tri.a.y = tmp_vert.y;
			tmp_tri.a.z = tmp_vert.z;
			tmp_tri.a.r = tmp_vert.r;
			tmp_tri.a.g = tmp_vert.g;
			tmp_tri.a.b = tmp_vert.b;
			//tmp_tri.a.setcolor(tmp_vert.r, tmp_vert.g, tmp_vert.b);

			tmp_vert = vertex3darray.at( face3darray.at(i+1) );
			tmp_tri.b.x = tmp_vert.x;
			tmp_tri.b.y = tmp_vert.y;
			tmp_tri.b.z = tmp_vert.z;
			tmp_tri.b.r = tmp_vert.r;
			tmp_tri.b.g = tmp_vert.g;
			tmp_tri.b.b = tmp_vert.b;
			//tmp_tri.b.setcolor(tmp_vert.r, tmp_vert.g, tmp_vert.b);

			tmp_vert = vertex3darray.at( face3darray.at(i+2) );
			tmp_tri.c.x = tmp_vert.x;
			tmp_tri.c.y = tmp_vert.y;
			tmp_tri.c.z = tmp_vert.z;
			tmp_tri.c.r = tmp_vert.r;
			tmp_tri.c.g = tmp_vert.g;
			tmp_tri.c.b = tmp_vert.b;
			//tmp_tri.c.setcolor(tmp_vert.r, tmp_vert.g, tmp_vert.b);
			/*
			#ifdef DEBUGMSG
				printf("Trying to draw triangle: %f %f %f\n", tmp_vert.x, tmp_vert.y, tmp_vert.z);
				printvertexarray();
			#endif
			*/
			//printf("%i\n", i);
			//printf("%f\n", vertex3darray.at(4).r);
			tmp_tri.color = SDL_MapRGB(surface->format, int(255*tmp_vert.r), int(255*tmp_vert.g), int(255*tmp_vert.b));
			tmp_tri.draw(surface);
		}

}

bool Entity::loadfromfile(string filename_) {
	bool result;
	filename = filename_;

	cout << "Loading file " << filename << ": ";

	string filename_ext = filename.substr(filename.length()-4, 4);
							//cout << filename_ext << endl;
	if (filename_ext.compare(".obj") == 0) {   // Jos 3d objekti -tiedosto:

		// TEXT FILE
		string line;
		ifstream entityfile(filename.c_str(), ios::binary);   // Default?
		if (entityfile.is_open()) {
			int vertex_n = 0;
			int face_n = 0;
			vertex3darray.clear();
			face3darray.clear();
			while (!entityfile.eof()) {
				getline (entityfile, line);
				if (line.length() > 0) {
					if (line.at(0) == 'v') {  // Vertex
						vertex_n++;
						char kytkin;
						kytkin = 'x';
						string x, y, z;
						x = y = z = "";

						for (int i = 2; i < line.length(); i++) {
							//cout << line.at(i) << endl;
							if (line.at(i) == ' ') {
								kytkin++;
							}
							else {
								if (kytkin == 'x') {
									x.append(line.substr(i, 1));
								}
								else if (kytkin == 'y') {
									y.append(line.substr(i, 1));
								}
								else if (kytkin == 'z') {
									z.append(line.substr(i, 1));
								}
							}
						}
						vertex3d_struct vert;
						std::stringstream ss_x;
						std::stringstream ss_y;
						std::stringstream ss_z;
						ss_x << x;
						ss_x >> vert.x;
						ss_y << y;
						ss_y >> vert.y;
						ss_z << z;
						ss_z >> vert.z;
						vert.r = 1.0;   // TODO
						vert.g = 1.0;   // TODO
						vert.b = 1.0;   // TODO
						vertex3darray.push_back(vert);
						/*
						#ifdef DEBUGMSG
							cout << endl;
							cout << "x: " << x << " y: " << y << " z: " << z << endl;
							cout << "x: " << vert.x <<  " y: " << vert.y << " z: " << vert.z << endl;
							printf("%f %f %f\n",  vertex3darray.at(vertex3darray.size()-1).x, vertex3darray.at(vertex3darray.size()-1).y, vertex3darray.at(vertex3darray.size()-1).z);
						#endif
						*/
					}
					else if (line.at(0) == 'f') { // Face
						face_n++;
						char kytkin;
						kytkin = 'a';
						string a, b, c;
						a = b = c = "";

						for (int i = 2; i < line.length(); i++) {
								char merkki = line.at(2);
							//cout << line.at(i) << endl;
							if (line.at(i) == ' ')
							{
								kytkin++;
							}
							else {
								if (kytkin == 'a') {
									a.append(line.substr(i, 1));
								}
								else if (kytkin == 'b') {
									b.append(line.substr(i, 1));
								}
								else if (kytkin == 'c') {
									c.append(line.substr(i, 1));
								}
							}
						}
						unsigned int int_a, int_b, int_c;
						std::stringstream ss_a;
						std::stringstream ss_b;
						std::stringstream ss_c;
						ss_a << a;
						ss_a >> int_a;
						ss_b << b;
						ss_b >> int_b;
						ss_c << c;
						ss_c >> int_c;
						face3darray.push_back(int_a-1);
						face3darray.push_back(int_b-1);
						face3darray.push_back(int_c-1);
						#ifdef DEBUGMSG
							cout << "a: " << int_a << " b: " << int_b << " c: " << int_c << endl;
						#endif
					}
				}
			}
			result = entityfile.is_open();
			entityfile.close();
			cout << vertex_n << " vertexes, " << face_n << " faces" << endl;
		} //if (entityfile.is_open())
		else {
			cout << "ERROR" << endl;
			result = false;
		}
	} //if (filename_ext.compare(".obj") == 0)

	else if (filename_ext.compare(".ent") == 0) {
		// Jos entity -tiedosto:
		//  lue luokan Entity muuttujille arvot

		// BINARY FILE
		ifstream::pos_type size;
		char * memblock;
		ifstream file (filename.c_str(), ios::in|ios::binary|ios::ate);
		if (file.is_open()) {
			size = file.tellg();
			memblock = new char [size];
			file.seekg (0, ios::beg);
			file.read (memblock, size);
			file.close();
			cout << "OK " << size << " bytes" << endl;
			// TODO: parse data into vertexarray
			printf(memblock);
			delete[] memblock;
		}
		else {
			cerr << "ERROR" << endl;
			result = false;
		}
		result = true;
	} //if (filename_ext.compare(".ent") == 0)

	return result;
}

bool Entity::loadfromfile() {
	return loadfromfile(filename);
}

bool Entity::savetofile(string filename_) {
	bool result;
	filename = filename_;
	ofstream entityfile(filename.c_str(), ios::binary | ios::trunc);   // Default?
	for (int i=0; i<vertex3darray.size()-1; i++)
	{
	//    entityfile << vertex3darray.at(i);
	}
	result = entityfile.is_open();
	entityfile.close();
	return result;
}

bool Entity::savetofile() {
	return savetofile(filename);
}

void Entity::pushgeom() {
	vertex2darray_stored.resize(vertex2darray.size());
	vertex3darray_stored.resize(vertex3darray.size());
	face2darray_stored.resize(face2darray.size());
	face3darray_stored.resize(face3darray.size());
	for (int i=0; i<vertex3darray_stored.size(); i++) {
		vertex3darray_stored.at(i) = vertex3darray.at(i);
	}
	for (int i=0; i<vertex2darray_stored.size(); i++) {
		vertex2darray_stored.at(i) = vertex2darray.at(i);
	}
	for (int i=0; i<face2darray_stored.size(); i++) {
		face2darray_stored.at(i) = face2darray.at(i);
	}
	for (int i=0; i<face3darray_stored.size(); i++) {
		face3darray_stored.at(i) = face3darray.at(i);
	}
}

void Entity::popgeom() {
	vertex2darray.resize(vertex2darray_stored.size());
	vertex3darray.resize(vertex3darray_stored.size());
	face2darray.resize(face2darray_stored.size());
	face3darray.resize(face3darray_stored.size());
	for (int i=0; i<vertex3darray.size(); i++) {
		vertex3darray.at(i) = vertex3darray_stored.at(i);
	}
	for (int i=0; i<vertex2darray.size(); i++) {
		vertex2darray.at(i) = vertex2darray_stored.at(i);
	}
	for (int i=0; i<face2darray.size(); i++) {
		face2darray.at(i) = face2darray_stored.at(i);
	}
	for (int i=0; i<face3darray.size(); i++) {
		face3darray.at(i) = face3darray_stored.at(i);
	}
}

void Entity::effux_sine(Uint32 time) {
	for (int i=0; i<vertex3darray.size(); i++) {
		vertex3d_struct v;
		v = vertex3darray.at(i);
		v.z = v.z/2 + fabs(v.z/2*sin(PIX2/1000.0*time));
		//v.y = v.y/2 + v.y/2*sin(PI/1000.0*time);
		vertex3darray.at(i) = v;
	}
}

/*
Entity create_3dbox(float a, SDL_Surface *sdlsurface) {
	Entity result(sdlsurface);
	return result;
}
*/

/*
void Entity::generate_3dball(float r, Uint16 corners) {
	vertex3d_struct v;
	// generate vertexes:
	for (float z=0; z<corners; z++) {
		//float scale = 1.0+r*sin(PI/corners*z);
		float scale = r;

		for (int angle=0; angle<corners; angle++) { // 0..corners
			float color_temp = 0.0;
			v.x = scale * sin(PIX2/corners*angle);
			v.y = scale * cos(PIX2/corners*angle);
			v.z = -corners/2+(2*r)/corners*z;
				v.r = color_temp;
				v.g = color_temp;
				v.b = 1.0;
			vertex3darray.push_back(v);
			v.x = scale * sin(PIX2/corners*(angle+1));
			v.y = scale * cos(PIX2/corners*(angle+1));
			v.z = -corners/2+(2*r)/corners*z;
				v.r = color_temp;
				v.g = color_temp;
				v.b = 0.5;
			vertex3darray.push_back(v);
			v.x = scale * sin(PIX2/corners*(angle));
			v.y = scale * cos(PIX2/corners*(angle));
			v.z = -corners/2+(2*r)/corners*z;
				v.r = color_temp;
				v.g = color_temp;
				v.b = 0.0;
			vertex3darray.push_back(v);
		}
	}
	// generate faces:
		for (int i = 0; i<((corners-1)*corners*3); i+=3) {
			face3darray.push_back(i);
			face3darray.push_back(i+1);
			face3darray.push_back(i+corners);

			face3darray.push_back(i+1);
			face3darray.push_back(i+corners);
			face3darray.push_back(i+corners+1);
		}
}
*/

void Entity::generate_3dball(float r, Uint16 corners) {
	vertex3d_struct v;
	Point a;

	for (int x=0; x<corners; x++){
		for (int z=0; z<corners; z++){
			a.x = r;
			a.y = 0;
			a.z = 0;
			a.rotate(0, 0, PIX2/corners*z);
			a.rotate(x, 0, 0);

			v.x = a.x;
			v.y = a.y;
			v.z = a.z;
			// generate vertex:
			vertex3darray.push_back(v);
		}
	}

	// generate faces:
	for (int i=0; i<vertex3darray.size()-corners-3; i+=3 ) {
		face3darray.push_back(i);
		face3darray.push_back(i+1);
		face3darray.push_back(i+2);
	}


}
