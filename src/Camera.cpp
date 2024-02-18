#include <includes/Camera.hpp>

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch):   Position(position), 
                                                                            Center(glm::vec3(0.0f, 0.0f, 0.0f)), 
                                                                            Up(up), WorldUp(up), 
                                                                            Yaw(yaw),
                                                                            Pitch(pitch),
                                                                            MovementSpeed(SPEED),
                                                                            MouseSensitivity(SENSITIVITY),
                                                                            Zoom(ZOOM)
{
    updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch):    Position(glm::vec3(posX, posY, posZ)),
                                                                                                                Center(glm::vec3(0.0f, 0.0f, 0.0f)),
                                                                                                                Up(glm::vec3(upX, upY, upZ)),
                                                                                                                WorldUp(glm::vec3(upX, upY, upZ)),
                                                                                                                Yaw(yaw),
                                                                                                                Pitch(pitch),
                                                                                                                MovementSpeed(SPEED),
                                                                                                                MouseSensitivity(SENSITIVITY),
                                                                                                                Zoom(ZOOM)
{
    updateCameraVectors();
}

Camera::~Camera(void) {}

Camera::Camera(const Camera &other)
{
    *this = other;
}

Camera &Camera::operator=(const Camera &other)
{
    if (this != &other)
    {
        this->Position = other.Position;
        this->Center = other.Center;
        this->Up = other.Up;
        this->Right = other.Right;
        this->WorldUp = other.WorldUp;
        this->Yaw = other.Yaw;
        this->Pitch = other.Pitch;
        this->MovementSpeed = other.MovementSpeed;
        this->MouseSensitivity = other.MouseSensitivity;
        this->Zoom = other.Zoom;
    }
    return *this;
}

glm::mat4 Camera::GetViewMatrix(void) const
{
    return glm::lookAt(Position, Position + Center, Up);
}

void Camera::updateCameraVectors(void)
{
        // calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Center = glm::normalize(front);
    // also re-calculate the Right and Up vector
    Right = glm::normalize(glm::cross(Center, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    Up    = glm::normalize(glm::cross(Right, Center));
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw   += xoffset;
        Pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }

        // update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors();
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
    float velocity = MovementSpeed * deltaTime;
    if (direction == FORWARD)
        Position += Center * velocity;
    if (direction == BACKWARD)
        Position -= Center * velocity;
    if (direction == LEFT)
        Position -= Right * velocity;
    if (direction == RIGHT)
        Position += Right * velocity;
}

void Camera::ProcessMouseScroll(float offset)
{
	Zoom -= offset;
	if (Zoom < 1.0f)
		Zoom = 1.0f;
	if (Zoom > 45.0f)
		Zoom = 45.0f;
}