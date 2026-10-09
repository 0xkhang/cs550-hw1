#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <glm/glm.hpp>
#include <glm/ext/quaternion_float.hpp>

// Represents a camera orbiting around a position in 3D space.
class Camera
{
public:

	// Position to orbit around
	const glm::vec3 &target() const;
	void set_target(const glm::vec3 &target);

	// Distance from orbit target
	float target_distance() const;
	void set_target_distance(float target_distance);

	// Rotation around orbit point
	const glm::quat &orientation() const;
	void set_orientation(const glm::quat &q);

	// Viewport dimensions
	void set_size(int width, int height);
	int width() const;
	int height() const;

	void validate();

	// Projection matrix
	const glm::mat4 &projection();

	// View matrix
	const glm::mat4 &view();

	// Eye position
	const glm::vec3 &position();

	// Front vector
	const glm::vec3 &front();

	// Right vector
	const glm::vec3 &right();

	// Up vector
	const glm::vec3 &up();

	void trackball(const glm::vec2 &old_pos, const glm::vec2 &new_pos);

	// Reset camera to default values
	void reset();

	Camera();
	~Camera() = default;
private:
	enum ValidFlags
	{
		DIRTY_PROJECTION = 0x1,
		DIRTY_VIEW = 0x2
	};

	glm::vec3 _target;
	float _target_distance;
	glm::quat _orientation;

	int _width, _height;

	unsigned _dirty_mask;

	glm::mat4 _projection;
	glm::mat4 _view;

	glm::vec3 _position;
	glm::vec3 _front, _right, _up;
};

#endif
