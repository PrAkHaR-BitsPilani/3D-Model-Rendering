#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>


///Containes the four direction in which a camera can move. These four direction need not be the conventional one.
enum camera_movements {
    FORWARD,
    BACKWARD,
    RIGHT,
    LEFT
};
///Default value.
const float YAW = 0.0f;
///Default value.
const float PITCH = 0.0f;
///defalut value
const float ROLL = 0.0f;
///Default value.
const float SPEED = 2.5f;
///Default value.
const float SENSITIVITY = 0.1f;
///Default value.
///FOV here means Field Of View.
const float FOV = 45.0f;
///Implementation of a simple camera
///
///It uses a perspective projection and supports 3D movement.
class Camera
{
private:
    //camera attributes
    glm::vec3 m_cameraPos;
    glm::vec3 m_cameraFront;
    glm::vec3 m_cameraUp;
    glm::vec3 m_cameraRight;
    glm::vec3 m_worldUp;
    glm::vec3 cameraFrontOrg;
    glm::vec3 cameraRightOrg;
    glm::vec3 cameraUpOrg;
    //euler angles
    float m_yaw;
    float m_pitch;
    float m_roll;
    //camera options
    float m_cameraSpeed;
    float m_cameraSensitivity;
    float m_fov;

    void updateCameraVectors();


public:
    ///Initializes the camera with the initial values.
    ///@param position the position where the camera is placed (in world coordinates)
    ///@param front the point which the camera is looking (in world coordinates)
    ///@param up the world-up direction
    ///@param yaw determines how much left or right are we looking
    ///@param pitch determins how much up or down are we looking
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH, float roll = ROLL);

    ///Returns a view matrix corresponding to the current state of the camera.
    glm::mat4 getViewMatrix();
    ///Processes keyboard events.
    ///@param direction Specifies the direction in which camera needs to be moved.
    ///@param deltatime The time difference between two successive keyboard inputs. This is needed to synchronize the frame rate.
    void processKeyboardInput(camera_movements direction, float deltatime);
    ///Processes mouse events. Changes the yaw and pitch values.
    void processMouseMovement(float x_offset, float y_offset, bool constrainedPitch = true);
    ///Processes scrolling events. Changes field of view.
    void processMouseScroll(float y_offset);
    ///process camera roll
    void processCameraRoll(float theta);
    ///Sets camera movement speed
    void setSpeed(float speed);
    ///Sets the Euler Angles { PITCH YAW ROLL }
    void setAngles(glm::vec3 EulerAngles);
    ///Resets the camera
    ///@attention the camera is placed at \p position looking at the point \f$ (0,0,-1) \f$
    void recenter(glm::vec3 position);
    ///Returns the current field of view
    float getFOV();
    glm::vec3 getPosition();

};





