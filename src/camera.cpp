#include "camera.h"

#include <glm/ext/quaternion_trigonometric.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/norm.hpp>

const glm::vec3 &Camera::target() const
{
	return _target;
}

void Camera::set_target(const glm::vec3 &target)
{
	_target = target;
	_dirty_mask |= DIRTY_VIEW;
}

float Camera::target_distance() const
{
	return _target_distance;
}

void Camera::set_target_distance(float target_distance)
{
	_target_distance = target_distance;
	_dirty_mask |= DIRTY_VIEW;
}

const glm::quat &Camera::orientation() const
{
	return _orientation;
}

void Camera::set_orientation(const glm::quat &q)
{
	_orientation = q;
	_dirty_mask |= DIRTY_VIEW;
}

void Camera::set_size(int width, int height)
{
	_width = width;
	_height = height;
	_dirty_mask |= DIRTY_PROJECTION;
}

int Camera::width() const
{
	return _width;
}

int Camera::height() const
{
	return _height;
}

void Camera::validate()
{
	if (_dirty_mask & DIRTY_PROJECTION)
	{
		// Compute projection matrix

		float aspect = static_cast<float>(_width) / static_cast<float>(_height);
		if (aspect > 1.0f)
			_projection = glm::ortho(-aspect, aspect, -1.0f, 1.0f, -10.0f, 10.0f);
		else
		{
			float inv_aspect = 1.0f / aspect;
			_projection = glm::ortho(-1.0f, 1.0f, -inv_aspect, inv_aspect, -10.0f, 10.0f);
		}
	}

	if (_dirty_mask & DIRTY_VIEW)
	{
		// Compute view matrix and vectors

		_front = glm::normalize(_orientation * glm::vec3(0.0f, 0.0f, -1.0f));
		_right = glm::normalize(_orientation * glm::vec3(1.0f, 0.0f, 0.0f));
		_up = glm::normalize(_orientation * glm::vec3(0.0f, 1.0f, 0.0f));

		_position = _target - _target_distance * _front;
		_view = glm::lookAt(_position, _target, _up);
	}

	_dirty_mask = 0;
}

const glm::mat4 &Camera::projection()
{
	validate();
	return _projection;
}

const glm::mat4 &Camera::view()
{
	validate();
	return _view;
}

const glm::vec3 &Camera::position()
{
	validate();
	return _position;
}

const glm::vec3 &Camera::front()
{
	validate();
	return _front;
}

const glm::vec3 &Camera::right()
{
	validate();
	return _right;
}

const glm::vec3 &Camera::up()
{
	validate();
	return _up;
}

static glm::vec3 project_to_sphere(
	const glm::vec2 &pos,  // mouse position in pixels relative to top-left of screen
	const glm::vec2 &dim   // size of the viewport in pixels
)
{
	// TODO: Project 2D mouse pixel coordinates onto a unit sphere centered at the origin (normalized device coordinates)
	// Hint: If the coordinates are outside the sphere, project to nearest point on the equator.
	
	return glm::vec3(0.0);
}

void Camera::trackball(const glm::vec2 &old_pos, const glm::vec2 &new_pos)
{
	glm::vec2 dim(_width, _height);  // size of the viewport
	glm::vec3 p0 = project_to_sphere(old_pos, dim);  // old position on sphere
	glm::vec3 p1 = project_to_sphere(new_pos, dim);  // new position on sphere

	// TODO: Find the quaternion rotating p0 to p1 and rotate _orienation to update the view
	// Hint: glm::angleAxis(angle, axis) gives a quaternion rotating angle radians around axis

	_dirty_mask |= DIRTY_VIEW;  // marks the view as dirty, keep this
}

void Camera::reset()
{
	_target = glm::vec3(0.0f);
	_target_distance = 1.0f;
	_orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);

	_dirty_mask = DIRTY_VIEW | DIRTY_PROJECTION;
}

Camera::Camera() :
	_dirty_mask(-1),
	_target(0.0f),
	_target_distance(1.0f),
	_orientation(1.0f, 0.0f, 0.0f, 0.0f),
	_width(1), _height(1),
	_projection(0.0f),
	_view(0.0f),
	_position(0.0f),
	_front(0.0f), _right(0.0f), _up(0.0f)
{

}
