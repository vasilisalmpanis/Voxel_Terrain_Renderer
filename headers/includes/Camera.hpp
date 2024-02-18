#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.05f;
const float ZOOM = 45.0f;

class Camera {
    public:
        Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
        Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
        ~Camera(void);
        Camera(const Camera &other);
        Camera &operator=(const Camera &other);
        void        updateCameraVectors(void);
        glm::mat4   GetViewMatrix(void) const;
        void        ProcessKeyboard(Camera_Movement direction, float deltaTime);
        void        ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
        void        ProcessMouseScroll(float yoffset);

    private:
        glm::vec3 Position;
        glm::vec3 Center;
        glm::vec3 Up;
        glm::vec3 Right;
        glm::vec3 WorldUp;

        // Euler Angles
        float Yaw;
        float Pitch;

        // Camera options
        float MovementSpeed;
        float MouseSensitivity;
        float Zoom;
};

#endif